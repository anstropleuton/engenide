/// @file plat_utils.hpp
/// Defines several platform-specific utilities.
/// @note This is a private header.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#pragma once

#include <unicode/ustring.h>

#include <cstdint>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

using native_char = std::conditional_t<sizeof(wchar_t) == 2, wchar_t, char>;

inline constexpr std::int32_t replacement_character{0xfffd};

auto write_text(std::string_view text) -> void;
// Same function as above where native_char is char
auto write_text(std::basic_string_view<native_char> text) -> void;

template <typename output_string, typename convert_function>
auto convert_text(convert_function const convert) {
    auto status{U_ZERO_ERROR};
    auto length{std::int32_t{}};
    convert(nullptr, 0, &length, &status);
    if (status != U_BUFFER_OVERFLOW_ERROR && U_FAILURE(status))
        throw std::runtime_error{u_errorName(status)};

    status = U_ZERO_ERROR;
    output_string output{};
    output.resize(static_cast<std::size_t>(length));
    convert(output.data(), length, &length, &status);
    if (U_FAILURE(status))
        throw std::runtime_error{u_errorName(status)};
    return output;
}

inline auto to_utf16(std::string_view const text) {
    return convert_text<std::u16string>(
        [&](char16_t *const     destination,
            std::int32_t const  capacity,
            std::int32_t *const length,
            UErrorCode *const   status) {
            u_strFromUTF8WithSub(destination, capacity, length, text.data(), static_cast<std::int32_t>(text.size()),
                replacement_character, nullptr, status);
        });
}

inline auto to_utf16(std::u32string_view const text) {
    return convert_text<std::u16string>(
        [&](char16_t *const     destination,
            std::int32_t const  capacity,
            std::int32_t *const length,
            UErrorCode *const   status) {
            u_strFromUTF32WithSub(destination, capacity, length, reinterpret_cast<UChar32 const *>(text.data()),
                static_cast<std::int32_t>(text.size()), replacement_character, nullptr, status);
        });
}

inline auto to_utf8(std::u16string_view const text) {
    return convert_text<std::string>([&](char *const         destination,
                                         std::int32_t const  capacity,
                                         std::int32_t *const length,
                                         UErrorCode *const   status) {
        u_strToUTF8WithSub(destination, capacity, length, text.data(), static_cast<std::int32_t>(text.size()),
            replacement_character, nullptr, status);
    });
}

inline auto to_utf8(std::u32string_view const text) {
    return to_utf8(to_utf16(text));
}

inline auto to_native(std::u16string_view const text) {
    if constexpr (std::is_same_v<native_char, wchar_t>)
        return std::wstring{reinterpret_cast<wchar_t const *>(text.data()), text.size()};
    else
        return to_utf8(text);
}

inline auto to_native(std::u32string_view const text) {
    if constexpr (std::is_same_v<native_char, wchar_t>)
        return to_native(std::u16string_view{to_utf16(text)});
    else
        return to_utf8(text);
}

inline auto to_native(std::u8string_view const text) {
    auto const bytes{std::string_view{reinterpret_cast<char const *>(text.data()), text.size()}};
    if constexpr (std::is_same_v<native_char, wchar_t>)
        return to_native(std::u16string_view{to_utf16(bytes)});
    else
        return std::string{bytes};
}

template <typename type>
inline constexpr bool is_u8_text{std::is_convertible_v<type const &, std::u8string_view>};

template <typename type>
inline constexpr bool is_u16_text{std::is_convertible_v<type const &, std::u16string_view>};

template <typename type>
inline constexpr bool is_u32_text{std::is_convertible_v<type const &, std::u32string_view>};

template <typename type>
decltype(auto) to_native_argument(type &&value) {
    if constexpr (is_u8_text<type>)
        return to_native(std::u8string_view{value});
    else if constexpr (is_u16_text<type>)
        return to_native(std::u16string_view{value});
    else if constexpr (is_u32_text<type>)
        return to_native(std::u32string_view{value});
    else
        return std::forward<type>(value);
}

template <typename string_type>
auto with_newline(string_type text) {
    text.push_back('\n');
    return text;
}

template <typename format_view, typename... argument_types>
auto format_native(format_view const format, argument_types &&... arguments) {
    std::tuple<decltype(to_native_argument(std::forward<argument_types>(arguments)))...> converted{
        to_native_argument(std::forward<argument_types>(arguments))...
    };

    return std::apply([&](auto &... native_arguments) {
        if constexpr (std::is_same_v<native_char, wchar_t>)
            return std::vformat(to_native(format), std::make_wformat_args(native_arguments...));
        else
            return std::vformat(to_native(format), std::make_format_args(native_arguments...));
    }, converted);
}

template <typename... argument_types>
auto u8print(std::format_string<argument_types...> const format, argument_types &&... arguments) {
    write_text(std::format(format, std::forward<argument_types>(arguments)...));
}

template <typename... argument_types>
auto u8println(std::format_string<argument_types...> const format, argument_types &&... arguments) {
    write_text(with_newline(std::format(format, std::forward<argument_types>(arguments)...)));
}

template <typename... argument_types>
auto u16print(std::u16string_view const format, argument_types &&... arguments) {
    write_text(format_native(format, arguments...));
}

template <typename... argument_types>
auto u16println(std::u16string_view const format, argument_types &&... arguments) {
    write_text(with_newline(format_native(format, arguments...)));
}

template <typename... argument_types>
auto u32print(std::u32string_view const format, argument_types &&... arguments) {
    write_text(format_native(format, arguments...));
}

template <typename... argument_types>
auto u32println(std::u32string_view const format, argument_types &&... arguments) {
    write_text(with_newline(format_native(format, arguments...)));
}
