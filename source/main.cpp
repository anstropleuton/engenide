/// @file main.cpp
/// Engenide CLI entry point (eng.exe).
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#include <print>

#include "eng_config.hpp"
#include "plat_utils.hpp"
#include "CLI/CLI.hpp"
#include "engenide/source_code.hpp"

[[nodiscard]] auto main(int const argc, char const *const argv[]) -> int { // NOLINT(*-exception-escape)
    CLI::App app{"Engenide - a general-purpose systems language between C++ and Rust."};

    app.name("eng");
    app.set_version_flag("-V,--version", eng::engenide_version_str);
    app.require_subcommand(1);
    app.failure_message(CLI::FailureMessage::help);

    auto *process = app.add_subcommand("process", "Process an Engenide source code");

    std::filesystem::path source;

    process->add_option("source", source, "Engenide source file")
           ->required()
           ->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    if (*process) {
        auto const code{eng::source_code::load_file(source)};

        for (auto const [begin, end] : code.lines)
            u16println(u"{:>4}-{:<4}: {}", begin, end, std::u16string_view{code.content}.substr(begin, end - begin));
    }
}
