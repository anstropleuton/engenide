/// @file plat_utils.cpp
/// Implementation for @ref plat_utils.hpp.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#include "plat_utils.hpp"

#ifdef _WIN32
#include <windows.h>
#elifdef __linux__
#include <cerrno>
#include <unistd.h>
#endif

#ifdef _WIN32

static auto is_console(HANDLE const handle) -> bool {
    auto mode{DWORD{}};
    return GetConsoleMode(handle, &mode) != 0;
}

static auto write_file(HANDLE const handle, std::string_view const bytes) -> void {
    auto remaining{bytes};
    while (!remaining.empty()) {
        auto       written{DWORD{}};
        auto const count{static_cast<DWORD>(remaining.size())};
        if (!static_cast<bool>(WriteFile(handle, remaining.data(), count, &written, nullptr)) || written == 0)
            return;
        remaining.remove_prefix(written);
    }
}

static auto write_console(HANDLE const handle, std::wstring_view const text) -> void {
    auto remaining{text};
    while (!remaining.empty()) {
        auto       written{DWORD{}};
        auto const count{static_cast<DWORD>(remaining.size())};
        if (!static_cast<bool>(WriteConsoleW(handle, remaining.data(), count, &written, nullptr)) || written == 0)
            return;
        remaining.remove_prefix(written);
    }
}

auto write_text(std::string_view const text) -> void {
    auto *const handle{GetStdHandle(STD_OUTPUT_HANDLE)};
    if (!is_console(handle)) {
        write_file(handle, text);
        return;
    }
    auto const utf16{to_utf16(text)};
    write_console(handle, std::wstring_view{reinterpret_cast<wchar_t const *>(utf16.data()), utf16.size()});
}

auto write_text(std::wstring_view const text) -> void {
    auto *const handle{GetStdHandle(STD_OUTPUT_HANDLE)};
    if (is_console(handle)) {
        write_console(handle, text);
        return;
    }
    write_file(handle, to_utf8(std::u16string_view{reinterpret_cast<char16_t const *>(text.data()), text.size()}));
}

#else

auto write_text(std::string_view const text) -> void {
    auto remaining{text};
    while (!remaining.empty()) {
        auto const written{write(STDOUT_FILENO, remaining.data(), remaining.size())};
        if (written < 0) {
            if (errno == EINTR)
                continue;
            return;
        }
        remaining.remove_prefix(static_cast<std::size_t>(written));
    }
}

#endif
