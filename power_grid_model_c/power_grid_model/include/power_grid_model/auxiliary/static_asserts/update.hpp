// SPDX-FileCopyrightText: 2022 Contributors to the Power Grid Model project <dynamic.grid.calculation@alliander.com>
//
// SPDX-License-Identifier: MPL-2.0

// This header file is automatically generated. DO NOT modify it manually!

// clang-format off
#pragma once
#ifndef POWER_GRID_MODEL_AUXILIARY_STATIC_ASSERTS_UPDATE_HPP
#define POWER_GRID_MODEL_AUXILIARY_STATIC_ASSERTS_UPDATE_HPP

#include "../update.hpp" // NOLINT

#include <cstddef>

namespace power_grid_model::test {

// static asserts for BaseUpdate
static_assert(std::is_standard_layout_v<BaseUpdate>);

// static asserts for BranchUpdate
static_assert(std::is_standard_layout_v<BranchUpdate>);
// static asserts for conversion of BranchUpdate to BaseUpdate
static_assert(std::alignment_of_v<BranchUpdate> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(BranchUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(BranchUpdate, id) == offsetof(BaseUpdate, id));

// static asserts for Branch3Update
static_assert(std::is_standard_layout_v<Branch3Update>);
// static asserts for conversion of Branch3Update to BaseUpdate
static_assert(std::alignment_of_v<Branch3Update> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(Branch3Update::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(Branch3Update, id) == offsetof(BaseUpdate, id));

// static asserts for ApplianceUpdate
static_assert(std::is_standard_layout_v<ApplianceUpdate>);
// static asserts for conversion of ApplianceUpdate to BaseUpdate
static_assert(std::alignment_of_v<ApplianceUpdate> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(ApplianceUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(ApplianceUpdate, id) == offsetof(BaseUpdate, id));

// static asserts for TransformerUpdate
static_assert(std::is_standard_layout_v<TransformerUpdate>);
// static asserts for conversion of TransformerUpdate to BaseUpdate
static_assert(std::alignment_of_v<TransformerUpdate> >= std::alignment_of_v<BranchUpdate>);
static_assert(std::same_as<decltype(TransformerUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(TransformerUpdate, id) == offsetof(BaseUpdate, id));
// static asserts for conversion of TransformerUpdate to BranchUpdate
static_assert(std::alignment_of_v<TransformerUpdate> >= std::alignment_of_v<BranchUpdate>);
static_assert(std::same_as<decltype(TransformerUpdate::id), decltype(BranchUpdate::id)>);
static_assert(std::same_as<decltype(TransformerUpdate::from_status), decltype(BranchUpdate::from_status)>);
static_assert(std::same_as<decltype(TransformerUpdate::to_status), decltype(BranchUpdate::to_status)>);
static_assert(offsetof(TransformerUpdate, id) == offsetof(BranchUpdate, id));
static_assert(offsetof(TransformerUpdate, from_status) == offsetof(BranchUpdate, from_status));
static_assert(offsetof(TransformerUpdate, to_status) == offsetof(BranchUpdate, to_status));

// static asserts for ThreeWindingTransformerUpdate
static_assert(std::is_standard_layout_v<ThreeWindingTransformerUpdate>);
// static asserts for conversion of ThreeWindingTransformerUpdate to BaseUpdate
static_assert(std::alignment_of_v<ThreeWindingTransformerUpdate> >= std::alignment_of_v<Branch3Update>);
static_assert(std::same_as<decltype(ThreeWindingTransformerUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(ThreeWindingTransformerUpdate, id) == offsetof(BaseUpdate, id));
// static asserts for conversion of ThreeWindingTransformerUpdate to Branch3Update
static_assert(std::alignment_of_v<ThreeWindingTransformerUpdate> >= std::alignment_of_v<Branch3Update>);
static_assert(std::same_as<decltype(ThreeWindingTransformerUpdate::id), decltype(Branch3Update::id)>);
static_assert(std::same_as<decltype(ThreeWindingTransformerUpdate::status_1), decltype(Branch3Update::status_1)>);
static_assert(std::same_as<decltype(ThreeWindingTransformerUpdate::status_2), decltype(Branch3Update::status_2)>);
static_assert(std::same_as<decltype(ThreeWindingTransformerUpdate::status_3), decltype(Branch3Update::status_3)>);
static_assert(offsetof(ThreeWindingTransformerUpdate, id) == offsetof(Branch3Update, id));
static_assert(offsetof(ThreeWindingTransformerUpdate, status_1) == offsetof(Branch3Update, status_1));
static_assert(offsetof(ThreeWindingTransformerUpdate, status_2) == offsetof(Branch3Update, status_2));
static_assert(offsetof(ThreeWindingTransformerUpdate, status_3) == offsetof(Branch3Update, status_3));

// static asserts for LoadGenUpdate<true>
static_assert(std::is_standard_layout_v<LoadGenUpdate<true>>);
// static asserts for conversion of LoadGenUpdate<true> to BaseUpdate
static_assert(std::alignment_of_v<LoadGenUpdate<true>> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(LoadGenUpdate<true>::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(LoadGenUpdate<true>, id) == offsetof(BaseUpdate, id));
// static asserts for conversion of LoadGenUpdate<true> to ApplianceUpdate
static_assert(std::alignment_of_v<LoadGenUpdate<true>> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(LoadGenUpdate<true>::id), decltype(ApplianceUpdate::id)>);
static_assert(std::same_as<decltype(LoadGenUpdate<true>::status), decltype(ApplianceUpdate::status)>);
static_assert(offsetof(LoadGenUpdate<true>, id) == offsetof(ApplianceUpdate, id));
static_assert(offsetof(LoadGenUpdate<true>, status) == offsetof(ApplianceUpdate, status));
// static asserts for LoadGenUpdate<false>
static_assert(std::is_standard_layout_v<LoadGenUpdate<false>>);
// static asserts for conversion of LoadGenUpdate<false> to BaseUpdate
static_assert(std::alignment_of_v<LoadGenUpdate<false>> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(LoadGenUpdate<false>::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(LoadGenUpdate<false>, id) == offsetof(BaseUpdate, id));
// static asserts for conversion of LoadGenUpdate<false> to ApplianceUpdate
static_assert(std::alignment_of_v<LoadGenUpdate<false>> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(LoadGenUpdate<false>::id), decltype(ApplianceUpdate::id)>);
static_assert(std::same_as<decltype(LoadGenUpdate<false>::status), decltype(ApplianceUpdate::status)>);
static_assert(offsetof(LoadGenUpdate<false>, id) == offsetof(ApplianceUpdate, id));
static_assert(offsetof(LoadGenUpdate<false>, status) == offsetof(ApplianceUpdate, status));
// static asserts for SymLoadGenUpdate
static_assert(std::is_standard_layout_v<SymLoadGenUpdate>);
// static asserts for conversion of SymLoadGenUpdate to BaseUpdate
static_assert(std::alignment_of_v<SymLoadGenUpdate> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(SymLoadGenUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(SymLoadGenUpdate, id) == offsetof(BaseUpdate, id));
// static asserts for conversion of SymLoadGenUpdate to ApplianceUpdate
static_assert(std::alignment_of_v<SymLoadGenUpdate> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(SymLoadGenUpdate::id), decltype(ApplianceUpdate::id)>);
static_assert(std::same_as<decltype(SymLoadGenUpdate::status), decltype(ApplianceUpdate::status)>);
static_assert(offsetof(SymLoadGenUpdate, id) == offsetof(ApplianceUpdate, id));
static_assert(offsetof(SymLoadGenUpdate, status) == offsetof(ApplianceUpdate, status));
// static asserts for AsymLoadGenUpdate
static_assert(std::is_standard_layout_v<AsymLoadGenUpdate>);
// static asserts for conversion of AsymLoadGenUpdate to BaseUpdate
static_assert(std::alignment_of_v<AsymLoadGenUpdate> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(AsymLoadGenUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(AsymLoadGenUpdate, id) == offsetof(BaseUpdate, id));
// static asserts for conversion of AsymLoadGenUpdate to ApplianceUpdate
static_assert(std::alignment_of_v<AsymLoadGenUpdate> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(AsymLoadGenUpdate::id), decltype(ApplianceUpdate::id)>);
static_assert(std::same_as<decltype(AsymLoadGenUpdate::status), decltype(ApplianceUpdate::status)>);
static_assert(offsetof(AsymLoadGenUpdate, id) == offsetof(ApplianceUpdate, id));
static_assert(offsetof(AsymLoadGenUpdate, status) == offsetof(ApplianceUpdate, status));

// static asserts for SourceUpdate
static_assert(std::is_standard_layout_v<SourceUpdate>);
// static asserts for conversion of SourceUpdate to BaseUpdate
static_assert(std::alignment_of_v<SourceUpdate> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(SourceUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(SourceUpdate, id) == offsetof(BaseUpdate, id));
// static asserts for conversion of SourceUpdate to ApplianceUpdate
static_assert(std::alignment_of_v<SourceUpdate> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(SourceUpdate::id), decltype(ApplianceUpdate::id)>);
static_assert(std::same_as<decltype(SourceUpdate::status), decltype(ApplianceUpdate::status)>);
static_assert(offsetof(SourceUpdate, id) == offsetof(ApplianceUpdate, id));
static_assert(offsetof(SourceUpdate, status) == offsetof(ApplianceUpdate, status));

// static asserts for ShuntUpdate
static_assert(std::is_standard_layout_v<ShuntUpdate>);
// static asserts for conversion of ShuntUpdate to BaseUpdate
static_assert(std::alignment_of_v<ShuntUpdate> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(ShuntUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(ShuntUpdate, id) == offsetof(BaseUpdate, id));
// static asserts for conversion of ShuntUpdate to ApplianceUpdate
static_assert(std::alignment_of_v<ShuntUpdate> >= std::alignment_of_v<ApplianceUpdate>);
static_assert(std::same_as<decltype(ShuntUpdate::id), decltype(ApplianceUpdate::id)>);
static_assert(std::same_as<decltype(ShuntUpdate::status), decltype(ApplianceUpdate::status)>);
static_assert(offsetof(ShuntUpdate, id) == offsetof(ApplianceUpdate, id));
static_assert(offsetof(ShuntUpdate, status) == offsetof(ApplianceUpdate, status));

// static asserts for VoltageSensorUpdate<true>
static_assert(std::is_standard_layout_v<VoltageSensorUpdate<true>>);
// static asserts for conversion of VoltageSensorUpdate<true> to BaseUpdate
static_assert(std::alignment_of_v<VoltageSensorUpdate<true>> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(VoltageSensorUpdate<true>::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(VoltageSensorUpdate<true>, id) == offsetof(BaseUpdate, id));
// static asserts for VoltageSensorUpdate<false>
static_assert(std::is_standard_layout_v<VoltageSensorUpdate<false>>);
// static asserts for conversion of VoltageSensorUpdate<false> to BaseUpdate
static_assert(std::alignment_of_v<VoltageSensorUpdate<false>> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(VoltageSensorUpdate<false>::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(VoltageSensorUpdate<false>, id) == offsetof(BaseUpdate, id));
// static asserts for SymVoltageSensorUpdate
static_assert(std::is_standard_layout_v<SymVoltageSensorUpdate>);
// static asserts for conversion of SymVoltageSensorUpdate to BaseUpdate
static_assert(std::alignment_of_v<SymVoltageSensorUpdate> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(SymVoltageSensorUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(SymVoltageSensorUpdate, id) == offsetof(BaseUpdate, id));
// static asserts for AsymVoltageSensorUpdate
static_assert(std::is_standard_layout_v<AsymVoltageSensorUpdate>);
// static asserts for conversion of AsymVoltageSensorUpdate to BaseUpdate
static_assert(std::alignment_of_v<AsymVoltageSensorUpdate> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(AsymVoltageSensorUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(AsymVoltageSensorUpdate, id) == offsetof(BaseUpdate, id));

// static asserts for PowerSensorUpdate<true>
static_assert(std::is_standard_layout_v<PowerSensorUpdate<true>>);
// static asserts for conversion of PowerSensorUpdate<true> to BaseUpdate
static_assert(std::alignment_of_v<PowerSensorUpdate<true>> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(PowerSensorUpdate<true>::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(PowerSensorUpdate<true>, id) == offsetof(BaseUpdate, id));
// static asserts for PowerSensorUpdate<false>
static_assert(std::is_standard_layout_v<PowerSensorUpdate<false>>);
// static asserts for conversion of PowerSensorUpdate<false> to BaseUpdate
static_assert(std::alignment_of_v<PowerSensorUpdate<false>> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(PowerSensorUpdate<false>::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(PowerSensorUpdate<false>, id) == offsetof(BaseUpdate, id));
// static asserts for SymPowerSensorUpdate
static_assert(std::is_standard_layout_v<SymPowerSensorUpdate>);
// static asserts for conversion of SymPowerSensorUpdate to BaseUpdate
static_assert(std::alignment_of_v<SymPowerSensorUpdate> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(SymPowerSensorUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(SymPowerSensorUpdate, id) == offsetof(BaseUpdate, id));
// static asserts for AsymPowerSensorUpdate
static_assert(std::is_standard_layout_v<AsymPowerSensorUpdate>);
// static asserts for conversion of AsymPowerSensorUpdate to BaseUpdate
static_assert(std::alignment_of_v<AsymPowerSensorUpdate> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(AsymPowerSensorUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(AsymPowerSensorUpdate, id) == offsetof(BaseUpdate, id));

// static asserts for FaultUpdate
static_assert(std::is_standard_layout_v<FaultUpdate>);
// static asserts for conversion of FaultUpdate to BaseUpdate
static_assert(std::alignment_of_v<FaultUpdate> >= std::alignment_of_v<BaseUpdate>);
static_assert(std::same_as<decltype(FaultUpdate::id), decltype(BaseUpdate::id)>);
static_assert(offsetof(FaultUpdate, id) == offsetof(BaseUpdate, id));



} // namespace power_grid_model::test

#endif
// clang-format on