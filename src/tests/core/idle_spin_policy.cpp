// SPDX-FileCopyrightText: Copyright 2026 Eden Emulator Project
// SPDX-License-Identifier: GPL-3.0-or-later

#include <catch2/catch_test_macros.hpp>

#include "core/hle/kernel/idle_spin_policy.h"

using Kernel::ShouldSpinWhenIdle;
using Settings::CoreIdleSpin;

TEST_CASE("Auto idle spin needs at least eight host threads", "[core][idle_spin]") {
    CHECK(ShouldSpinWhenIdle(CoreIdleSpin::Auto, 32));
    CHECK(ShouldSpinWhenIdle(CoreIdleSpin::Auto, 16));
    CHECK(ShouldSpinWhenIdle(CoreIdleSpin::Auto, 8));
    CHECK_FALSE(ShouldSpinWhenIdle(CoreIdleSpin::Auto, 7));
    CHECK_FALSE(ShouldSpinWhenIdle(CoreIdleSpin::Auto, 4));
    CHECK_FALSE(ShouldSpinWhenIdle(CoreIdleSpin::Auto, 0));
}

TEST_CASE("On and Off ignore the host thread count", "[core][idle_spin]") {
    for (const unsigned threads : {0U, 2U, 8U, 64U}) {
        CHECK(ShouldSpinWhenIdle(CoreIdleSpin::On, threads));
        CHECK_FALSE(ShouldSpinWhenIdle(CoreIdleSpin::Off, threads));
    }
}
