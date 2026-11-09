/// @file
/// Implementation for @ref lexer.hpp.
///
/// Part of Engenide, a general-purpose systems language between C++ and Rust.
/// @copyright (c) 2026 Anstro Pleuton
/// MIT Licensed.

#include "engenide/lexer.hpp"

#include "engenide/data.hpp"
#include "engenide/internal_error.hpp"
#include "engenide/report.hpp"
#include "engenide/source_code.hpp"

#include <unicode/uchar.h>
#include <unicode/umachine.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <memory>
#include <new>
#include <string_view>
#include <utility>
#include <vector>

namespace {
    class lex_scanner;

    class bidi_balance final {
        struct direction final {
            std::size_t pointer{};
            bool        is_format{};
        };

        std::vector<direction> dir_stack_;
        lex_scanner           &scanner_;

    public:
        explicit bidi_balance(lex_scanner &scanner) : scanner_{scanner} {}

        auto record_n_report_invalid() -> void;

        auto report_imbalance() -> void;
    };

    class depth_guard final {
        std::size_t &depth_;

    public:
        explicit depth_guard(std::size_t &depth) : depth_{depth} {
            ++depth_;
        }

        ~depth_guard() {
            --depth_;
        }

        depth_guard(depth_guard const &)                     = delete;
        auto operator=(depth_guard const &) -> depth_guard & = delete;
        depth_guard(depth_guard &&)                          = delete;
        auto operator=(depth_guard &&) -> depth_guard &      = delete;
    };

    constexpr std::size_t max_depth{32};

    class lex_scanner {
        eng::source_code const                   &code_;
        std::vector<eng::raw_token>               raw_tokens_;
        std::vector<std::unique_ptr<eng::report>> reports_;
        std::size_t                               depth_{};

        friend bidi_balance;

    public:
        explicit lex_scanner(eng::source_code const &code) : code_{code} {}

        [[nodiscard]] auto get_result() && -> eng::lex_scan_result {
            return {std::move(raw_tokens_), std::move(reports_)};
        }

    private:
        [[nodiscard]] static auto is_whitespace_(UChar32 const chr) {
            return u_isUWhiteSpace(chr);
        }

        [[nodiscard]] static auto is_syntactic_(UChar32 const chr) {
            return chr == '`' || chr == '#' || chr == '\'' || chr == '"';
        }

        [[nodiscard]] static auto is_symbolic_(UChar32 const chr) {
            return (U_GET_GC_MASK(chr) & (U_GC_P_MASK | U_GC_SM_MASK | U_GC_SC_MASK | U_GC_SK_MASK)) != 0;
        }

        [[nodiscard]] static auto is_atomic_(UChar32 const chr) {
            return chr == '@' ||
                   chr == '(' ||
                   chr == ')' ||
                   chr == '[' ||
                   chr == ']' ||
                   chr == '{' ||
                   chr == '}' ||
                   chr == ';' ||
                   chr == ':' ||
                   chr == ',' ||
                   chr == '.';
        }

        [[nodiscard]] static auto is_composite_(UChar32 const chr) {
            return !is_atomic_(chr) && !is_syntactic_(chr) && is_symbolic_(chr);
        }

        [[nodiscard]] static auto is_escape_(UChar32 const chr) {
            return chr == 'a' ||
                   chr == 'b' ||
                   chr == 'e' ||
                   chr == 'f' ||
                   chr == 'n' ||
                   chr == 'r' ||
                   chr == 't' ||
                   chr == 'v' ||
                   chr == '\'' ||
                   chr == '"' ||
                   chr == '\\' ||
                   chr == '#' ||
                   chr == '$';
        }

        [[nodiscard]] static auto is_numeric_escape_(UChar32 const chr) {
            return (chr >= 'A' && chr <= 'F') || (U_GET_GC_MASK(chr) & U_GC_ND_MASK) != 0;
        }

        [[nodiscard]] static auto is_plausible_escape_(UChar32 const chr) {
            return (U_GET_GC_MASK(chr) & (U_GC_Z_MASK | U_GC_C_MASK)) == 0;
        }

        [[nodiscard]] static auto is_more_plausible_escape_(UChar32 const chr) {
            return (U_GET_GC_MASK(chr) & (U_GC_Z_MASK | U_GC_C_MASK | U_GC_S_MASK | U_GC_P_MASK)) == 0;
        }

