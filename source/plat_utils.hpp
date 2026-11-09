/// @file
/// Defines several platform-specific utilities.
/// @note This is a private header.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#pragma once

#include <unicode/umachine.h>
#include <unicode/urename.h>
#include <unicode/ustring.h>
#include <unicode/utypes.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

#ifdef _WIN32
using native_char = wchar_t;
#else
using native_char = char;
#endif

inline constexpr std::int32_t replacement_character{0xfffd};

auto write_text(std::string_view text) -> void;

#ifdef _WIN32
auto write_text(std::wstring_view text) -> void;
#endif

template <typename output_string, typename convert_function> auto convert_text(convert_function const convert) {
    auto status{U_ZERO_ERROR};
    auto length{std::int32_t{}};
    convert(nullptr, 0, &length, &status);
    if (status != U_BUFFER_OVERFLOW_ERROR && U_FAILURE(status)) throw std::runtime_error{u_errorName(status)};

    status = U_ZERO_ERROR;
    output_string output{};
    output.resize(static_cast<std::size_t>(length));
    convert(output.data(), length, &length, &status);
    if (U_FAILURE(status)) throw std::runtime_error{u_errorName(status)};
    return output;
}

inline auto to_utf16(std::string_view const text) {
    return convert_text<std::u16string>([&](char16_t *const destination, std::int32_t const capacity,
                                            std::int32_t *const length, UErrorCode *const status) -> void {
        u_strFromUTF8WithSub(destination, capacity, length, text.data(), static_cast<std::int32_t>(text.size()),
            replacement_character, nullptr, status);
    });
}

inline auto to_utf16(std::u32string_view const text) {
    return convert_text<std::u16string>([&](char16_t *const destination, std::int32_t const capacity,
                                            std::int32_t *const length, UErrorCode *const status) -> void {
        u_strFromUTF32WithSub(destination, capacity, length, reinterpret_cast<UChar32 const *>(text.data()),
            static_cast<std::int32_t>(text.size()), replacement_character, nullptr, status);
    });
}

inline auto to_utf8(std::u16string_view const text) {
    return convert_text<std::string>([&](char *const destination, std::int32_t const capacity,
                                         std::int32_t *const length, UErrorCode *const status) -> void {
        u_strToUTF8WithSub(destination, capacity, length, text.data(), static_cast<std::int32_t>(text.size()),
            replacement_character, nullptr, status);
    });
}

inline auto to_utf8(std::u32string_view const text) {
    return to_utf8(to_utf16(text));
}

template <typename char_type = native_char> auto to_native(std::u16string_view const text) {
    if constexpr (std::is_same_v<char_type, wchar_t>)
        return std::wstring{reinterpret_cast<wchar_t const *>(text.data()), text.size()};
    else return to_utf8(text);
}

template <typename char_type = native_char> auto to_native(std::u32string_view const text) {
    if constexpr (std::is_same_v<char_type, wchar_t>) return to_native<char_type>(std::u16string_view{to_utf16(text)});
    else return to_utf8(text);
}

template <typename char_type = native_char> auto to_native(std::string_view const text) {
    if constexpr (std::is_same_v<char_type, wchar_t>) return to_native<char_type>(std::u16string_view{to_utf16(text)});
    else return std::string{text};
}

template <typename char_type = native_char> auto to_native(std::u8string_view const text) {
    return to_native<char_type>(std::string_view{reinterpret_cast<char const *>(text.data()), text.size()});
}

template <typename type> inline constexpr bool is_u8_text{std::is_convertible_v<type const &, std::u8string_view>};

template <typename type> inline constexpr bool is_u16_text{std::is_convertible_v<type const &, std::u16string_view>};

template <typename type> inline constexpr bool is_u32_text{std::is_convertible_v<type const &, std::u32string_view>};

template <typename type> inline constexpr bool is_narrow_text{std::is_convertible_v<type const &, std::string_view>};

