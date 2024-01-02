// SPDX-FileCopyrightText: 2022 Contributors to the Power Grid Model project <dynamic.grid.calculation@alliander.com>
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#ifndef POWER_GRID_MODEL_CALCULATION_PARAMETERS_HPP
#define POWER_GRID_MODEL_CALCULATION_PARAMETERS_HPP

#include "enum.hpp"
#include "grouped_index_vector.hpp"
#include "power_grid_model.hpp"
#include "three_phase_tensor.hpp"

namespace power_grid_model {

// Entry of YBus, node addmittance matrix
struct YBusElement {
    YBusElementType element_type{};
    Idx idx{}; // index of the component
};

// everything here always per unit

// branch math calculation parameter and math output
template <bool sym> struct BranchCalcParam {
    std::array<ComplexTensor<sym>, 4> value;
    // getter
    ComplexTensor<sym>& yff() { return value[0]; }
    ComplexTensor<sym> const& yff() const { return value[0]; }
    ComplexTensor<sym>& yft() { return value[1]; }
    ComplexTensor<sym> const& yft() const { return value[1]; }
    ComplexTensor<sym>& ytf() { return value[2]; }
    ComplexTensor<sym> const& ytf() const { return value[2]; }
    ComplexTensor<sym>& ytt() { return value[3]; }
    ComplexTensor<sym> const& ytt() const { return value[3]; }
};

template <bool sym> struct BranchMathOutput {
    ComplexValue<sym> s_f{};
    ComplexValue<sym> s_t{};
    ComplexValue<sym> i_f{};
    ComplexValue<sym> i_t{};
};

template <bool sym> struct BranchShortCircuitMathOutput {
    ComplexValue<sym> i_f{};
    ComplexValue<sym> i_t{};
};

// fault math calculation parameters and math output
struct FaultCalcParam {
    DoubleComplex y_fault{};
    FaultType fault_type{};
    FaultPhase fault_phase{};
};

template <bool sym> struct FaultShortCircuitMathOutput {
    ComplexValue<sym> i_fault{};
};

// appliance math output, always injection direction
// s > 0, energy appliance -> node
template <bool sym> struct ApplianceMathOutput {
    ComplexValue<sym> s{};
    ComplexValue<sym> i{};
};
template <bool sym> struct ApplianceShortCircuitMathOutput {
    ComplexValue<sym> i{};
};

// Complex measured value of a sensor in p.u. with a uniform variance across all phases and axes of the complex plane
// (circularly symmetric)
template <bool sym> struct UniformComplexRandomVariable {
    static constexpr bool symmetric{sym};

    ComplexValue<sym> value{};
    double variance{}; // variance (sigma^2) of the error range, in p.u.
};

// voltage sensor calculation parameters for state estimation
// The value is the complex voltage
// If the imaginary part is NaN, it means the angle calculation is not correct
template <bool sym> using VoltageSensorCalcParam = UniformComplexRandomVariable<sym>;

// power sensor calculation parameters for state estimation
// The value is the complex power
//   * for appliances, it is always in injection direction
//   * for branches, the direction is node -> branch
template <bool sym> struct PowerSensorCalcParam {
    static constexpr bool symmetric{sym};

    ComplexValue<sym> value{};
    RealValue<sym> p_variance{}; // variance (sigma^2) of the error range of the active power, in p.u.
    RealValue<sym> q_variance{}; // variance (sigma^2) of the error range of the reactive power, in p.u.
};

template <typename T>
concept sensor_calc_param_type =
    std::same_as<T, VoltageSensorCalcParam<true>> || std::same_as<T, VoltageSensorCalcParam<false>> ||
    std::same_as<T, PowerSensorCalcParam<true>> || std::same_as<T, PowerSensorCalcParam<false>>;

static_assert(sensor_calc_param_type<VoltageSensorCalcParam<true>>);
static_assert(sensor_calc_param_type<VoltageSensorCalcParam<false>>);
static_assert(sensor_calc_param_type<PowerSensorCalcParam<true>>);
static_assert(sensor_calc_param_type<PowerSensorCalcParam<false>>);

// from, to side
// in case of indices for math model, -1 means the branch is not connected to that side
using BranchIdx = std::array<Idx, 2>;
// node 0, 1, 2 side
// in case of indices for math model, -1 means the branch is not connected to that side
using Branch3Idx = std::array<Idx, 3>;

struct MathModelTopology {
    Idx slack_bus_{};
    std::vector<double> phase_shift;
    std::vector<BranchIdx> branch_bus_idx;
    std::vector<BranchIdx> fill_in;
    DenseGroupedIdxVector sources_per_bus;
    DenseGroupedIdxVector shunts_per_bus;
    SparseGroupedIdxVector load_gens_per_bus;
    std::vector<LoadGenType> load_gen_type;
    DenseGroupedIdxVector voltage_sensors_per_bus;
    DenseGroupedIdxVector power_sensors_per_source;
    DenseGroupedIdxVector power_sensors_per_load_gen;
    DenseGroupedIdxVector power_sensors_per_shunt;
    DenseGroupedIdxVector power_sensors_per_branch_from;
    DenseGroupedIdxVector power_sensors_per_branch_to;
    DenseGroupedIdxVector power_sensors_per_bus;

