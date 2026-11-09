/// @file
/// Lexical analysis (scanner & screener).
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#pragma once

#include "data.hpp"
#include "report.hpp"
#include "source_code.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

/// Lexer is split in two parts: classification and canonicalization.
namespace eng {
#define ENG_RAW_TOKEN_KIND_LIST(X)                     \
    X(whitespace)             /**< `any` */            \
    X(line_comment)           /**< `# line` */         \
    X(block_comment)          /**< `#{ block }#` */    \
    X(identifier)             /**< `name` */           \
    X(raw_identifier)         /**< `` `class` `` */    \
    X(symbolic)               /**< `+`, `?` */         \
    X(delimiter)              /**< `@`, `;` */         \
    X(numeric_literal)        /**< `123`, `456.789` */ \
    X(literal_escape)         /**< `\n`, `\t` */       \
    X(literal_numeric_escape) /**< `\1B` */            \
    X(interp_sign)            /**< `$` */              \
    X(interp_format)          /**< `(format)` */       \
    X(interp_begin)           /**< `{` */              \
    X(interp_end)             /**< `}` */              \
    X(interp_identifier)      /**< `value` */          \
    X(string_begin)           /**< `"` */              \
    X(string_end)             /**< `"` */              \
    X(string_part)            /**< `asd` */            \
    X(raw_segment_opener)     /**< `#delim{` */        \
    X(raw_segment_closer)     /**< `}delim#` */        \
    X(raw_segment)            /**< `asd` */            \
    X(char_begin)             /**< `'` */              \
    X(char_part)              /**< `a` */              \
    X(char_end)               /**< `'` */              \
    X(invalid)                /**< `/shrug` */

    /// Exact token category, differentiating every detail.
    enum class raw_token_kind : std::uint8_t {
#define X(name) name,
        ENG_RAW_TOKEN_KIND_LIST(X)
#undef X // NOLINT(readability-trailing-comma)
    };

    [[nodiscard]] constexpr auto raw_token_kind_str(raw_token_kind const kind) -> std::string_view {
        constexpr std::array names{
#define X(name) #name,
            ENG_RAW_TOKEN_KIND_LIST(X)
#undef X
        };
        auto const index{static_cast<std::size_t>(kind)};
        return index < std::size(names) ? names.at(index) : std::string_view{};
    }

#define ENG_TOKEN_KIND_LIST(X) \
    X(identifier)              \
    X(keyword)                 \
    X(symbolic)                \
    X(delimiter)               \
    X(numeric_literal)         \
    X(interp_begin)            \
    X(interp_end)              \
    X(interp_format)           \
    X(string_begin)            \
    X(string_part)             \
    X(string_end)              \
    X(char_literal)

    /// Relevant token category, excludes whitespace and comment.
    enum class token_kind : std::uint8_t {
#define X(name) name,
        ENG_TOKEN_KIND_LIST(X)
#undef X // NOLINT(readability-trailing-comma)
    };

    [[nodiscard]] constexpr auto token_kind_str(token_kind const kind) -> std::string_view {
        constexpr std::array names{
#define X(name) #name,
            ENG_TOKEN_KIND_LIST(X)
#undef X
        };
        auto const index{static_cast<std::size_t>(kind)};
        return index < std::size(names) ? names.at(index) : std::string_view{};
    }

    /// Purely token classification of the source code (lossless).
    struct raw_token final {
        raw_token_kind kind{};
        source_loc     loc{};
    };

    /// Token canonicalized (lossy).
    struct token_value final {
        std::u32string id_sym_part; ///< Identifier or Symbolic or String Part or Format Part.
        keyword_enum   keyword{};
        delimiter_enum delimiter{};
        std::uint64_t  integer{};
        double         floating{};
        char32_t       character{};
    };

    struct token final {
        token_kind     kind{};
        raw_token_kind raw_kind{}; ///< For friendlier diagnosis.
        source_loc     loc{};
        token_value    value{};
    };

    struct lex_scan_result final {
        std::vector<raw_token>               raw_tokens;
        std::vector<std::unique_ptr<report>> reports;
    };

    /// Lexer stage 1: classification.
    [[nodiscard]] auto lex_scan(source_code const &code) -> lex_scan_result;

    struct lex_screen_result final {
        std::vector<token>                   tokens;
        std::vector<std::unique_ptr<report>> reports;
    };

    /// Lexer stage 2: canonicalization.
    [[nodiscard]] auto lex_screen(source_code const &code, std::vector<raw_token> const &raw_tokens)
        -> lex_screen_result;

    // Stage 1 errors

    ENG_REPORT(invalid_bidi_pop_error, error, (std::string alternative;), (, std::string_view const alternative),
        (, alternative{alternative}), ("Trying to pop wrong bi-directional marker, expected {}", alternative));

    ENG_REPORT(empty_bidi_pop_error, error, (), (), (), ("Trying to pop non-pushed bi-directional marker"));

    ENG_REPORT(bidi_push_note, note, (), (), (), ("Previous bi-directional marker pushed"));

    ENG_REPORT(imbalanced_bidi_error, error, (), (), (), ("Imbalanced bi-directional character marker"));

    ENG_REPORT(unterm_char_error, error, (), (), (), ("Unterminated character literal"));

    ENG_REPORT(unterm_string_error, error, (), (), (), ("Unterminated string literal"));

    ENG_REPORT(unterm_format_error, error, (), (), (), ("Unterminated string format specifier"));

    ENG_REPORT(expr_interp_required_error, error, (), (), (),
        ("Expression-based interpolation syntax ('{{' ... '}}') required after format specifier"));

    ENG_REPORT(unterm_expr_interp_error, error, (), (), (), ("Unterminated expression-based interpolation"));

    ENG_REPORT(expr_interp_nest_note, note, (std::size_t nest;), (, std::size_t const nest), (, nest{nest}),
        ("Expression-based interpolation can be nested, current nesting level is {} deep", nest));

    ENG_REPORT(invalid_interp_error, error, (), (), (), ("Invalid character in interpolation"));

    ENG_REPORT(escape_interp_help, help, (), (), (), ("Interpolation '$' can be escaped using '\\$'"));

    ENG_REPORT(invalid_raw_segment_error, error, (), (), (), ("Invalid character in raw segment"));

    ENG_REPORT(escape_raw_segment_help, help, (), (), (), ("Raw segment '#' can be escaped using '\\#'"));

    ENG_REPORT(unterm_raw_segment_error, error, (), (), (), ("Unterminated raw segment in string"));

    ENG_REPORT(numeric_escape_length_error, error, (), (), (),
        ("Numeric escape sequence must be two capitalized hexadecimal digits"));

    ENG_REPORT(invalid_escape_sequence_error, error, (), (), (), ("Invalid escape sequence"));

    ENG_REPORT(unterm_block_comment_error, error, (), (), (), ("Unterminated block comment"));

    ENG_REPORT(unterm_raw_ident_error, error, (), (), (), ("Unterminated raw identifier"));

    ENG_REPORT(block_comment_nest_note, note, (std::size_t nest;), (, std::size_t const nest), (, nest{nest}),
        ("Block comment can be nested, current nesting level is {} deep", nest));

    ENG_REPORT(invalid_character_error, error, (), (), (), ("Invalid character in source code"));

    ENG_REPORT(interp_too_deep_error, error, (std::size_t limit;), (, std::size_t const limit), (, limit{limit}),
        ("Nested interpolation exceeded {} depth limit", limit));

    // Stage 2 errors

    // ...
}
