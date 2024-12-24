// SPDX-FileCopyrightText: 2021-2024 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "etest/etest2.h"

int main() {
    etest::Suite s{};
    s.add_test("this should fail", [](etest::IActions &a) { a.expect_eq(1, 2); });
    return s.run();
}