    Idx n_bus() const { return static_cast<Idx>(phase_shift.size()); }

    Idx n_branch() const { return static_cast<Idx>(branch_bus_idx.size()); }

    Idx n_source() const { return sources_per_bus.element_size(); }

    Idx n_shunt() const { return shunts_per_bus.element_size(); }

    Idx n_load_gen() const { return load_gens_per_bus.element_size(); }

    Idx n_voltage_sensor() const { return voltage_sensors_per_bus.element_size(); }

    Idx n_source_power_sensor() const { return power_sensors_per_source.element_size(); }

    Idx n_load_gen_power_sensor() const { return power_sensors_per_load_gen.element_size(); }

    Idx n_shunt_power_power_sensor() const { return power_sensors_per_shunt.element_size(); }

    Idx n_branch_from_power_sensor() const { return power_sensors_per_branch_from.element_size(); }

    Idx n_branch_to_power_sensor() const { return power_sensors_per_branch_to.element_size(); }

    Idx n_bus_power_sensor() const { return power_sensors_per_bus.element_size(); }
};

template <bool sym> struct MathModelParam {
    std::vector<BranchCalcParam<sym>> branch_param;
    ComplexTensorVector<sym> shunt_param;
    ComplexTensorVector<sym> source_param;
};

template <bool sym> struct MathModelParamIncrement {
    //MathModelParam<sym> param;
    //std::vector<BranchCalcParam<sym>> branch_param;
    //ComplexTensorVector<sym> shunt_param;
    //ComplexTensorVector<sym> source_param;
    std::vector<Idx> branch_param_to_change;
    std::vector<Idx> shunt_param_to_change;
};

template <bool sym> struct PowerFlowInput {
    ComplexVector source;                // Complex u_ref of each source
    ComplexValueVector<sym> s_injection; // Specified injection power of each load_gen
};

template <bool sym> struct StateEstimationInput {
    // connection status of shunt, load_gen, source
    // this is needed to determine if a measurement is relevant
    // if the shunt/load_gen/source is disconnected, all its measurements are discarded
    IntSVector shunt_status;
    IntSVector load_gen_status;
    IntSVector source_status;
    // measured value
    std::vector<VoltageSensorCalcParam<sym>> measured_voltage;
    std::vector<PowerSensorCalcParam<sym>> measured_source_power;
    std::vector<PowerSensorCalcParam<sym>> measured_load_gen_power;
    std::vector<PowerSensorCalcParam<sym>> measured_shunt_power;
    std::vector<PowerSensorCalcParam<sym>> measured_branch_from_power;
    std::vector<PowerSensorCalcParam<sym>> measured_branch_to_power;
    std::vector<PowerSensorCalcParam<sym>> measured_bus_injection;
};

struct ShortCircuitInput {
    DenseGroupedIdxVector fault_buses;
    std::vector<FaultCalcParam> faults;
    ComplexVector source; // Complex u_ref of each source
};

template <typename T>
concept symmetric_calculation_input_type =
    std::same_as<T, PowerFlowInput<true>> || std::same_as<T, StateEstimationInput<true>>;

static_assert(symmetric_calculation_input_type<PowerFlowInput<true>>);
static_assert(symmetric_calculation_input_type<StateEstimationInput<true>>);
static_assert(!symmetric_calculation_input_type<PowerFlowInput<false>>);
static_assert(!symmetric_calculation_input_type<StateEstimationInput<false>>);
static_assert(!symmetric_calculation_input_type<ShortCircuitInput>);

template <typename T>
concept asymmetric_calculation_input_type =
    std::same_as<T, PowerFlowInput<false>> || std::same_as<T, StateEstimationInput<false>> ||
    std::same_as<T, ShortCircuitInput>;

static_assert(!asymmetric_calculation_input_type<PowerFlowInput<true>>);
static_assert(!asymmetric_calculation_input_type<StateEstimationInput<true>>);
static_assert(asymmetric_calculation_input_type<PowerFlowInput<false>>);
static_assert(asymmetric_calculation_input_type<StateEstimationInput<false>>);
static_assert(asymmetric_calculation_input_type<ShortCircuitInput>);

template <typename T>
concept calculation_input_type = symmetric_calculation_input_type<T> || asymmetric_calculation_input_type<T>;

static_assert(calculation_input_type<PowerFlowInput<true>>);
static_assert(calculation_input_type<StateEstimationInput<true>>);
static_assert(calculation_input_type<PowerFlowInput<false>>);
static_assert(calculation_input_type<StateEstimationInput<false>>);
static_assert(calculation_input_type<ShortCircuitInput>);

template <bool sym> struct MathOutput {
    std::vector<ComplexValue<sym>> u;
    std::vector<ComplexValue<sym>> bus_injection;
    std::vector<BranchMathOutput<sym>> branch;
    std::vector<ApplianceMathOutput<sym>> source;
    std::vector<ApplianceMathOutput<sym>> shunt;
    std::vector<ApplianceMathOutput<sym>> load_gen;
};

template <bool sym> struct ShortCircuitMathOutput {
    std::vector<ComplexValue<sym>> u_bus;
    std::vector<FaultShortCircuitMathOutput<sym>> fault;
    std::vector<BranchShortCircuitMathOutput<sym>> branch;
    std::vector<ApplianceShortCircuitMathOutput<sym>> source;
    std::vector<ApplianceShortCircuitMathOutput<sym>> shunt;
};

template <typename T>
concept symmetric_math_output_type = std::same_as<T, MathOutput<true>> || std::same_as<T, ShortCircuitMathOutput<true>>;

static_assert(symmetric_math_output_type<MathOutput<true>>);
static_assert(!symmetric_math_output_type<MathOutput<false>>);
static_assert(symmetric_math_output_type<ShortCircuitMathOutput<true>>);
static_assert(!symmetric_math_output_type<ShortCircuitMathOutput<false>>);

template <typename T>
concept asymmetric_math_output_type =
    std::same_as<T, MathOutput<false>> || std::same_as<T, ShortCircuitMathOutput<false>>;

static_assert(!asymmetric_math_output_type<MathOutput<true>>);
static_assert(asymmetric_math_output_type<MathOutput<false>>);
static_assert(!asymmetric_math_output_type<ShortCircuitMathOutput<true>>);
static_assert(asymmetric_math_output_type<ShortCircuitMathOutput<false>>);

template <typename T>
concept steady_state_math_output_type = std::same_as<T, MathOutput<true>> || std::same_as<T, MathOutput<false>>;

static_assert(steady_state_math_output_type<MathOutput<true>>);
static_assert(steady_state_math_output_type<MathOutput<false>>);
static_assert(!steady_state_math_output_type<ShortCircuitMathOutput<true>>);
static_assert(!steady_state_math_output_type<ShortCircuitMathOutput<false>>);

template <typename T>
concept short_circuit_math_output_type =
    std::same_as<T, ShortCircuitMathOutput<true>> || std::same_as<T, ShortCircuitMathOutput<false>>;

static_assert(!short_circuit_math_output_type<MathOutput<true>>);
static_assert(!short_circuit_math_output_type<MathOutput<false>>);
static_assert(short_circuit_math_output_type<ShortCircuitMathOutput<true>>);
static_assert(short_circuit_math_output_type<ShortCircuitMathOutput<false>>);

template <typename T>
concept math_output_type = (symmetric_math_output_type<T> || asymmetric_math_output_type<T>) &&
                           (steady_state_math_output_type<T> || short_circuit_math_output_type<T>);

static_assert(math_output_type<MathOutput<true>>);
static_assert(math_output_type<MathOutput<false>>);
static_assert(math_output_type<ShortCircuitMathOutput<true>>);
static_assert(math_output_type<ShortCircuitMathOutput<false>>);

// component indices at physical model side
// from, to node indices for branches
// node1, node2, node3 indices for 3-way branches
// node indices for source, load_gen, shunt
struct ComponentTopology {
    Idx n_node{};
    std::vector<BranchIdx> branch_node_idx;
    std::vector<Branch3Idx> branch3_node_idx;
    IdxVector shunt_node_idx;
    IdxVector source_node_idx;
    IdxVector load_gen_node_idx;
    std::vector<LoadGenType> load_gen_type;
    IdxVector voltage_sensor_node_idx;
    IdxVector power_sensor_object_idx; // the index is relative to branch, source, shunt, or load_gen
    std::vector<MeasuredTerminalType> power_sensor_terminal_type;

