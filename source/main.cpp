/// @file
/// Engenide CLI entry point (eng.exe).
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#include "CLI/CLI.hpp"
#include "eng_config.hpp"
#include "engenide/lexer.hpp"
#include "engenide/source_code.hpp"
#include "plat_utils.hpp"

#include <filesystem>
#include <print>

[[nodiscard]] auto main(int const argc, char const *const argv[]) -> int {
    CLI::App app{"Engenide - a general-purpose systems language between C++ and Rust."};

    app.name("eng");
    app.set_version_flag("-V,--version", eng::engenide_version_str);
    app.require_subcommand(1);
    app.failure_message(CLI::FailureMessage::help);

    auto *process{app.add_subcommand("process", "Process an Engenide source code")};

    std::filesystem::path source;

    process->add_option("source", source, "Engenide source file")->required()->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    if (*process) {
        auto const maybe_code{eng::source_code::load_file(source)};

        if (!maybe_code) {
            std::println("{}", maybe_code.error().message());
            return 1;
        }

        auto const &code{maybe_code.value()};

        auto const lex_scan_result{eng::lex_scan(code)};

        for (auto const raw_token : lex_scan_result.raw_tokens) {
            u32print(U"{}", raw_token.loc.view(code));
        }
    }
}
