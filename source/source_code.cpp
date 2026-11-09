/// @file
/// Implementation for @ref source_code.hpp.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#include "engenide/source_code.hpp"

#include <unicode/ucnv.h>
#include <unicode/ucnv_err.h>
#include <unicode/utypes.h>

#include <algorithm>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <expected>
#include <filesystem>
#include <format>
#include <fstream>
#include <ios>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

auto eng::source_code_error::message() const -> std::string {
    switch (error) {
        case error_kind::failed_to_open_file: return std::format("Failed to open file"); break;
        case error_kind::failed_to_determine_file_size: return std::format("Failed to determine file size"); break;
        case error_kind::file_size_too_large:
            return std::format("File size too large: {} > {}", too_large_size, max_file_size);
            break;
        case error_kind::failed_to_read_file: return std::format("Failed to read file"); break;
        case error_kind::failed_to_detect_encoding:
            return std::format("Failed to detect encoding: ICU error: {}: {}", icu_error,
                u_errorName(static_cast<UErrorCode>(icu_error)));
            break;
        case error_kind::unsupported_encoding:
            return std::format("Unsupported encoding: {}", unsupported_encoding);
            break;
        case error_kind::failed_to_convert_encoding:
            return std::format("Failed to convert encoding: ICU error: {}: {}", icu_error,
                u_errorName(static_cast<UErrorCode>(icu_error)));
            break;
    }
}

[[nodiscard]] auto eng::source_loc::preview(source_code const &code) const -> std::u32string {
    std::size_t const last{size() == 0 ? begin : end - 1};

    auto const first_pos{code.get_row_col_index(begin)};
    auto const last_pos{code.get_row_col_index(last)};

    if (!first_pos.has_value() || !last_pos.has_value()) return {};

    auto const [first_row, first_col]{first_pos.value()};
    auto const [last_row, last_col]{last_pos.value()};

    std::size_t const width{std::to_string(code.lines.size()).size()};

    std::u32string result{};

    for (std::size_t row{first_row}; row <= last_row; ++row) {
        std::u32string_view const line{code.lines.at(row).view(code)};
        std::string const         number{std::to_string(row + 1)};

        result.push_back(U' ');
        result.append(width - number.size(), U' ');
        result.append(number.begin(), number.end());
        result.append(U" | ");
        result.append(line);
        result.push_back(U'\n');

        result.push_back(U' ');
        result.append(width, U' ');
        result.append(U" | ");

        std::size_t const from{row == first_row ? first_col : 0};
        std::size_t const to{row == last_row ? last_col : (line.empty() ? 0 : line.size() - 1)};

        for (std::size_t col{}; col < from; ++col) {
            result.push_back(col < line.size() && line.at(col) == U'\t' ? U'\t' : U' ');
        }

        result.push_back(row == first_row ? U'^' : U'~');
        result.append(to > from ? to - from : 0, U'~');
        result.push_back(U'\n');
    }

    return result;
}

[[nodiscard]] auto eng::source_loc::view(source_code const &code) const -> std::u32string_view {
    return std::u32string_view{code.content}.substr(begin, size());
}

namespace {
    using converter_ptr = std::unique_ptr<UConverter, decltype(&ucnv_close)>;

    static_assert(sizeof(char32_t) == 4);
    static_assert(std::endian::native == std::endian::little || std::endian::native == std::endian::big);

    constexpr char const *utf32_native{std::endian::native == std::endian::little ? "UTF-32LE" : "UTF-32BE"};
}