    inline Idx n_node_total() const { return n_node + (Idx)branch3_node_idx.size(); }
};

// connection property
using BranchConnected = std::array<IntS, 2>;
using Branch3Connected = std::array<IntS, 3>;

// component connection property at model side
struct ComponentConnections {
    std::vector<BranchConnected> branch_connected;
    std::vector<Branch3Connected> branch3_connected;
    DoubleVector branch_phase_shift;
    // 3-way branch, phase shift = phase_node_x - phase_internal_node
    std::vector<std::array<double, 3>> branch3_phase_shift;
    IntSVector source_connected;
};

// To couple 3-way branch, to math model, 3 virtual branches are created
// they are always in the same math model group
// sequence numbers of 3 virtual branches are saved in pos
struct Idx2DBranch3 {
    Idx group{};
    // 0: node 0 -> internal node
    // 1: node 1 -> internal node
    // 2: node 2 -> internal node
    std::array<Idx, 3> pos;

    friend constexpr bool operator==(Idx2DBranch3 const& x, Idx2DBranch3 const& y) = default;
};

// couple component to math model
// use Idx2D to map component to math model
//		group = math model sequence number,
//		group = -1 means isolated component
//		pos = sequence number in math model,
//		pos = -1 means not connected at that side, only applicable for branches
struct ComponentToMathCoupling {
    std::vector<Idx2D> fault;
};

// couple component to math model
// like ComponentToMathCoupling but for components that are immutable after the topology is fixed
// use Idx2D to map component to math model
//		group = math model sequence number,
//		group = -1 means isolated component
//		pos = sequence number in math model,
//		pos = -1 means not connected at that side, only applicable for branches
struct TopologicalComponentToMathCoupling {
    std::vector<Idx2D> node;
    std::vector<Idx2D> branch;
    std::vector<Idx2DBranch3> branch3;
    std::vector<Idx2D> shunt;
    std::vector<Idx2D> load_gen;
    std::vector<Idx2D> source;
    std::vector<Idx2D> voltage_sensor;
    std::vector<Idx2D> power_sensor; // can be coupled to branch-from/to, source, load_gen, or shunt sensor
};

// change of update cause topology and param change, or just param change
struct UpdateChange {
    bool topo{};
    bool param{};

    friend constexpr UpdateChange operator||(UpdateChange const& x, UpdateChange const& y) {
        return UpdateChange{x.topo || y.topo, x.param || y.param};
    }
};

} // namespace power_grid_model

#endif
