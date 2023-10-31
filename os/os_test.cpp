// SPDX-FileCopyrightText: 2021-2023 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "os/os.h"

#include "etest/etest2.h"

int main() {
    etest::Suite s{"os"};
    s.add_test("font_paths", [](etest::IActions &a) {
        auto font_paths = os::font_paths();
        a.expect(!font_paths.empty());
    });

    return s.run();
}
