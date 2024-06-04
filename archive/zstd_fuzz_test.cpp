// SPDX-FileCopyrightText: 2024 David Zero <zero-one@zer0-one.net>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "archive/zstd.h"

#include <span>
#include <stddef.h> // NOLINT
#include <stdint.h> // NOLINT

extern "C" int LLVMFuzzerTestOneInput(uint8_t const *data, size_t size); // NOLINT

extern "C" int LLVMFuzzerTestOneInput(uint8_t const *data, size_t size) {
    std::ignore = archive::zstd_decode({data, size});
    return 0;
}
