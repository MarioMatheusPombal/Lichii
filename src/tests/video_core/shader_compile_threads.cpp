// SPDX-FileCopyrightText: Copyright 2026 Eden Emulator Project
// SPDX-License-Identifier: GPL-3.0-or-later

#include <catch2/catch_test_macros.hpp>

#include "video_core/renderer_vulkan/shader_compile_threads.h"

using Vulkan::ShaderCompileThreadCount;

TEST_CASE("Auto keeps one core free on large hosts as before", "[video_core][shader_threads]") {
    // The previous desktop rule was max(hw, 2) - 1.
    for (const std::size_t hw : {12U, 16U, 24U, 32U, 64U}) {
        REQUIRE(ShaderCompileThreadCount(0, hw) == hw - 1);
    }
}

TEST_CASE("Auto uses half of the threads on small hosts", "[video_core][shader_threads]") {
    REQUIRE(ShaderCompileThreadCount(0, 11) == 5);
    REQUIRE(ShaderCompileThreadCount(0, 8) == 4);
    REQUIRE(ShaderCompileThreadCount(0, 6) == 3);
    REQUIRE(ShaderCompileThreadCount(0, 4) == 2);
    REQUIRE(ShaderCompileThreadCount(0, 2) == 1);
    REQUIRE(ShaderCompileThreadCount(0, 1) == 1);
    REQUIRE(ShaderCompileThreadCount(0, 0) == 1);
}

TEST_CASE("An explicit count wins and is capped", "[video_core][shader_threads]") {
    REQUIRE(ShaderCompileThreadCount(1, 32) == 1);
    REQUIRE(ShaderCompileThreadCount(6, 4) == 6);
    REQUIRE(ShaderCompileThreadCount(16, 8) == 16);
    REQUIRE(ShaderCompileThreadCount(99, 8) == 16);
}
