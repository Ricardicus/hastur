// SPDX-FileCopyrightText: 2025 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "json/json.h"

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <tuple>

extern "C" int LLVMFuzzerTestOneInput(std::uint8_t const *data, std::size_t size);

extern "C" int LLVMFuzzerTestOneInput(std::uint8_t const *data, std::size_t size) {
    std::ignore = json::parse(std::string_view{reinterpret_cast<char const *>(data), size});
    return 0;
}