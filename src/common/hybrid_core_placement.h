// SPDX-FileCopyrightText: Copyright 2026 Eden Emulator Project
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cstddef>

#include "common/settings_enums.h"

namespace Common {

// Auto only restricts threads to a core class when that class is big enough to be worth the
// restriction. A CPU with a handful of performance threads (for example 4P+8E laptops) is better
// served by letting the scheduler use every core; the same goes for a tiny efficiency cluster
// that would have to carry the texture decoder alone.
inline constexpr std::size_t AutoMinPerformanceThreads = 8;
inline constexpr std::size_t AutoMinEfficiencyThreads = 4;

[[nodiscard]] constexpr bool ShouldPinToPerformanceCores(Settings::HybridCorePlacement mode,
                                                         std::size_t performance_threads) {
    switch (mode) {
    case Settings::HybridCorePlacement::Off:
        return false;
    case Settings::HybridCorePlacement::On:
        return true;
    default:
        return performance_threads >= AutoMinPerformanceThreads;
    }
}

[[nodiscard]] constexpr bool ShouldPinToEfficiencyCores(Settings::HybridCorePlacement mode,
                                                        std::size_t efficiency_threads) {
    switch (mode) {
    case Settings::HybridCorePlacement::Off:
        return false;
    case Settings::HybridCorePlacement::On:
        return true;
    default:
        return efficiency_threads >= AutoMinEfficiencyThreads;
    }
}

} // namespace Common
