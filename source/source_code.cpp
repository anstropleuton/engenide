/// @file source_code.cpp
/// Implementation for @ref source_code.hpp.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#include "engenide/source_code.hpp"

#include <cstring>
#include <fstream>
#include <limits>
#include <memory>

#include "utils.hpp"
#include "unicode/ucnv.h"
#include "unicode/ucnv_err.h"
#include "unicode/utypes.h"

auto eng::source_code::load_file(std::filesystem::path const &filename) -> source_code {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(filename, std::ios::binary);

    std::string const raw{std::istreambuf_iterator{file}, {}};

    if (constexpr auto int_max{std::numeric_limits<std::int32_t>::max()}; raw.size() > int_max)
        throw_runtime("{}: File too large: must be <= {}",
            path_to_utf8(filename), int_max);

    // Find BOM
    std::int32_t sign_length{};
    UErrorCode   error_code{};

    char const *encoding{
        ucnv_detectUnicodeSignature(raw.c_str(), static_cast<std::int32_t>(raw.size()), &sign_length, &error_code)
    };

    if (static_cast<bool>(U_FAILURE(error_code)))
        throw_runtime("{}: Failed to detect encoding: {}; must be UTF-8/16/32",
            path_to_utf8(filename), u_errorName(error_code));
    error_code = U_ZERO_ERROR;

    if (encoding != nullptr &&
        std::strcmp(encoding, "UTF-8") != 0 &&
        std::strcmp(encoding, "UTF-16BE") != 0 &&
        std::strcmp(encoding, "UTF-16LE") != 0 &&
        std::strcmp(encoding, "UTF-32BE") != 0 &&
        std::strcmp(encoding, "UTF-32LE") != 0)
        throw_runtime("{}: Unsupported encoding: {}; must be UTF-8/16/32",
            path_to_utf8(filename), encoding);

    // Try UTF-8 if no BOM is present
    if (encoding == nullptr) encoding = "UTF-8";

    // Convert UTF-* to UTF-16
    std::unique_ptr<UConverter, decltype(&ucnv_close)> const converter{ucnv_open(encoding, &error_code), &ucnv_close};

    if (static_cast<bool>(U_FAILURE(error_code)))
        throw_runtime("{}: Failed to create converter: {}",
            path_to_utf8(filename), u_errorName(error_code));
    error_code = U_ZERO_ERROR;

    ucnv_setToUCallBack(converter.get(), UCNV_TO_U_CALLBACK_STOP, nullptr, nullptr, nullptr, &error_code);

    if (static_cast<bool>(U_FAILURE(error_code)))
        throw_runtime("{}: Failed to configure converter: {}",
            path_to_utf8(filename), u_errorName(error_code));
    error_code = U_ZERO_ERROR;

    char const *const  input{raw.data() + sign_length};
    std::int32_t const input_size{static_cast<std::int32_t>(raw.size()) - sign_length};

    source_code code;
    code.content.resize(static_cast<std::size_t>(input_size) + 1);

    std::int32_t const converted{
        ucnv_toUChars(converter.get(), code.content.data(), static_cast<std::int32_t>(code.content.size()), input,
            input_size, &error_code)
    };

    if (static_cast<bool>(U_FAILURE(error_code)))
        throw_runtime("{}: Invalid encoding: {}; must be UTF-8/16/32",
            path_to_utf8(filename), u_errorName(error_code));
    error_code = U_ZERO_ERROR;

    code.content.resize(converted);

    // Normalize CRLF -> LF and build line ranges
    std::size_t write{};
    std::size_t line_begin{};

    for (std::size_t read{}; read < code.content.size(); ++read, ++write) {
        if (code.content.at(read) == u'\r' &&
            read + 1 < code.content.size() &&
            code.content.at(read + 1) == u'\n')
            ++read;

        code.content.at(write) = code.content.at(read);

        if (code.content.at(write) == u'\n') {
            code.lines.emplace_back(line_begin, write);
            line_begin = write + 1;
        }
    }

    if (line_begin < write)
        code.lines.emplace_back(line_begin, write);

    code.content.resize(write);

    return code;
}
