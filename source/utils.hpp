/// @file utils.hpp
/// Defines several utilities.
/// @note This is a private header.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#pragma once

inline auto path_to_utf8(std::filesystem::path const &path) {
    auto const string{path.u8string()};
    return std::string{reinterpret_cast<char const *>(string.data()), string.size()};
}

template <typename... args_type>
[[noreturn]] auto throw_runtime(std::format_string<args_type...> fmt, args_type &&... args) {
    throw std::runtime_error(std::format(fmt, std::forward<args_type>(args)...));
}

template <typename... args_type>
[[noreturn]] auto throw_logic(std::format_string<args_type...> fmt, args_type &&... args) {
    throw std::logic_error(std::format(fmt, std::forward<args_type>(args)...));
}

template <typename... args_type>
[[noreturn]] auto throw_argument(std::format_string<args_type...> fmt, args_type &&... args) {
    throw std::invalid_argument(std::format(fmt, std::forward<args_type>(args)...));
}

template <typename... args_type>
[[noreturn]] auto throw_oor(std::format_string<args_type...> fmt, args_type &&... args) {
    throw std::out_of_range(std::format(fmt, std::forward<args_type>(args)...));
}
