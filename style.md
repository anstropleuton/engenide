# Style Guidelines

1. East-const: Put the const modifier after type
2. Brace-initializer: Use brace initializer over value initializer, even for
   designated initializer
3. lower_snake_case: Every identifier follows lower_snake_case, with few
   exceptions:
    - Macros: UPPER_SNAKE_CASE
    - Private members: lower_snake_case_with_suffix_
4. Initialize: Always initialize members that could be garbage when left
   uninitialized

```cpp
int const constant{value};
```

5. Trailing return type: Use trailing return type over regular return type for
   all functions
6. Standard prefix: Use `std::` even for types that may also be available
   globally

```cpp
auto square(std::float32_t const x) -> std::float32_t {
    return x * x;
}
```

7. Capital suffix: Use capital letter for literal with suffix

```cpp
square(5.0F);
```

8. Markers: Mark functions with `[[nodiscard]]` and `noexcept`, variables with
   `const` and types with `final` by default
9. Checks: Always use `vector.at(index)` over `vector[index]` and
   `optional.value()` over `*optional`

```cpp
struct stash final {
    std::vector<int>   values{};
    std::optional<int> favorite{};
};

[[nodiscard]] auto count(stash const &s) noexcept -> std::size_t {
    return s.values.size();
}

[[nodiscard]] auto first_plus_favorite(stash const &s) -> int {
    int const first{s.values.at(0)};
    int const favorite{s.favorite.value()};
    return first + favorite;
}
```

10. Align: Align variables, fields, parameters, etc. in columns

```cpp
std::vector<user> const &users{get_users()};
std::size_t const        count{users.size()};
```