auto eng::source_code::load_file(std::filesystem::path const &filename)
    -> std::expected<source_code, source_code_error> {
    std::ifstream file{filename, std::ios::binary | std::ios::ate};

    if (!file) return std::unexpected(source_code_error{.error{source_code_error::error_kind::failed_to_open_file}});

    auto const end_pos{file.tellg()};

    if (end_pos < 0)
        return std::unexpected(source_code_error{.error{source_code_error::error_kind::failed_to_determine_file_size}});

    auto const file_size{static_cast<std::size_t>(static_cast<std::streamoff>(end_pos))};

    if (file_size > max_file_size)
        return std::unexpected(
            source_code_error{.error{source_code_error::error_kind::file_size_too_large}, .too_large_size{file_size}});

    std::string raw(file_size, '\0');

    file.seekg(0);
    if (!file.read(raw.data(), static_cast<std::streamsize>(raw.size())))
        return std::unexpected(source_code_error{.error{source_code_error::error_kind::failed_to_read_file}});

    std::int32_t sign_length{};
    UErrorCode   error_code{U_ZERO_ERROR};

    char const *encoding{
        ucnv_detectUnicodeSignature(raw.c_str(), static_cast<std::int32_t>(raw.size()), &sign_length, &error_code),
    };

    if (U_FAILURE(error_code)) {
        return std::unexpected(source_code_error{
            .error{source_code_error::error_kind::failed_to_detect_encoding},
            .icu_error{static_cast<std::int32_t>(error_code)},
        });
    }

    if (encoding != nullptr &&
        std::strcmp(encoding, "UTF-8") != 0 &&
        std::strcmp(encoding, "UTF-16BE") != 0 &&
        std::strcmp(encoding, "UTF-16LE") != 0 &&
        std::strcmp(encoding, "UTF-32BE") != 0 &&
        std::strcmp(encoding, "UTF-32LE") != 0) {
        return std::unexpected(source_code_error{
            .error{source_code_error::error_kind::unsupported_encoding},
            .unsupported_encoding{encoding},
        });
    }

    // Without a BOM, assume UTF-8 (UTF-16/32 files must carry a BOM)
    if (encoding == nullptr) encoding = "UTF-8";

    std::size_t unit_size{1};
    if (std::strncmp(encoding, "UTF-16", 6) == 0) unit_size = 2;
    else if (std::strncmp(encoding, "UTF-32", 6) == 0) unit_size = 4;

    converter_ptr const from_converter{ucnv_open(encoding, &error_code), &ucnv_close};

    if (U_FAILURE(error_code)) {
        return std::unexpected(source_code_error{
            .error{source_code_error::error_kind::failed_to_convert_encoding},
            .icu_error{static_cast<std::int32_t>(error_code)},
        });
    }

    ucnv_setToUCallBack(from_converter.get(), UCNV_TO_U_CALLBACK_STOP, nullptr, nullptr, nullptr, &error_code);

    if (U_FAILURE(error_code)) {
        return std::unexpected(source_code_error{
            .error{source_code_error::error_kind::failed_to_convert_encoding},
            .icu_error{static_cast<std::int32_t>(error_code)},
        });
    }

    converter_ptr const to_converter{ucnv_open(utf32_native, &error_code), &ucnv_close};

    if (U_FAILURE(error_code)) {
        return std::unexpected(source_code_error{
            .error{source_code_error::error_kind::failed_to_convert_encoding},
            .icu_error{static_cast<std::int32_t>(error_code)},
        });
    }

    ucnv_setFromUCallBack(to_converter.get(), UCNV_FROM_U_CALLBACK_STOP, nullptr, nullptr, nullptr, &error_code);

    if (U_FAILURE(error_code)) {
        return std::unexpected(source_code_error{
            .error{source_code_error::error_kind::failed_to_convert_encoding},
            .icu_error{static_cast<std::int32_t>(error_code)},
        });
    }

    char const *const  input{raw.data() + sign_length};
    std::int32_t const input_size{static_cast<std::int32_t>(raw.size()) - sign_length};

    source_code code;
    code.content.resize(static_cast<std::size_t>(input_size) / unit_size);

    char       *target{reinterpret_cast<char *>(code.content.data())};
    char const *target_begin{target};
    char const *target_limit{target + code.content.size() * sizeof(char32_t)};
    char const *source{input};

    ucnv_convertEx(to_converter.get(), from_converter.get(), &target, target_limit, &source, input + input_size,
        nullptr, nullptr, nullptr, nullptr, true, true, &error_code);

    if (static_cast<bool>(U_FAILURE(error_code))) {
        return std::unexpected(source_code_error{
            .error{source_code_error::error_kind::failed_to_convert_encoding},
            .icu_error{static_cast<std::int32_t>(error_code)},
        });
    }

    auto &content{code.content};
    content.resize(static_cast<std::size_t>(target - target_begin) / sizeof(char32_t));

    // Normalize CRLF -> LF in place and build line ranges (end is exclusive, newline not included)
    std::size_t write{};
    std::size_t line_begin{};

    for (std::size_t read{}; read < content.size(); ++read, ++write) {
        if (content.at(read) == U'\r' && read + 1 < content.size() && content.at(read + 1) == U'\n') ++read;

        content.at(write) = content.at(read);

        if (content.at(write) == U'\n') {
            code.lines.emplace_back(line_begin, write);
            line_begin = write + 1;
        }
    }

    if (line_begin < write) code.lines.emplace_back(line_begin, write);

    content.resize(write);

    return code;
}

[[nodiscard]] auto eng::source_code::get_row_col_index(std::size_t const index) const noexcept
    -> std::optional<std::pair<std::size_t, std::size_t>> {
    auto const upper{std::ranges::upper_bound(lines, index, {}, &source_loc::begin)};

    if (upper == lines.begin()) return std::nullopt;

    auto const line{std::prev(upper)};

    if (index > line->end) return std::nullopt;

    return std::pair{static_cast<std::size_t>(line - lines.begin()), index - line->begin};
}
