// SPDX-FileCopyrightText: 2022 Contributors to the Power Grid Model project <dynamic.grid.calculation@alliander.com>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <random>

#include "power_grid_model/main_model.hpp"
#include "power_grid_model/timer.hpp"

namespace power_grid_model::benchmark {

struct Option {
    Idx n_node_total_specified;  // rough specification of total nodes
    Idx n_mv_feeder;             // n mv feeder will be changed it is too small
    Idx n_node_per_mv_feeder;
    Idx n_lv_feeder;
    Idx n_connection_per_lv_feeder;    // per connection: one node for connection joint, one node for actual house
    Idx n_parallel_hv_mv_transformer;  // will be calculated
    Idx n_lv_grid;                     // will be calculated
    double ratio_lv_grid;              // ratio when lv grid will be generated
    bool has_mv_ring;
    bool has_lv_ring;
};

struct InputData {
    std::vector<NodeInput> node;
    std::vector<TransformerInput> transformer;
    std::vector<LineInput> line;
    std::vector<SourceInput> source;
    std::vector<SymLoadGenInput> sym_load;
    std::vector<AsymLoadGenInput> asym_load;
    std::vector<ShuntInput> shunt;
};

template <bool sym>
struct OutputData {
    std::vector<NodeOutput<sym>> node;
    std::vector<BranchOutput<sym>> transformer;
    std::vector<BranchOutput<sym>> line;
    std::vector<ApplianceOutput<sym>> source;
    std::vector<ApplianceOutput<sym>> sym_load;
    std::vector<ApplianceOutput<sym>> asym_load;
    std::vector<ApplianceOutput<sym>> shunt;
};

class FictionalGridGenerator {
   public:
    FictionalGridGenerator() {
    }

    void generate_grid(Option const& option) {
        generate_grid(option, std::random_device{}());
    }

    void generate_grid(Option const& option, std::random_device::result_type seed) {
        // initialization
        input_ = InputData{};
        mv_ring_.clear();
        lv_ring_.clear();
        option_ = option;
        gen_ = std::mt19937_64{seed};
        id_gen_ = 0;
        // process option to calculate n_lv_grid
        Idx total_mv_connection = option_.n_mv_feeder * option_.n_node_per_mv_feeder;
        Idx const node_per_lv_grid = option_.n_lv_feeder * option_.n_connection_per_lv_feeder * 2 + 1;
        option_.n_lv_grid = (option_.n_node_total_specified - total_mv_connection) / node_per_lv_grid;
        if (option_.n_lv_grid > total_mv_connection) {
            option_.n_mv_feeder = option_.n_lv_grid / option_.n_node_per_mv_feeder + 1;
        }
        total_mv_connection = option_.n_mv_feeder * option_.n_node_per_mv_feeder;
        option_.ratio_lv_grid = (double)option_.n_lv_grid / (double)total_mv_connection;
        // each mv connection 1MVA, each transformer 60 MVA, scaled by 10%
        option_.n_parallel_hv_mv_transformer = (int)((double)total_mv_connection * 1.1 / 60.0) + 1;
        // start generating grid
        generate_mv_grid();
    }

