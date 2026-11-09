/// @file
/// Reports for diagnosis.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#pragma once

#include "source_code.hpp"

#include <cstdint>
#include <format> // IWYU pragma: keep
#include <memory> // IWYU pragma: keep
#include <string>
#include <utility>

namespace eng {
    enum class severity_type : std::uint8_t { note, warning, error, help };

    struct report {
        /// Name of the derived report class (e.g., unused_function_parameter, missing_statement_semicolon).
        /// @todo Replace 'e.g.' names with real names.
        std::string   class_name;
        severity_type severity;
        source_loc    location;

        /// Get error message description.
        /// @note Does not include location preview.
        [[nodiscard]] virtual auto message() const -> std::string = 0;

        virtual ~report() = default;

    protected:
        report(std::string class_name, severity_type const severity, source_loc const location)
            : class_name{std::move(class_name)}, severity{severity}, location{location} {}

        report(report const &)                     = default;
        auto operator=(report const &) -> report & = default;
        report(report &&)                          = default;
        auto operator=(report &&) -> report &      = default;
    };

#define ENG_UNPAREN(...) __VA_ARGS__

    // clang-format off

/// Gotta create tons of report types
#define ENG_REPORT(NAME, SEVERITY, FIELDS, PARAMS, INITS, FORMAT)                           \
    struct NAME final : report {                                                            \
        explicit NAME(source_loc location ENG_UNPAREN PARAMS)                               \
            : report(#NAME, severity_type::SEVERITY, location) ENG_UNPAREN INITS {}         \
                                                                                            \
        ENG_UNPAREN FIELDS                                                                  \
                                                                                            \
        [[nodiscard]] auto message() const -> std::string override {                        \
            return std::format FORMAT;                                                      \
        }                                                                                   \
    };                                                                                      \
                                                                                            \
    template <typename... args_type>                                                        \
    [[nodiscard]] inline auto make_##NAME(args_type &&...args) -> std::unique_ptr<report> { \
        return std::make_unique<NAME>(std::forward<args_type>(args)...);                    \
    }

    // clang-format on
}
