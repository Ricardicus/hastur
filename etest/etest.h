// SPDX-FileCopyrightText: 2021-2024 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#ifndef ETEST_TEST_H_
#define ETEST_TEST_H_

#include "etest/etest2.h"

#include <functional>
#include <optional>
#include <source_location>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace etest {

[[nodiscard]] int run_all_tests(RunOptions const & = {}) noexcept;

void test(std::string name, std::function<void()> body) noexcept;
void disabled_test(std::string name, std::function<void()> body) noexcept;

// Weak test requirement. Allows the test to continue even if the check fails.
void expect(bool,
        std::optional<std::string_view> log_message = std::nullopt,
        std::source_location const &loc = std::source_location::current()) noexcept;

// Hard test requirement. Stops the test (using an exception) if the check fails.
void require(bool,
        std::optional<std::string_view> log_message = std::nullopt,
        std::source_location const &loc = std::source_location::current());

// Weak test requirement. Prints the types compared on failure (if printable).
template<Printable T, Printable U>
void expect_eq(T const &a,
        U const &b,
        std::optional<std::string_view> log_message = std::nullopt,
        std::source_location const &loc = std::source_location::current()) noexcept {
    if (a == b) {
        return;
    }

    std::stringstream ss;
    ss << a << " !=\n" << b;
    expect(false, log_message ? std::move(log_message) : std::move(ss).str(), loc);
}

template<typename T, typename U>
void expect_eq(T const &a,
        U const &b,
        std::optional<std::string_view> log_message = std::nullopt,
        std::source_location const &loc = std::source_location::current()) noexcept {
    expect(a == b, std::move(log_message), loc);
}

// Hard test requirement. Prints the types compared on failure (if printable).
template<Printable T, Printable U>
void require_eq(T const &a,
        U const &b,
        std::optional<std::string_view> log_message = std::nullopt,
        std::source_location const &loc = std::source_location::current()) {
    if (a == b) {
        return;
    }

    std::stringstream ss;
    ss << a << " !=\n" << b;
    require(false, log_message ? std::move(log_message) : std::move(ss).str(), loc);
}

template<typename T, typename U>
void require_eq(T const &a,
        U const &b,
        std::optional<std::string_view> log_message = std::nullopt,
        std::source_location const &loc = std::source_location::current()) {
    require(a == b, std::move(log_message), loc);
}

} // namespace etest

#endif
