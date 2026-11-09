# Engenide Design

Engenide is a general-purpose systems language between C++ and Rust.

## Grammar Notation

The notation is context-free: each rule has one non-terminal on its left side.
Constructs a context-free grammar cannot express (e.g. raw strings with a
matching delimiter) are special terminals, defined in prose where first used.

A rule is `name = definition ;` and may span lines. Whitespace is insignificant
except between tokens and inside terminals. `#` outside a terminal starts a
comment to end of line.

| Notation    | Meaning                                                        |
|-------------|----------------------------------------------------------------|
| `name`      | Non-terminal.                                                  |
| `"text"`    | Terminal: literal source text.                                 |
| `{special}` | Special terminal, e.g. `{unicode}`.                            |
| `(a)`       | Grouping.                                                      |
| `[a]`       | Optional.                                                      |
| `a...`      | One or more `a`.                                               |
| `[a...]`    | Zero or more `a`.                                              |
| `a % s`     | One or more `a` separated by `s`, optional trailing `s`.       |
| `[a % s]`   | Zero or more of the above.                                     |
| `a b`       | Sequence.                                                      |
| `a \| b`    | Choice.                                                        |

`a % s` means `a [(s a)...] [s]`: it accepts `a`, `a s`, `a s a`, never a lone `s`.

```
arguments = [expression % ","] ;   # f()  f(x)  f(x,)  f(x, y,)
generics  = "<" type % "," ">" ;   # never empty
```

**Precedence** (high to low): terminals, names, `(...)`, `[...]`; then `...` and
`%` (`...` takes the item before it, `%` the item on each side; use `()` for
groups); then sequence; then `|`.

**Restrictions:** the operand of `...` and both sides of `%` must not be
optional or repeated, and `[ ]` may not wrap an optional. So `[a]...`, `a......`,
`[a] % s` and `[[a]]` are errors. Zero or more is `[a...]` or `[a % s]`.

**Terminals:** inside `"..."`, every character stands for itself except
escapes, and the notation is case-sensitive. `\"` quote, `\\` backslash,
`\a` bell, `\b` backspace, `\e` escape, `\f` form feed, `\n` new line,
`\r` carriage return, `\t` tab, `\v` vertical tab, and `\XX` an ASCII
character (exactly two capital hex digits, `00`-`7F`), e.g. `"\0A"` is a line feed.
