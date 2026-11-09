/// @file
/// Defines several utilities.
/// @note This is a private header.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#pragma once

#include <filesystem>
#include <string>

inline auto path_to_utf8(std::filesystem::path const &path) {
    auto const string{path.u8string()};
    return std::string{reinterpret_cast<char const *>(string.data()), string.size()};
}
