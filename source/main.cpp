/// @file main.cpp
/// Engenide CLI entry point (eng.exe).
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#include <print>

#include "engenide/source_code.hpp"

[[nodiscard]] auto main() -> int { // NOLINT(*-exception-escape)
    std::println("cwd: {}", std::filesystem::current_path().string());

    auto const code{eng::source_code::load_file("test.eng")};

    std::println("content: {}", code.content.size());
    std::println("lines: {}", code.lines.size());

    for (auto const line : code.lines)
        std::println("[{}, {})", line.begin, line.end);
}
