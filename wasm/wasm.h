// SPDX-FileCopyrightText: 2023-2024 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#ifndef WASM_WASM_H_
#define WASM_WASM_H_

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace wasm {

// https://webassembly.github.io/spec/core/binary/modules.html#indices
using TypeIdx = std::uint32_t;
using FuncIdx = std::uint32_t;

// https://webassembly.github.io/spec/core/syntax/types.html
struct ValueType {
    enum Kind : std::uint8_t {
        // Number types.
        Int32,
        Int64,
        Float32,
        Float64,

        // Vector types.
        Vector128,

        // Reference types.
        FunctionReference,
        ExternReference,
    };

    Kind kind{};

    [[nodiscard]] bool operator==(ValueType const &) const = default;
};

// https://webassembly.github.io/spec/core/binary/types.html#result-types
using ResultType = std::vector<ValueType>;

// https://webassembly.github.io/spec/core/binary/types.html#function-types
struct FunctionType {
    ResultType parameters;
    ResultType results;

    [[nodiscard]] bool operator==(FunctionType const &) const = default;
};

// https://webassembly.github.io/spec/core/binary/modules.html#type-section
struct TypeSection {
    std::vector<FunctionType> types;

    [[nodiscard]] bool operator==(TypeSection const &) const = default;
};

// https://webassembly.github.io/spec/core/binary/modules.html#function-section
struct FunctionSection {
    std::vector<TypeIdx> type_indices;

    [[nodiscard]] bool operator==(FunctionSection const &) const = default;
};

// https://webassembly.github.io/spec/core/binary/types.html#limits
struct Limits {
    std::uint32_t min{};
    std::optional<std::uint32_t> max{};

    [[nodiscard]] bool operator==(Limits const &) const = default;
};

// https://webassembly.github.io/spec/core/binary/types.html#table-types
struct TableType {
    ValueType element_type{};
    Limits limits{};

    [[nodiscard]] bool operator==(TableType const &) const = default;
};

// https://webassembly.github.io/spec/core/binary/modules.html#table-section
struct TableSection {
    std::vector<TableType> tables{};

    [[nodiscard]] bool operator==(TableSection const &) const = default;
};

// https://webassembly.github.io/spec/core/binary/types.html#memory-types
using MemType = Limits;

// https://webassembly.github.io/spec/core/binary/modules.html#memory-section
struct MemorySection {
    std::vector<MemType> memories{};

    [[nodiscard]] bool operator==(MemorySection const &) const = default;
};

// https://webassembly.github.io/spec/core/binary/modules.html#binary-export
struct Export {
    enum class Type { Function = 0, Table = 1, Memory = 2, Global = 3 };

    std::string name{};
    Type type{};
    std::uint32_t index{};

    [[nodiscard]] bool operator==(Export const &) const = default;
};

// https://webassembly.github.io/spec/core/binary/modules.html#binary-exportsec
struct ExportSection {
    std::vector<Export> exports{};

    [[nodiscard]] bool operator==(ExportSection const &) const = default;
};

struct StartSection {
    FuncIdx start{};

    [[nodiscard]] bool operator==(StartSection const &) const = default;
};

// https://webassembly.github.io/spec/core/binary/modules.html#binary-codesec
struct CodeEntry {
    struct Local {
        std::uint32_t count{};
        ValueType type{};

        [[nodiscard]] bool operator==(Local const &) const = default;
    };

    std::vector<std::uint8_t> code{};
    std::vector<Local> locals{};

    [[nodiscard]] bool operator==(CodeEntry const &) const = default;
};
struct CodeSection {
    std::vector<CodeEntry> entries{};

    [[nodiscard]] bool operator==(CodeSection const &) const = default;
};

// https://webassembly.github.io/spec/core/syntax/modules.html
struct Module {
    // TODO(robinlinden): custom_sections
    std::optional<TypeSection> type_section{};
    // TODO(robinlinden): import_section
    std::optional<FunctionSection> function_section{};
    std::optional<TableSection> table_section{};
    std::optional<MemorySection> memory_section{};
    // TODO(robinlinden): global_section
    std::optional<ExportSection> export_section{};
    std::optional<StartSection> start_section{};
    // TODO(robinlinden): element_section
    std::optional<CodeSection> code_section{};
    // TODO(robinlinden): data_section
    // TODO(robinlinden): data_count_section

    [[nodiscard]] bool operator==(Module const &) const = default;
};

} // namespace wasm

#endif
