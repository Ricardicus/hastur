// SPDX-FileCopyrightText: 2021-2023 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "etest/etest.h"

#include "etest/cxx_compat.h"
#include "etest/etest2.h"

#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

namespace etest {
namespace {
Suite &registry() {
    static Suite test_registry{};
    return test_registry;
}

struct DummyActions : public IActions {
    void expect(bool, std::optional<std::string_view>, etest::source_location const &) noexcept override {}
    void require(bool, std::optional<std::string_view>, etest::source_location const &) override {}
};
DummyActions dummy_actions;
std::reference_wrapper<IActions> current_actions{dummy_actions};
} // namespace

int run_all_tests(RunOptions const &opts) noexcept {
    return registry().run(opts);
}

void test(std::string name, std::function<void()> body) noexcept {
    registry().add_test(std::move(name), [body = std::move(body)](IActions &a) {
        current_actions = a;
        body();
    });
}

void disabled_test(std::string name, std::function<void()> body) noexcept {
    registry().disabled_test(std::move(name), [body = std::move(body)](IActions &a) {
        current_actions = a;
        body();
    });
}

void expect(bool b, std::optional<std::string_view> log_message, etest::source_location const &loc) noexcept {
    current_actions.get().expect(b, std::move(log_message), loc);
}

void require(bool b, std::optional<std::string_view> log_message, etest::source_location const &loc) {
    current_actions.get().require(b, std::move(log_message), loc);
}

} // namespace etest
