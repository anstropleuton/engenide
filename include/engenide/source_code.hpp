/// @file source_code.hpp
/// Defines source code object for source of truth.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>

namespace eng {
    /// Location in the source code content.
    struct source_loc final {
        std::size_t begin{}; /// Begin (inclusive).
        std::size_t end{};   /// End (exclusive).
    };

    /// Source code object for source of truth.
    struct source_code final {
        std::u16string          content; /// Source code contents.
        std::vector<source_loc> lines;   /// Range of all the lines of the content (excludes newline).

        /// Create a source code from file content.
        [[nodiscard]] static auto load_file(std::filesystem::path const &filename) -> source_code;
    };
}
