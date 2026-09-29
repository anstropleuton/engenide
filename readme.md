# Engenide

Engenide is a systems programming language that you can say is like "C++ and Rust with my own taste". A middle ground
between them, with a focus on extensibility and ergonomics.

Currently, very early in the development.

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

## License

Engenide specification and implementation is licensed under MIT license.
