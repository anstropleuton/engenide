/// @file
/// Internal Engenide Engine Error & Recovery
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#pragma once

#include <concepts>
#include <cstddef>
#include <exception>
#include <format>
#include <functional>
#include <new>
#include <stacktrace>
#include <string>
#include <type_traits>

#if defined(__GNUC__) || defined(__clang__)
#    define ENG_FUNC_SIG __PRETTY_FUNCTION__
#elifdef _MSC_VER
#    define ENG_FUNC_SIG __FUNCSIG__
#else
#    define ENG_FUNC_SIG __func__
#endif

namespace eng {
    constexpr std::size_t internal_error_length{1024};

    /// Internal error thrown from public functions.
    class internal_error final : public std::exception {
        std::string     message_;
        std::stacktrace trace_; ///< Trace may not tell the whole story...

    public:
        template <typename... args_type>
        explicit internal_error(std::format_string<args_type...> format, args_type &&...args)
            : trace_(std::stacktrace::current()) {
            message_.append("Internal Engenide Engine Error: ");
            message_.append(std::format(format, std::forward<args_type>(args)...));
            message_.append("\n");
            message_.append(std::to_string(trace_));
            message_.append("\n");
            message_.append("Please report this issue at https://github.com/anstropleuton/engenide/issues");
        }

        [[nodiscard]] auto what() const -> char const * override {
            return message_.c_str();
        }

        [[nodiscard]] auto trace() const -> std::stacktrace const & {
            return trace_;
        }
    };

    template <typename function_type>
        requires std::invocable<function_type, void> && std::same_as<std::invoke_result_t<function_type, void>, void>
    [[nodiscard]] inline auto wrap_internal_error(function_type &&function) try {
        std::invoke(std::forward(function));
    } catch (eng::internal_error const &) {
        throw;
    } catch (std::bad_alloc const &) {
        throw;
    } catch (std::exception const &error) {
        throw eng::internal_error("Exception thrown from lex_scanner: {}", error.what());
    }
}
