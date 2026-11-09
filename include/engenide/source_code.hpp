/// @file
/// Source code object for source of truth.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#pragma once

#include <cstddef>
#include <cstdint>
#include <expected>
#include <filesystem>
#include <limits>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace eng {
    static constexpr std::size_t max_file_size{std::numeric_limits<std::int32_t>::max()};

    /// Source code loading error cant use reports (no "location" to store).
    struct source_code_error final {
        enum class error_kind : std::uint8_t {
            failed_to_open_file,
            failed_to_determine_file_size,
            file_size_too_large,        ///< Has too_large_size.
            failed_to_read_file,
            failed_to_detect_encoding,  ///< Has icu_error.
            unsupported_encoding,       ///< Has unsupported_encoding.
            failed_to_convert_encoding, ///< Has icu_error.
        };

        error_kind   error{};
        std::size_t  too_large_size{};
        std::int32_t icu_error{};
        std::string  unsupported_encoding;

        /// Get error message description.
        [[nodiscard]] auto message() const -> std::string;
    };

    struct source_code;

    struct source_loc final {
        std::size_t begin{}; ///< Begin (inclusive).
        std::size_t end{};   ///< End (exclusive).

        [[nodiscard]] constexpr auto size() const {
            return end - begin;
        }

        /// Get a fancy diagnosis preview of the text with line numbers.
        [[nodiscard]] auto preview(source_code const &code) const -> std::u32string;

        /// Get a view of the string content.
        [[nodiscard]] auto view(source_code const &code) const -> std::u32string_view;
    };

    struct source_code final {
        std::u32string          content;
        std::vector<source_loc> lines; ///< Range of all the lines of the content (excludes newline).

        [[nodiscard]] static auto load_file(std::filesystem::path const &filename)
            -> std::expected<source_code, source_code_error>;

        [[nodiscard]] auto get_row_col_index(std::size_t index) const noexcept
            -> std::optional<std::pair<std::size_t, std::size_t>>;
    };
}
