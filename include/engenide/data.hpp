/// @file
/// List of things in Engenide.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <optional>
#include <string_view>
#include <type_traits>

namespace eng {
#define ENG_KEYWORD_LIST(X) \
    X(aborts)               \
    X(addr)                 \
    X(all)                  \
    X(as)                   \
    X(auto)                 \
    X(base)                 \
    X(be)                   \
    X(bit_as)               \
    X(break)                \
    X(by)                   \
    X(case)                 \
    X(catch)                \
    X(class)                \
    X(cont)                 \
    X(continue)             \
    X(conv)                 \
    X(copy)                 \
    X(ctor)                 \
    X(decl)                 \
    X(default)              \
    X(defer)                \
    X(do)                   \
    X(dtor)                 \
    X(else)                 \
    X(emit)                 \
    X(enum)                 \
    X(export)               \
    X(false)                \
    X(final)                \
    X(fn)                   \
    X(for)                  \
    X(from)                 \
    X(get)                  \
    X(global)               \
    X(goto)                 \
    X(has)                  \
    X(if)                   \
    X(impl)                 \
    X(import)               \
    X(in)                   \
    X(inf)                  \
    X(inter)                \
    X(into)                 \
    X(is)                   \
    X(is_not)               \
    X(label)                \
    X(let)                  \
    X(life)                 \
    X(lit)                  \
    X(meets)                \
    X(move)                 \
    X(nan)                  \
    X(not_in)               \
    X(ns)                   \
    X(null)                 \
    X(nullptr)              \
    X(once)                 \
    X(onward)               \
    X(op)                   \
    X(ovrd)                 \
    X(patch)                \
    X(pers)                 \
    X(priv)                 \
    X(prop)                 \
    X(prot)                 \
    X(pub)                  \
    X(raw_as)               \
    X(re_as)                \
    X(result)               \
    X(return)               \
    X(self)                 \
    X(set)                  \
    X(share)                \
    X(size_of)              \
    X(static)               \
    X(switch)               \
    X(tag_by)               \
    X(tag_of)               \
    X(this)                 \
    X(throw)                \
    X(throws)               \
    X(to)                   \
    X(true)                 \
    X(try)                  \
    X(type)                 \
    X(type_of)              \
    X(undef)                \
    X(uninit)               \
    X(unsafe)               \
    X(virt)                 \
    X(where)                \
    X(while)                \
    X(with)

    enum class keyword_enum : std::uint8_t {
#define X(name) kw_##name,
        ENG_KEYWORD_LIST(X)
#undef X // NOLINT(readability-trailing-comma)
    };

#define X(name) +1 // NOLINT(bugprone-macro-parentheses)
    inline constexpr std::size_t keyword_count{0 ENG_KEYWORD_LIST(X)};
#undef X

    inline constexpr std::array<std::string_view, keyword_count> keyword_strings{
#define X(name) #name,
        ENG_KEYWORD_LIST(X)
#undef X
    };

    inline constexpr std::array<std::u32string_view, keyword_count> keyword_strings_u32{
#define X(name) U"" #name,
        ENG_KEYWORD_LIST(X)
#undef X
    };

    static_assert(std::ranges::is_sorted(keyword_strings));
    static_assert(std::ranges::is_sorted(keyword_strings_u32));

    [[nodiscard]] constexpr auto keyword_str(keyword_enum const keyword) -> std::string_view {
        auto const index{static_cast<std::size_t>(keyword)};
        return index < keyword_count ? keyword_strings.at(index) : std::string_view{};
    }

    /// Binary search for matching keyword.
    [[nodiscard]] constexpr auto parse_keyword(std::u32string_view const keyword) -> std::optional<keyword_enum> {
        auto const iter{std::ranges::lower_bound(keyword_strings_u32, keyword)};
        if (iter != keyword_strings_u32.end() && *iter == keyword)
            return static_cast<keyword_enum>(iter - keyword_strings_u32.begin());
        return std::nullopt;
    }

#define ENG_DELIMITER_LIST(X)     \
    X("!!", double_exclaim, 2)    \
    X("$", currency, 1)           \
    X("(", left_paren, 1)         \
    X(")", right_paren, 1)        \
    X(",", comma, 1)              \
    X(".", period, 1)             \
    X(":", colon, 1)              \
    X(":=", colon_equal, 2)       \
    X(";", semicolon, 1)          \
    X("<:", left_angle_colon, 2)  \
    X("=", equal, 1)              \
    X("=>", equal_right_angle, 2) \
    X("?", question, 1)           \
    X("??", double_question, 2)   \
    X("@", at, 1)                 \
    X("[", left_bracket, 1)       \
    X("]", right_bracket, 1)      \
    X("{", left_brace, 1)         \
    X("}", right_brace, 1)

    enum class delimiter_enum : std::uint8_t {
#define X(text, name, length) dl_##name,
        ENG_DELIMITER_LIST(X)
#undef X // NOLINT(readability-trailing-comma)
    };

#define X(text, name, length) +1 // NOLINT(bugprone-macro-parentheses)
    inline constexpr std::size_t delimiter_count{0 ENG_DELIMITER_LIST(X)};
#undef X

#define X(text, name, length) length,
    inline constexpr std::size_t max_delimiter_length{
        static_cast<size_t>(std::max({ENG_DELIMITER_LIST(X) 0})),
    };
#undef X

    inline constexpr std::array<std::string_view, delimiter_count> delimiter_strings{
#define X(text, name, length) text,
        ENG_DELIMITER_LIST(X)
#undef X
    };

    inline constexpr std::array<std::u32string_view, delimiter_count> delimiter_strings_u32{
#define X(text, name, length) U"" text,
        ENG_DELIMITER_LIST(X)
#undef X
    };

    static_assert(std::ranges::is_sorted(delimiter_strings));
    static_assert(std::ranges::is_sorted(delimiter_strings_u32));

    [[nodiscard]] constexpr auto delimiter_str(delimiter_enum const delimiter) -> std::string_view {
        auto const iter{static_cast<std::size_t>(delimiter)};
        return iter < delimiter_count ? delimiter_strings.at(iter) : std::string_view{};
    }

    /// Longest-match (maximal munch): preferring `=>` over `=`, `:=` over `:`, etc.
    [[nodiscard]] constexpr auto parse_delimiter(std::u32string_view const input) -> std::optional<delimiter_enum> {
        auto const first{delimiter_strings_u32.begin()};
        auto const last{first + delimiter_count};

        for (auto length{std::min(input.size(), max_delimiter_length)}; length > 0; --length) {
            auto const candidate{input.substr(0, length)};

            auto const iter{std::lower_bound(first, last, candidate)};
            if (iter != last && *iter == candidate) {
                return static_cast<delimiter_enum>(iter - first);
            }
        }
        return std::nullopt;
    }
}
