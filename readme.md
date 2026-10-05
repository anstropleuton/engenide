# Engenide

Engenide is a systems programming language that you can say is like "C++ and
Rust with my own taste". A middle ground between them, with a focus on
extensibility and ergonomics.

Currently, very early in the development.

**Engine** - A collective term I coined for Compiler and Interpreter combined.

## Goals

Achieve a middle ground between C++'s "Superpowers, or die trying" and Rust's
"Superpowers, mental tax included".

Multiple paradigms coexist, none are picked as favorite by the language.

Language allows multiple ways of doing things. Enforcement may be handled by
teams, or perhaps - no promises - an Engine's plugin system.

Frictionless for common, safe cases. Small friction for deviation. Large
friction for unsafe stuff.

AOT and JIT paths. Every mode-specific feature has a defined degradation path in
the other mode, and if not possible, not included.

Big standard library. Not as big as Python tho...

## Anti-Goals

No Minimalism at Language Design level. "One obvious way" isn't fun.

Small, curated packages in Engenide's official package repository, rather than
anything user uploaded and review passed.

## Design

Design can be found in [design/](design/index.md) directory. Please be mindful
that it will change rapidly.

## Example

```eng
# Hello world - Engenide
import io: eng.std.io;

@executable("hello_world")
fn hello throws {
    io.print("What's your name? ");
    let name = io.scanln();
    io.println("Hello $name!");
};
```

## Usage

*TODO: Add usage*

```shell
git clone --depth=1 https://github.com/anstropleuton/engenide.git
cd engenide
cmake --preset release
```

The `eng` binary or `eng.exe` is the engine compiler.

## License

Engenide specification and implementation is licensed under MIT license.