template <typename type> auto to_native_argument(type &&value) -> decltype(auto) {
    if constexpr (is_u8_text<type>) return to_native(std::u8string_view{value});
    else if constexpr (is_u16_text<type>) return to_native(std::u16string_view{value});
    else if constexpr (is_u32_text<type>) return to_native(std::u32string_view{value});
    else if constexpr (is_narrow_text<type> && std::is_same_v<native_char, wchar_t>)
        return to_native(std::string_view{value});
    else return std::forward<type>(value);
}

template <typename string_type> auto with_newline(string_type text) {
    text.push_back('\n');
    return text;
}

template <typename format_view, typename... argument_types>
auto format_native(format_view const format, argument_types &&...arguments) {
    std::tuple<decltype(to_native_argument(std::forward<argument_types>(arguments)))...> const converted{
        to_native_argument(std::forward<argument_types>(arguments))...};

    return std::apply(
        [&](auto &...native_arguments) -> auto {
            if constexpr (std::is_same_v<native_char, wchar_t>)
                return std::vformat(to_native(format), std::make_wformat_args(native_arguments...));
            else return std::vformat(to_native(format), std::make_format_args(native_arguments...));
        },
        converted);
}

/// The type an argument has after `to_native_argument` converts it, used for compile-time format checking.
template <typename type>
using checked_argument = std::remove_cvref_t<decltype(to_native_argument(std::declval<type>()))>;

/// Compile-time checked format string for UTF-16 and UTF-32 literals.
///
/// Like `std::format_string`, but for `char16_t` and `char32_t`. The literal is validated at compile time by
/// building a `std::basic_format_string` of `native_char` from its ASCII skeleton. Only the structure of the format
/// string (`{}`, `:`, digits, etc.) matters for validation, so any non-ASCII character is replaced with `?`, which
/// is still a valid literal or fill character.
template <typename char_type, typename... argument_types> struct basic_unicode_format_string {
    std::basic_string_view<char_type> text;

    template <std::size_t size>
    // NOLINTNEXTLINE(*-explicit-constructor, *-avoid-c-arrays)
    consteval basic_unicode_format_string(char_type const (&literal)[size]) : text{literal, size - 1} {
        std::array<native_char, size> ascii{};
        for (std::size_t index{}; index < size; ++index)
            ascii.at(index) =
                literal[index] < 0x80 ? static_cast<native_char>(literal[index]) : static_cast<native_char>('?');

        std::basic_string_view<native_char> const                                          view{ascii.data(), size - 1};
        std::basic_format_string<native_char, checked_argument<argument_types> &...> const check{view};
        (void)check;
    }
};

template <typename... argument_types>
using u16_format_string = basic_unicode_format_string<char16_t, std::type_identity_t<argument_types>...>;

template <typename... argument_types>
using u32_format_string = basic_unicode_format_string<char32_t, std::type_identity_t<argument_types>...>;

template <typename... argument_types>
auto u8print(std::format_string<argument_types...> const format, argument_types &&...arguments) {
    write_text(std::format(format, std::forward<argument_types>(arguments)...));
}

template <typename... argument_types>
auto u8println(std::format_string<argument_types...> const format, argument_types &&...arguments) {
    write_text(with_newline(std::format(format, std::forward<argument_types>(arguments)...)));
}

template <typename... argument_types>
auto u16print(u16_format_string<argument_types...> const format, argument_types &&...arguments) {
    write_text(format_native(format.text, std::forward<argument_types>(arguments)...));
}

template <typename... argument_types>
auto u16println(u16_format_string<argument_types...> const format, argument_types &&...arguments) {
    write_text(with_newline(format_native(format.text, std::forward<argument_types>(arguments)...)));
}

template <typename... argument_types>
auto u32print(u32_format_string<argument_types...> const format, argument_types &&...arguments) {
    write_text(format_native(format.text, std::forward<argument_types>(arguments)...));
}

template <typename... argument_types>
auto u32println(u32_format_string<argument_types...> const format, argument_types &&...arguments) {
    write_text(with_newline(format_native(format.text, std::forward<argument_types>(arguments)...)));
}
