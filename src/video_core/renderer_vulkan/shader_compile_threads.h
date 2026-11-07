// SPDX-FileCopyrightText: Copyright 2026 Eden Emulator Project
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <algorithm>
#include <cstddef>

namespace Vulkan {

inline constexpr std::size_t MaxShaderCompileThreads = 16;

// Number of threads that build pipelines. configured == 0 is Auto: every core but one on hosts
// with 12 or more hardware threads (the long-standing default), half of them on smaller hosts so
// a build burst does not starve the emulation and render threads. hardware_threads may be 0.
[[nodiscard]] constexpr std::size_t ShaderCompileThreadCount(std::size_t configured,
                                                             std::size_t hardware_threads) {
    if (configured != 0) {
        return std::min(configured, MaxShaderCompileThreads);
    }
    if (hardware_threads >= 12) {
        return hardware_threads - 1;
    }
    return std::max<std::size_t>(1, hardware_threads / 2);
}

} // namespace Vulkan