    void generate_mv_grid() {
        // source node
        Idx const id_source_node = id_gen_++;
        NodeInput const source_node{{id_source_node}, 150.0e3};
        input_.node.push_back(source_node);
        SourceInput const source{{{id_gen_++}, id_source_node, true}, 1.05, nan, 1e20, nan, nan};
        input_.source.push_back(source);

        // transformer and mv busbar
        Idx const id_mv_busbar = id_gen_++;
        NodeInput const mv_busbar{{id_mv_busbar}, 10.5e3};
        input_.node.push_back(mv_busbar);
        for (Idx i = 0; i != option_.n_parallel_hv_mv_transformer; ++i) {
            // transformer, 150/10.5kV, 60MVA, uk=20.3%
            TransformerInput const transformer{{{id_gen_++}, id_source_node, id_mv_busbar, true, true},
                                              150.0e3,
                                              10.5e3,
                                              60.0e6,
                                              0.203,
                                              200e3,
                                              0.01,
                                              40e3,
                                              WindingType::wye_n,
                                              WindingType::delta,
                                              5,
                                              BranchSide::from,
                                              0,
                                              -10,
                                              10,
                                              0,
                                              2.5e3,
                                              nan,
                                              nan,
                                              nan,
                                              nan,
                                              nan,
                                              nan,
                                              nan,
                                              nan};
            input_.transformer.push_back(transformer);
            // shunt, Z0 = 0 + j7 ohm
            ShuntInput const shunt{{{id_gen_++}, id_mv_busbar, true}, 0.0, 0.0, 0.0, -1.0 / 7.0};
            input_.shunt.push_back(shunt);
        }


        // template input
        NodeInput const mv_node{{0}, 10.5e3};
        SymLoadGenInput const mv_sym_load{{{{0}, 0, true}, LoadGenType::const_i}, 0.8e6, 0.6e6};
        // cable 630Al XLPE 10kV with neutral conductor, 1 km
        LineInput const mv_line{{{0}, 0, 0, true, true}, 0.063, 0.103, 0.4e-6, 0.0004, 0.275, 0.101, 0.66e-6, 0.0, 1e3};

        // random generator
        std::uniform_int_distribution<Idx> load_type_gen{0, 2};
        // scaled with 10 times
        std::uniform_real_distribution<double> real_gen{0.8 * 10.0 / option_.n_node_per_mv_feeder,
                                                        1.2 * 10.0 / option_.n_node_per_mv_feeder};
        std::bernoulli_distribution lv_gen{option_.ratio_lv_grid};

        // loop all feeder
        for (Idx i = 0; i < option_.n_mv_feeder; i++) {
            Idx prev_node_id = id_mv_busbar;
            // loop all mv connection
            for (Idx j = 0; j < option_.n_node_per_mv_feeder; ++j) {
                // node
                Idx const current_node_id = id_gen_++;
                NodeInput node = mv_node;
                node.id = current_node_id;
                input_.node.push_back(node);
                // line
                LineInput line = mv_line;
                line.id = id_gen_++;
                line.from_node = prev_node_id;
                line.to_node = current_node_id;
                // scale r1, x1, r0, x0
                double const cable_ratio = real_gen(gen_);
                line.r1 *= cable_ratio;
                line.x1 *= cable_ratio;
                line.c1 *= cable_ratio;
                line.r0 *= cable_ratio;
                line.x0 *= cable_ratio;
                line.c0 *= cable_ratio;
                input_.line.push_back(line);
                // generate lv grid
                if (lv_gen(gen_)) {
                    generate_lv_grid(current_node_id);
                    continue;
                }
                // generate mv sym load
                SymLoadGenInput sym_load = mv_sym_load;
                sym_load.id = id_gen_++;
                sym_load.node = current_node_id;
                sym_load.type = static_cast<LoadGenType>((IntS)load_type_gen(gen_));
                double const sym_scale = real_gen(gen_);
                sym_load.p_specified *= sym_scale;
                sym_load.q_specified *= sym_scale;
                input_.sym_load.push_back(sym_load);
                // push to ring node
                if (j == option_.n_node_per_mv_feeder - 1) {
                    mv_ring_.push_back(current_node_id);
                }
            }

        }
        // add loop if needed, and there are more than one feeder, and there are ring nodes
        if (mv_ring_.size() > 1 && option_.has_mv_ring) {
        }

    }

    void generate_lv_grid(Idx mv_node) {
    }

   private:
    Option option_{};
    std::mt19937_64 gen_;
    Idx id_gen_;
    InputData input_;
    OutputData<true> sym_output_;
    OutputData<false> asym_output_;
    std::vector<Idx> mv_ring_;
    std::vector<Idx> lv_ring_;
};

}  // namespace power_grid_model::benchmark