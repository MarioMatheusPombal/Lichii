// SPDX-FileCopyrightText: Copyright 2026 Eden Emulator Project
// SPDX-License-Identifier: GPL-3.0-or-later

#include <catch2/catch_test_macros.hpp>

#include "common/hybrid_core_placement.h"

using Common::ShouldPinToEfficiencyCores;
using Common::ShouldPinToPerformanceCores;
using Settings::HybridCorePlacement;

TEST_CASE("Auto pins to performance cores only on large performance clusters",
          "[common][hybrid_core_placement]") {
    // 13900K: 16 P threads. 5800X-like hybrids do not exist, 12600K has 12.
    REQUIRE(ShouldPinToPerformanceCores(HybridCorePlacement::Auto, 16));
    REQUIRE(ShouldPinToPerformanceCores(HybridCorePlacement::Auto, 8));
    // 4P+8E laptop parts expose 8 logical P threads with SMT but 4 without it.
    REQUIRE_FALSE(ShouldPinToPerformanceCores(HybridCorePlacement::Auto, 7));
    REQUIRE_FALSE(ShouldPinToPerformanceCores(HybridCorePlacement::Auto, 4));
    REQUIRE_FALSE(ShouldPinToPerformanceCores(HybridCorePlacement::Auto, 0));
}

TEST_CASE("Auto pins to efficiency cores only on large efficiency clusters",
          "[common][hybrid_core_placement]") {
    REQUIRE(ShouldPinToEfficiencyCores(HybridCorePlacement::Auto, 16));
    REQUIRE(ShouldPinToEfficiencyCores(HybridCorePlacement::Auto, 4));
    REQUIRE_FALSE(ShouldPinToEfficiencyCores(HybridCorePlacement::Auto, 3));
    REQUIRE_FALSE(ShouldPinToEfficiencyCores(HybridCorePlacement::Auto, 0));
}

TEST_CASE("On always pins and Off never pins", "[common][hybrid_core_placement]") {
    for (const std::size_t count : {0U, 2U, 4U, 8U, 16U}) {
        REQUIRE(ShouldPinToPerformanceCores(HybridCorePlacement::On, count));
        REQUIRE(ShouldPinToEfficiencyCores(HybridCorePlacement::On, count));
        REQUIRE_FALSE(ShouldPinToPerformanceCores(HybridCorePlacement::Off, count));
        REQUIRE_FALSE(ShouldPinToEfficiencyCores(HybridCorePlacement::Off, count));
    }
}
