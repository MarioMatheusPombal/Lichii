// SPDX-FileCopyrightText: Copyright 2026 Eden Emulator Project
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "common/settings_enums.h"

namespace Kernel {

// Hosts with fewer hardware threads than this keep the idle emulated core asleep in Auto: the
// polling core would compete with the host threads that actually produce the work.
inline constexpr unsigned AutoIdleSpinMinHardwareThreads = 8;

// Decides whether an idle emulated core of a Switch 2 application polls before it blocks.
// hardware_threads is std::thread::hardware_concurrency(), which may be 0 when unknown.
[[nodiscard]] constexpr bool ShouldSpinWhenIdle(Settings::CoreIdleSpin mode,
                                                unsigned hardware_threads) {
    switch (mode) {
    case Settings::CoreIdleSpin::Off:
        return false;
    case Settings::CoreIdleSpin::On:
        return true;
    default:
        return hardware_threads >= AutoIdleSpinMinHardwareThreads;
    }
}

} // namespace Kernel
