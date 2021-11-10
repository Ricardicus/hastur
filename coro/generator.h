// SPDX-FileCopyrightText: 2021 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#ifndef CORO_GENERATOR_H_
#define CORO_GENERATOR_H_

#include <cassert>
#include <concepts>
#include <coroutine>
#include <optional>
#include <utility>

namespace coro {

template<std::movable T>
class Generator {
public:
    struct promise_type {
        std::optional<T> maybe_value;

        Generator<T> get_return_object() { return Generator{Handle::from_promise(*this)}; }

        void return_void() {}

        static std::suspend_never initial_suspend() noexcept { return {}; }
        static std::suspend_always final_suspend() noexcept { return {}; }

        std::suspend_always yield_value(T value) noexcept {
            maybe_value = std::move(value);
            return {};
        }

        static void unhandled_exception() { throw; }
    };

    using Handle = std::coroutine_handle<promise_type>;

    explicit Generator(Handle handle) : handle_(std::move(handle)) {}
    ~Generator() {
        if (handle_) {
            handle_.destroy();
        }
    }

    Generator(Generator const &) = delete;
    Generator &operator=(Generator const &) = delete;

    Generator(Generator &&other) noexcept : handle_{std::exchange(other.handle_, {})} {}
    Generator &operator=(Generator &&other) noexcept {
        if (this != &other) {
            handle_ = std::exchange(other.handle_, {});
        }

        return *this;
    }

    bool has_next() const { return !handle_.done(); }
    T next() {
        assert(has_next());
        auto v = std::move(*handle_.promise().maybe_value);
        handle_.resume();
        return v;
    }

private:
    Handle handle_{};
};

} // namespace coro

#endif