        [[nodiscard]] static auto is_ident_start_(UChar32 const chr) {
            return u_hasBinaryProperty(chr, UCHAR_XID_START);
        }

        [[nodiscard]] static auto is_ident_continue_(UChar32 const chr) {
            return u_hasBinaryProperty(chr, UCHAR_XID_CONTINUE);
        }

        [[nodiscard]] static auto is_numeric_start_(UChar32 const chr) {
            return (U_GET_GC_MASK(chr) & U_GC_ND_MASK) != 0;
        }

        [[nodiscard]] static auto is_numeric_continue_(UChar32 const chr) {
            return ((chr | 0x20) >= 'a' && (chr | 0x20) <= 'z') || (U_GET_GC_MASK(chr) & U_GC_ND_MASK) != 0;
        }

        std::size_t index_{};

        [[nodiscard]] auto is_eof_(std::int64_t const offset = 0) const {
            return index_ + offset >= code_.content.size();
        }

        [[nodiscard]] auto peek_(std::int64_t const offset = 0) const {
            return static_cast<UChar32>(code_.content.at(index_ + offset));
        }

        [[nodiscard]] auto pointer_(std::int64_t const offset = 0) const {
            return std::min(index_ + offset, code_.content.size());
        }

        auto advance_(std::int64_t const offset = 1) {
            index_ += offset;
        }

        [[nodiscard]] auto substring_(std::size_t const begin, std::size_t const end) const {
            return std::u32string_view{code_.content}.substr(begin, end - begin);
        }

