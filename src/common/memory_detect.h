// SPDX-FileCopyrightText: Copyright 2020 yuzu Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common/common_types.h"

namespace Common {

struct MemoryInfo {
    u64 TotalPhysicalMemory{};
    u64 TotalSwapMemory{};
};

/**
 * Gets the memory info of the host system
 * @return Reference to a MemoryInfo struct with the physical and swap memory sizes in bytes
 */
[[nodiscard]] const MemoryInfo& GetMemInfo();

/**
 * Gets the physical memory that is free right now (not cached at startup, it changes)
 * @return Bytes, or 0 when the platform cannot tell (Android and other platforms included)
 */
[[nodiscard]] u64 GetAvailablePhysicalMemory();

} // namespace Common