        [[nodiscard]] auto scan_whitespace_() {
            if (is_eof_() || !is_whitespace_(peek_())) return false;

            std::size_t const begin{pointer_()};
            UChar32 const     whitespace{peek_()};

            advance_();

            while (!is_eof_() && peek_() == whitespace) {
                advance_();
            }

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::whitespace},
                .loc{begin, pointer_()},
            });

            return true;
        }

        [[nodiscard]] auto scan_comment_() {
            if (is_eof_() || peek_() != '#') return false;

            std::size_t const begin{pointer_()};

            advance_();

            if (!is_eof_() && peek_() == '{') {
                bidi_balance balance(*this);

                std::size_t nest{1};

                while (!is_eof_()) {
                    balance.record_n_report_invalid();

                    if (peek_() == '#') {
                        advance_();

                        if (!is_eof_() && peek_() == '{') {
                            ++nest;
                            advance_();
                        }

                        continue;
                    }

                    if (peek_() == '}') {
                        advance_();

                        if (!is_eof_() && peek_() == '#') {
                            --nest;
                            advance_();
                            if (nest == 0) break;
                        }

                        continue;
                    }

                    advance_();
                }

                balance.report_imbalance();

                if (nest != 0) {
                    reports_.push_back(eng::make_unterm_block_comment_error(eng::source_loc{begin, pointer_()}));
                    reports_.push_back(
                        eng::make_block_comment_nest_note(eng::source_loc{pointer_(-1), pointer_()}, nest));
                }

                raw_tokens_.push_back(eng::raw_token{
                    .kind{eng::raw_token_kind::block_comment},
                    .loc{begin, pointer_()},
                });

                return true;
            }

            bidi_balance balance(*this);

            while (!is_eof_()) {
                balance.record_n_report_invalid();

                if (peek_() == '\n') {
                    break;
                }

                advance_();
            }

            balance.report_imbalance();

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::line_comment},
                .loc{begin, pointer_()},
            });

            return true;
        }

        [[nodiscard]] auto scan_ident_() {
            if (is_eof_() || !is_ident_start_(peek_())) return false;

            std::size_t const begin{pointer_()};

            advance_();

            while (!is_eof_() && is_ident_continue_(peek_())) {
                advance_();
            }

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::identifier},
                .loc{begin, pointer_()},
            });

            return true;
        }

        [[nodiscard]] auto scan_raw_ident_() {
            if (is_eof_() || peek_() != '`') return false;

            std::size_t const begin{pointer_()};

            advance_();

            bool terminated{};

            bidi_balance balance(*this);
            while (!is_eof_()) {
                balance.record_n_report_invalid();

                if (peek_() == '\n') {
                    break;
                }

                if (peek_() == '\\') {
                    advance_();

                    if (is_eof_()) {
                        break;
                    }

                    if (peek_() == '\\' || peek_() == '`') {
                        advance_();
                    }

                    continue;
                }

                if (peek_() == '`') {
                    terminated = true;
                    advance_();
                    break;
                }

                advance_();
            }

            balance.report_imbalance();

            if (!terminated) {
                reports_.push_back(eng::make_unterm_raw_ident_error(eng::source_loc{begin, pointer_()}));
            }

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::raw_identifier},
                .loc{begin, pointer_()},
            });

            return true;
        }

        [[nodiscard]] auto scan_symbolic_() {
            if (is_eof_() || !is_composite_(peek_())) return false;

            std::size_t const begin{pointer_()};

            advance_();

            while (!is_eof_() && is_composite_(peek_())) {
                advance_();
            }

            auto const delimiter{eng::parse_delimiter(substring_(begin, pointer_()))};

            raw_tokens_.push_back(eng::raw_token{
                .kind{delimiter ? eng::raw_token_kind::delimiter : eng::raw_token_kind::symbolic},
                .loc{begin, pointer_()},
            });

            return true;
        }

        [[nodiscard]] auto scan_delimiter_() {
            if (is_eof_() || !is_atomic_(peek_())) return false;

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::delimiter},
                .loc{eng::source_loc{pointer_(), pointer_(1)}},
            });

            advance_();

            return true;
        }

        [[nodiscard]] auto scan_numeric_() {
            if (is_eof_() || !is_numeric_start_(peek_())) return false;

            std::size_t const begin{pointer_()};

            advance_();

            while (!is_eof_()) {
                if (is_numeric_continue_(peek_())) {
                    advance_();
                    continue;
                }

                if ((peek_() == '.' || peek_() == '\'') && !is_eof_(1) && is_numeric_continue_(peek_(1))) {
                    advance_();

                    continue;
                }

                break;
            }

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::numeric_literal},
                .loc{begin, pointer_()},
            });

            return true;
        }

        auto literal_escape_() {
            if (is_eof_() || peek_() != '\\') return;

            std::size_t const begin{pointer_()};

            advance_();

            if (!is_eof_() && is_escape_(peek_())) {
                advance_();

                raw_tokens_.push_back(eng::raw_token{
                    .kind{eng::raw_token_kind::literal_escape},
                    .loc{begin, pointer_()},
                });

                return;
            }

            if (is_eof_() || !is_numeric_escape_(peek_())) {
                advance_(!is_eof_() && is_plausible_escape_(peek_()) ? 1 : 0);

                reports_.push_back(eng::make_invalid_escape_sequence_error(eng::source_loc{begin, pointer_()}));

                raw_tokens_.push_back(eng::raw_token{
                    .kind{eng::raw_token_kind::invalid},
                    .loc{begin, pointer_()},
                });

                return;
            }

            advance_();

            if (is_eof_() || !is_numeric_escape_(peek_())) {
                advance_(!is_eof_() && is_more_plausible_escape_(peek_()) ? 1 : 0);

                reports_.push_back(eng::make_numeric_escape_length_error(eng::source_loc{begin, pointer_()}));

                raw_tokens_.push_back(eng::raw_token{
                    .kind{eng::raw_token_kind::invalid},
                    .loc{begin, pointer_()},
                });

                return;
            }

            advance_();

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::literal_numeric_escape},
                .loc{begin, pointer_()},
            });
        }

        /// @returns `true` if terminated.
        [[nodiscard]] auto interp_format_(std::size_t const interp_sign) {
            if (is_eof_() || peek_() != '(') return false;

            std::size_t const begin{pointer_()};

            advance_();

            bool terminated{};

            bidi_balance balance(*this);
            while (!is_eof_()) {
                balance.record_n_report_invalid();

                if (peek_() == '"') {
                    break;
                }

                if (peek_() == ')') {
                    terminated = true;
                    break;
                }

                advance_();
            }

            balance.report_imbalance();

            if (!terminated) {
                reports_.push_back(eng::make_unterm_format_error(eng::source_loc{begin, pointer_()}));
                reports_.push_back(eng::make_escape_interp_help(eng::source_loc{interp_sign, interp_sign + 1}));
            } else {
                advance_();
            }

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::interp_format},
                .loc{begin, pointer_()},
            });

            return terminated;
        }

        auto interp_expr_(std::size_t const interp_sign) {
            if (is_eof_() || peek_() != '{') return;

            if (depth_ >= max_depth) {
                reports_.push_back(
                    eng::make_interp_too_deep_error(eng::source_loc{pointer_(), pointer_(1)}, max_depth));

                raw_tokens_.push_back(eng::raw_token{
                    .kind{eng::raw_token_kind::invalid},
                    .loc{pointer_(), pointer_(1)},
                });

                advance_();
                return;
            }

            depth_guard const guard{depth_};

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::interp_begin},
                .loc{eng::source_loc{pointer_(), pointer_(1)}},
            });

            advance_();

            std::size_t nest{1};

            while (!is_eof_()) {
                if (peek_() == '{') {
                    ++nest;
                }

                if (peek_() == '}') {
                    --nest;
                    if (nest == 0) break;
                }

                if (!scan_next_()) {
                    break;
                }
            }

            if (nest != 0) {
                reports_.push_back(eng::make_unterm_expr_interp_error(eng::source_loc{pointer_(-1), pointer_()}));
                reports_.push_back(eng::make_escape_interp_help(eng::source_loc{interp_sign, interp_sign + 1}));
                reports_.push_back(eng::make_expr_interp_nest_note(eng::source_loc{pointer_(-1), pointer_()}, nest));
            } else {
                raw_tokens_.push_back(eng::raw_token{
                    .kind{eng::raw_token_kind::interp_end},
                    .loc{eng::source_loc{pointer_(), pointer_(1)}},
                });

                advance_();
            }
        }

        auto interp_ident_() {
            if (is_eof_() || !is_ident_start_(peek_())) return;

            std::size_t const begin{pointer_()};

            advance_();

            while (!is_eof_() && is_ident_continue_(peek_())) {
                advance_();
            }

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::interp_identifier},
                .loc{begin, pointer_()},
            });
        }

        auto interp_() {
            if (is_eof_() || peek_() != '$') return;

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::interp_sign},
                .loc{eng::source_loc{pointer_(), pointer_(1)}},
            });

            std::size_t const interp_sign{pointer_()};

            advance_();

            if (is_eof_()) return;

            if (peek_() == '(') {
                if (!interp_format_(interp_sign)) return;

                if (is_eof_() || peek_() != '{') {
                    reports_.push_back(eng::make_expr_interp_required_error(eng::source_loc{pointer_(), pointer_(1)}));
                    reports_.push_back(eng::make_escape_interp_help(eng::source_loc{interp_sign, interp_sign + 1}));
                    return;
                }

                interp_expr_(interp_sign);
            } else if (peek_() == '{') {
                interp_expr_(interp_sign);
            } else if (is_ident_start_(peek_())) {
                interp_ident_();
            } else {
                reports_.push_back(eng::make_invalid_interp_error(eng::source_loc{pointer_(), pointer_(1)}));
                reports_.push_back(eng::make_escape_interp_help(eng::source_loc{interp_sign, interp_sign + 1}));
            }
        }

        auto raw_segment_() {
            if (is_eof_() || peek_() != '#') return;

            std::size_t const opener{pointer_()};

            advance_();

            if (is_eof_()) {
                reports_.push_back(eng::make_invalid_raw_segment_error(eng::source_loc{pointer_(), pointer_(1)}));
                reports_.push_back(eng::make_escape_raw_segment_help(eng::source_loc{opener, opener + 1}));

                raw_tokens_.push_back(eng::raw_token{
                    .kind{eng::raw_token_kind::invalid},
                    .loc{opener, pointer_()},
                });

                return;
            }

            std::u32string_view delimiter{};

            if (is_ident_start_(peek_())) {
                std::size_t const delimiter_begin{pointer_()};

                advance_();

                while (!is_eof_() && is_ident_continue_(peek_())) {
                    advance_();
                }

                delimiter = substring_(delimiter_begin, pointer_());
            }

            if (is_eof_() || peek_() != '{') {
                reports_.push_back(eng::make_invalid_raw_segment_error(eng::source_loc{pointer_(), pointer_(1)}));
                reports_.push_back(eng::make_escape_raw_segment_help(eng::source_loc{opener, opener + 1}));

                raw_tokens_.push_back(eng::raw_token{
                    .kind{eng::raw_token_kind::invalid},
                    .loc{opener, pointer_()},
                });

                return;
            }

            advance_();

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::raw_segment_opener},
                .loc{opener, pointer_()},
            });

            std::size_t const segment{pointer_()};

            bidi_balance balance(*this);

            std::size_t closer{};

            bool terminated{};
            while (!is_eof_()) {
                balance.record_n_report_invalid();

                if (peek_() != '}') {
                    advance_();
                    continue;
                }

                closer = pointer_();

                advance_();

                if (is_eof_()) break;

                std::size_t const delimiter_begin{pointer_()};

                if (is_ident_start_(peek_())) {
                    advance_();

                    while (!is_eof_() && is_ident_continue_(peek_())) {
                        advance_();
                    }

                    if (is_eof_()) break;
                }

                if (delimiter != substring_(delimiter_begin, pointer_())) continue;

                if (peek_() == '#') {
                    terminated = true;
                    advance_();
                    break;
                }
            }

            balance.report_imbalance();

            if (!terminated) {
                reports_.push_back(eng::make_unterm_raw_segment_error(eng::source_loc{pointer_(-1), pointer_()}));
                reports_.push_back(eng::make_escape_raw_segment_help(eng::source_loc{opener, opener + 1}));

                raw_tokens_.push_back(eng::raw_token{
                    .kind{eng::raw_token_kind::raw_segment},
                    .loc{segment, pointer_()},
                });

                return;
            }

            if (segment != closer) {
                raw_tokens_.push_back(eng::raw_token{
                    .kind{eng::raw_token_kind::raw_segment},
                    .loc{segment, closer},
                });
            }

            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::raw_segment_closer},
                .loc{closer, pointer_()},
            });
        }

        [[nodiscard]] auto scan_quote_literal_() {
            if (is_eof_() || (peek_() != '"' && peek_() != '\'')) return false;

            UChar32 const     quote{peek_()};
            bool const        is_string{quote == '"'};
            std::size_t const quote_begin{pointer_()};

            raw_tokens_.push_back(eng::raw_token{
                .kind{is_string ? eng::raw_token_kind::string_begin : eng::raw_token_kind::char_begin},
                .loc{eng::source_loc{pointer_(), pointer_(1)}},
            });

            advance_();

            std::size_t begin{pointer_()};

            auto const start_part{[&] -> void { begin = pointer_(); }};

            auto const flush_part{
                [&] -> void {
                    if (begin != pointer_()) {
                        raw_tokens_.push_back(eng::raw_token{
                            .kind{is_string ? eng::raw_token_kind::string_part : eng::raw_token_kind::char_part},
                            .loc{begin, pointer_()},
                        });
                    }
                },
            };

            bidi_balance balance(*this);

            bool terminated{};
            while (!is_eof_()) {
                balance.record_n_report_invalid();

                if (!is_string && peek_() == '\n') {
                    break;
                }

                if (is_string && peek_() == '$') {
                    flush_part();
                    interp_();
                    start_part();
                    continue;
                }

                if (is_string && peek_() == '#') {
                    flush_part();
                    raw_segment_();
                    start_part();
                    continue;
                }

                if (peek_() == '\\') {
                    flush_part();
                    literal_escape_();
                    start_part();
                    continue;
                }

                if (peek_() == quote) {
                    terminated = true;
                    break;
                }

                advance_();
            }

            balance.report_imbalance();

            flush_part();

            if (!terminated) {
                reports_.push_back(is_string ? eng::make_unterm_string_error(eng::source_loc{quote_begin, pointer_()})
                                             : eng::make_unterm_char_error(eng::source_loc{quote_begin, pointer_()}));
            } else {
                raw_tokens_.push_back(eng::raw_token{
                    .kind{is_string ? eng::raw_token_kind::string_end : eng::raw_token_kind::char_end},
                    .loc{eng::source_loc{pointer_(), pointer_(1)}},
                });
                advance_();
            }

            return true;
        }

        auto invalid_character_() {
            if (is_eof_()) return;

            reports_.push_back(eng::make_invalid_character_error(eng::source_loc{pointer_(), pointer_(1)}));
            raw_tokens_.push_back(eng::raw_token{
                .kind{eng::raw_token_kind::invalid},
                .loc{eng::source_loc{pointer_(), pointer_(1)}},
            });
            advance_();
        }

        [[nodiscard]] auto scan_next_() -> bool {
            if (is_eof_()) return false;
            if (scan_whitespace_()) return true;
            if (scan_comment_()) return true;
            if (scan_ident_()) return true;
            if (scan_raw_ident_()) return true;
            if (scan_symbolic_()) return true;
            if (scan_delimiter_()) return true;
            if (scan_numeric_()) return true;
            if (scan_quote_literal_()) return true;
            invalid_character_();
            return true;
        }

    public:
        auto scan() {
            while (!is_eof_()) {
                std::size_t const before{pointer_()};
                std::ignore = scan_next_();
                if (pointer_() == before) {
                    throw eng::internal_error("scan_next_() did not move: before: {}", before);
                }
            }
        }
    };

    auto bidi_balance::record_n_report_invalid() -> void {
        if (scanner_.is_eof_()) return;

        UCharDirection const char_dir{u_charDirection(scanner_.peek_())};

        if (char_dir == U_LEFT_TO_RIGHT_EMBEDDING ||
            char_dir == U_RIGHT_TO_LEFT_EMBEDDING ||
            char_dir == U_LEFT_TO_RIGHT_OVERRIDE ||
            char_dir == U_RIGHT_TO_LEFT_OVERRIDE) {
            dir_stack_.emplace_back(scanner_.pointer_(), true);
            return;
        }

        if (char_dir == U_LEFT_TO_RIGHT_ISOLATE ||
            char_dir == U_RIGHT_TO_LEFT_ISOLATE ||
            char_dir == U_FIRST_STRONG_ISOLATE) {
            dir_stack_.emplace_back(scanner_.pointer_(), false);
            return;
        }

        if (char_dir != U_POP_DIRECTIONAL_FORMAT && char_dir != U_POP_DIRECTIONAL_ISOLATE) return;

        bool const is_format{char_dir == U_POP_DIRECTIONAL_FORMAT};
        if (dir_stack_.empty()) {
            scanner_.reports_.push_back(
                eng::make_empty_bidi_pop_error(eng::source_loc{scanner_.pointer_(), scanner_.pointer_(1)}));
        } else if (is_format != dir_stack_.back().is_format) {
            scanner_.reports_.push_back(
                eng::make_invalid_bidi_pop_error(eng::source_loc{scanner_.pointer_(), scanner_.pointer_(1)},
                    dir_stack_.back().is_format ? "format" : "isolate"));
            scanner_.reports_.push_back(
                eng::make_bidi_push_note(eng::source_loc{dir_stack_.back().pointer, dir_stack_.back().pointer + 1}));
        } else {
            dir_stack_.pop_back();
        }
    }

    auto bidi_balance::report_imbalance() -> void {
        if (!dir_stack_.empty()) {
            scanner_.reports_.push_back(eng::make_imbalanced_bidi_error(
                scanner_.is_eof_() ? eng::source_loc{scanner_.pointer_(-1), scanner_.pointer_()}
                                   : eng::source_loc{scanner_.pointer_(), scanner_.pointer_(1)}));
            for (direction const dir : dir_stack_) {
                scanner_.reports_.push_back(eng::make_bidi_push_note(eng::source_loc{dir.pointer, dir.pointer + 1}));
            }
        }
    }
}

auto eng::lex_scan(source_code const &code) -> lex_scan_result try {
    lex_scanner scanner(code);
    scanner.scan();
    return std::move(scanner).get_result();
} catch (eng::internal_error const &) {
    throw;
} catch (std::bad_alloc const &) {
    throw;
} catch (std::exception const &error) {
    throw eng::internal_error("Exception thrown from lex_scanner: {}", error.what());
}

namespace {}

auto eng::lex_screen(source_code const &code, std::vector<raw_token> const &raw_tokens) -> lex_screen_result try {
    // lex_screener screener(code);
    // screener.scan();
    // return std::move(screener).get_result();
    // TODO
    std::ignore = code;
    std::ignore = raw_tokens;
    return {};
} catch (eng::internal_error const &) {
    throw;
} catch (std::bad_alloc const &) {
    throw;
} catch (std::exception const &error) {
    throw eng::internal_error("Exception thrown from lex_screener: {}", error.what());
}
