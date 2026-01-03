# Engenide Programming Language <!-- omit from toc -->

This is a sketch design document for the Engenide Programming Language, not a formal specification. This does not include grammar or precise definitions. The purpose is to document my rough ideas before I forget them.

## TODO <!-- omit from toc -->

- [ ] Refine ideas.
  - [ ] Architecture.
  - [ ] Modifiers.
  - [ ] Expression.
  - [ ] Keywords.
  - [ ] Macros, Generics, Reflection, Metaprogramming.
  - [ ] Multi-threading.
  - [ ] Tooling.
  - [ ] Plugin system.
- [ ] Formalize into actual specification.
- [ ] Develop a standard library.
- [ ] Include examples.
- [ ] Develop tooling.
  - [ ] Processor.
  - [ ] Compiler.
  - [ ] Interpreter.
  - [ ] Assembler.
  - [ ] Evaluator.
  - [ ] Formal ABI.
  - [ ] Build system.
  - [ ] Packing system.
  - [ ] Language presets.
  - [ ] Plugin system.
- [ ] Official Engenide website.
- [ ] Official Engenide Package Repository (EPR).

## Table of Content <!-- omit from toc -->

- [1. Overview](#1-overview)
  - [1.1. What is Engenide?](#11-what-is-engenide)
  - [1.2. Features](#12-features)
  - [1.3. Philosophy](#13-philosophy)
  - [1.4. Architecture](#14-architecture)
- [2. Lexical Structure](#2-lexical-structure)
  - [2.1. Source Encoding](#21-source-encoding)
  - [2.2. Whitespace](#22-whitespace)
  - [2.3. Comments](#23-comments)
    - [2.3.1. Comment Evaluation](#231-comment-evaluation)
  - [2.4. Words](#24-words)
    - [2.4.1. Backtick Words](#241-backtick-words)
  - [2.5. Operators](#25-operators)
  - [2.6. Punctuations](#26-punctuations)
  - [2.7. Literals](#27-literals)
    - [2.7.1. Character Literals](#271-character-literals)
    - [2.7.2. Boolean Literals](#272-boolean-literals)
    - [2.7.3. Pointer Literal](#273-pointer-literal)
    - [2.7.4. Nullable Literal](#274-nullable-literal)
  - [2.8. Numeric Literals](#28-numeric-literals)
    - [2.8.1. Typing Convention](#281-typing-convention)
    - [2.8.2. Classification](#282-classification)
    - [2.8.3. Base Specification](#283-base-specification)
    - [2.8.4. Special Numeric Literals](#284-special-numeric-literals)
  - [2.9. String Literals](#29-string-literals)
    - [2.9.1. Escape Sequence](#291-escape-sequence)
    - [2.9.2. Raw Segments](#292-raw-segments)
    - [2.9.3. Interpolation Segments](#293-interpolation-segments)
    - [2.9.4. Implicit Concatenation](#294-implicit-concatenation)
- [3. Variable Declaration](#3-variable-declaration)
  - [3.1. Multiple Declaration](#31-multiple-declaration)
  - [3.2. Shadowing](#32-shadowing)
  - [3.3. Discarded Variable](#33-discarded-variable)
- [4. Types](#4-types)
  - [4.1. Integer Types](#41-integer-types)
  - [4.2. Floating-point Types](#42-floating-point-types)
  - [4.3. Character Types](#43-character-types)
  - [4.4. Boolean TYpes](#44-boolean-types)
  - [4.5. String](#45-string)
  - [4.6. Any Type](#46-any-type)
  - [4.7. Variants](#47-variants)
  - [4.8. Type Conversion](#48-type-conversion)
    - [4.8.1. Conversion Types](#481-conversion-types)
    - [4.8.2. Numeric Conversion](#482-numeric-conversion)
    - [4.8.3. Automatic Multi-conversion](#483-automatic-multi-conversion)
  - [4.9. Obtaining Size of Types](#49-obtaining-size-of-types)
  - [4.10. Modifiers](#410-modifiers)
    - [4.10.1. Constants](#4101-constants)
    - [4.10.2. Pointers](#4102-pointers)
    - [4.10.3. References](#4103-references)
    - [4.10.4. Nullables](#4104-nullables)
    - [4.10.5. Reference-Counting](#4105-reference-counting)
    - [4.10.6. Moving Types](#4106-moving-types)
    - [4.10.7. Unique Moving Types](#4107-unique-moving-types)
    - [4.10.8. Swapping Types](#4108-swapping-types)
    - [4.10.9. Polymorphic Types](#4109-polymorphic-types)
    - [4.10.10. Combining Modifiers](#41010-combining-modifiers)
  - [4.11. Arrays](#411-arrays)
    - [4.11.1. Typed and Untyped](#4111-typed-and-untyped)
    - [4.11.2. Static-Sized and Dynamic-Sized](#4112-static-sized-and-dynamic-sized)
    - [4.11.3. Accessing Arrays](#4113-accessing-arrays)
    - [4.11.4. Resizing Arrays](#4114-resizing-arrays)
    - [4.11.5. Count](#4115-count)
    - [4.11.6. Existance and Iteration](#4116-existance-and-iteration)
    - [4.11.7. Array Range Generator](#4117-array-range-generator)
    - [4.11.8. Array Repeat Generator](#4118-array-repeat-generator)
    - [4.11.9. Array Generator Expression](#4119-array-generator-expression)
    - [4.11.10. Array Packing and Unpacking](#41110-array-packing-and-unpacking)
  - [4.12. Tuples](#412-tuples)
  - [4.13. Maps](#413-maps)
- [5. Statements](#5-statements)
  - [5.1. Expressions](#51-expressions)
    - [5.1.1. Primary Expression](#511-primary-expression)
    - [5.1.2. Prefix Operator](#512-prefix-operator)
    - [5.1.3. Suffix Operator](#513-suffix-operator)
    - [5.1.4. Unary Combination](#514-unary-combination)
    - [5.1.5. Infix Operator](#515-infix-operator)
    - [5.1.6. Chaining](#516-chaining)
    - [5.1.7. Associativity](#517-associativity)
    - [5.1.8. Multi-Part Operator](#518-multi-part-operator)
    - [5.1.9. Member Access](#519-member-access)
  - [5.2. Variable Assignment](#52-variable-assignment)
  - [5.3. `if` Statement](#53-if-statement)
  - [5.4. `while` Statement](#54-while-statement)
  - [5.5. `for` Statement](#55-for-statement)
  - [5.6. `once` and `onward`](#56-once-and-onward)
  - [5.7. `break` and `cont`](#57-break-and-cont)
  - [5.8. `switch` Statement](#58-switch-statement)
  - [5.9. `match` And Pattern-Matching](#59-match-and-pattern-matching)
  - [5.10. `throw` and `try`-`catch`](#510-throw-and-try-catch)
  - [5.11. `require` and `comply`](#511-require-and-comply)
  - [5.12. `with` and `be`](#512-with-and-be)
  - [5.13. `defer` Blocks](#513-defer-blocks)
  - [5.14. Omission](#514-omission)
- [6. Functions](#6-functions)
  - [6.1. Multiple Returns](#61-multiple-returns)
  - [6.2. Naming Returns](#62-naming-returns)
  - [6.3. Implicit Returns](#63-implicit-returns)
  - [6.4. Return Type Inference](#64-return-type-inference)
  - [6.5. Named Arguments](#65-named-arguments)
  - [6.6. Default Parameter Values](#66-default-parameter-values)
  - [6.7. Overloading](#67-overloading)
    - [6.7.1. Basic Overloading](#671-basic-overloading)
    - [6.7.2. Overloading with Named Parameters](#672-overloading-with-named-parameters)
    - [6.7.3. Overload Selection](#673-overload-selection)
    - [6.7.4. Dynamic Overload Dispatch](#674-dynamic-overload-dispatch)
  - [6.8. Variadic Arguments](#68-variadic-arguments)
  - [6.9. First-Class Functions](#69-first-class-functions)
  - [6.10. Anonymous Function](#610-anonymous-function)
  - [6.11. Explicit Captures](#611-explicit-captures)
  - [6.12. Trailing Parameters](#612-trailing-parameters)
  - [6.13. Expression Functions](#613-expression-functions)
  - [6.14. Retaining Local Variables](#614-retaining-local-variables)
  - [6.15. Pure Functions](#615-pure-functions)
  - [6.16. Fake Pure Functions](#616-fake-pure-functions)
  - [6.17. Signature Compatibility](#617-signature-compatibility)
  - [6.18. Binding](#618-binding)
  - [6.19. `ego` Function](#619-ego-function)
  - [6.20. Side-Channeling](#620-side-channeling)
  - [6.21. Omission](#621-omission)
- [7. Classes](#7-classes)
  - [7.1. Instanciation](#71-instanciation)
  - [7.2. `this`, `self`, `base` and `loft` Keywords](#72-this-self-base-and-loft-keywords)
  - [7.3. Constructors](#73-constructors)
  - [7.4. Constructor as Member Function](#74-constructor-as-member-function)
  - [7.5. Default Constructor](#75-default-constructor)
  - [7.6. Factory Constructors](#76-factory-constructors)
  - [7.7. Destructors](#77-destructors)
  - [7.8. Copy Constructor](#78-copy-constructor)
  - [7.9. Move Constructor](#79-move-constructor)
  - [7.10. Swap Constructor](#710-swap-constructor)
  - [7.11. Access Modifiers](#711-access-modifiers)
  - [7.12. Friend Access](#712-friend-access)
  - [7.13. Inheritance and Polymorphism](#713-inheritance-and-polymorphism)
  - [7.14. Virtual and Override](#714-virtual-and-override)
  - [7.15. Diamond Inheritance](#715-diamond-inheritance)
  - [7.16. Abstract Classes](#716-abstract-classes)
  - [7.17. Retaining Instance Variables](#717-retaining-instance-variables)
  - [7.18. Member Functions as First-Class Citizens](#718-member-functions-as-first-class-citizens)
  - [7.19. Mutable Constant Instances](#719-mutable-constant-instances)
  - [7.20. Class Reopening](#720-class-reopening)
  - [7.21. Class Unpacking](#721-class-unpacking)
  - [7.22. Anonymous Class Declaration](#722-anonymous-class-declaration)
- [8. Namespaces](#8-namespaces)
  - [8.1. Dotted Declaration](#81-dotted-declaration)
  - [8.2. Extension](#82-extension)
  - [8.3. Access Specifiers](#83-access-specifiers)
  - [8.4. Implicit Contents](#84-implicit-contents)
  - [8.5. Spilling Content](#85-spilling-content)
- [9. Importing and Exporting](#9-importing-and-exporting)
- [10. Enumerators](#10-enumerators)
  - [10.1. Enums as Classes](#101-enums-as-classes)
  - [10.2. Enum Members](#102-enum-members)
  - [10.3. Inheriting Enums](#103-inheriting-enums)
  - [10.4. Default Value](#104-default-value)
  - [10.5. Member Generation](#105-member-generation)
  - [10.6. Member Iteration](#106-member-iteration)
  - [10.7. Enums as Sum Types](#107-enums-as-sum-types)
- [11. Properties](#11-properties)
  - [11.1. Properties as Class](#111-properties-as-class)
  - [11.2. Read-Only And Write-Only Properties](#112-read-only-and-write-only-properties)
- [12. Operator Overloading](#12-operator-overloading)
  - [12.1. Operator Types](#121-operator-types)
  - [12.2. Custom Operators](#122-custom-operators)
  - [12.3. Auto Generation](#123-auto-generation)
  - [12.4. Overloading Operators for Functions](#124-overloading-operators-for-functions)
- [13. Literal Typing](#13-literal-typing)
- [14. Custom Type Modifiers](#14-custom-type-modifiers)
- [15. Macros](#15-macros)
  - [15.1. Declarative Macros](#151-declarative-macros)
  - [15.2. Attribute Macros](#152-attribute-macros)
  - [15.3. Engine Macros](#153-engine-macros)
- [16. Coroutines](#16-coroutines)
  - [16.1. Cooperative Usage](#161-cooperative-usage)
  - [16.2. Multiple Coroutine Tasks](#162-multiple-coroutine-tasks)
  - [16.3. Cancelling Coroutines](#163-cancelling-coroutines)
  - [16.4. Calling Non-Coroutine Functions Concurrently](#164-calling-non-coroutine-functions-concurrently)
- [17. Multi-threading](#17-multi-threading)
  - [17.1. Creating Threads](#171-creating-threads)
  - [17.2. Shared Memory](#172-shared-memory)
  - [17.3. Memory Ordering](#173-memory-ordering)
  - [17.4. Thread-Local Storage](#174-thread-local-storage)
  - [17.5. Thread Pools](#175-thread-pools)
- [18. Generics and Concepts](#18-generics-and-concepts)
  - [18.1. Generics](#181-generics)
  - [18.2. Concepts](#182-concepts)
  - [18.3. Concepts on Classes](#183-concepts-on-classes)
  - [18.4. `auto` and Constrained `auto`](#184-auto-and-constrained-auto)
  - [18.5. Concepts as Polymorphic Interfaces](#185-concepts-as-polymorphic-interfaces)
  - [18.6. Arbitrary Constraints](#186-arbitrary-constraints)
- [19. Array Operations](#19-array-operations)
  - [19.1. Element-wise Operations](#191-element-wise-operations)
  - [19.2. Array Pipeline](#192-array-pipeline)
  - [19.3. Placeholder Pipeline](#193-placeholder-pipeline)
  - [19.4. Custom Combinators](#194-custom-combinators)
- [20. Undefining Entities](#20-undefining-entities)
- [21. Interoperability with C](#21-interoperability-with-c)
- [22. Manual Memory Management](#22-manual-memory-management)
- [23. Reflection](#23-reflection)
  - [23.1. Type Introspection](#231-type-introspection)
  - [23.2. Dynamic Invocation](#232-dynamic-invocation)
  - [23.3. Reflecting Enum Types](#233-reflecting-enum-types)
- [24. Compile-time Evaluation](#24-compile-time-evaluation)
- [25. Tooling](#25-tooling)
  - [25.1. CLI Usage](#251-cli-usage)
    - [25.1.1. Create a Project](#2511-create-a-project)
    - [25.1.2. Build the project](#2512-build-the-project)
    - [25.1.3. Use toolchain without a Project](#2513-use-toolchain-without-a-project)
  - [25.2. Project Configuration](#252-project-configuration)
    - [25.2.1. Project Metadata](#2521-project-metadata)
    - [25.2.2. Build Targets](#2522-build-targets)
    - [25.2.3. Dependencies](#2523-dependencies)
    - [25.2.4. Configuring Dependencies](#2524-configuring-dependencies)
    - [25.2.5. Packaging and Publishing](#2525-packaging-and-publishing)
    - [25.2.6. Custom Repository](#2526-custom-repository)
    - [25.2.7. Language Presets](#2527-language-presets)
    - [25.2.8. Presets as Language Constructs](#2528-presets-as-language-constructs)
- [26. Plugin System](#26-plugin-system)
  - [26.1. Example Plugins](#261-example-plugins)
- [27. Appendix A - List of Keywords](#27-appendix-a---list-of-keywords)
- [28. Appendix B - List of Built-in Operators](#28-appendix-b---list-of-built-in-operators)
- [29. Appendix C - List of Syntax Markers](#29-appendix-c---list-of-syntax-markers)

## 1. Overview

### 1.1. What is Engenide?

Engenide is a statically-typed, RTTI-dynamics, compiled, interpreted, bytecode, omni-paradigm, fully-feature, systems-level+general-purpose, versatile programming language designed around freedom of expression. It deliberately removes arbitrary constraints to provide extensive flexibility to the language.

Engenide derives a lot of its features from other languages that have solved key problems, such as C, C++, C#, Python, Rust, Java, JavaScript, TypeScript, Go, Kotlin, Vala, Zig, Swift, Scala, Dart, and many, many others. It aims to bring greats of those worlds while maintaining interoperability between the features.

Engenide also aims to provide flexibility and expressiveness by inventing consistent semantics where traditional programming lacks. It is useful for ease of use and developer ergonomics, and also helps eliminate arbitrary constraints.

Engenide specification is available under the terms of MIT license. An implementation (e.g., a compiler, an interpreter, or collectively: an engine, along with othere toolchain) can be freely implemented based on the specification, and licensed under the terms of the implementer.

The default, defacto implementation, also licensed under the terms of MIT license, is also available for reference. It includes tools such as engine, linter and formatter, along with documentation for standard library.

### 1.2. Features

- **Statically Typed**: All values in Engenide has an associated type. Engenide does allow dynamic typing using `any`, or variants for controlled typing.
- **Omni Paradigm**: Multiple paradigms not only co-exist in Engenide, but also interact with each other in a seamless way. Supporting procedural, object-oriented, functional, generic, meta programming, collection-oriented, concurrent, DSL-oriented and many other paradigms.
- **All Level**: Engenide is both high level which provides great developer ergonomics and also a low level which provides performance and control.
- **Compiled**: Engenide source code can be compiled down to machine-level instructions, making it blazingly fast.
- **Interpreted**: Engenide source code can also be interpreted, even using a REPL, to allow fast prototyping for immediate results.
- **Hybrid**: Engenide source code can also be compiled to bytecode, which allows running the source code across any platform that has the Engenide Interpreter, or can be converted to the platform's binary using Engenide Compiler.
- **Customizability**: Engenide allows you to customize the language to fit it to the problem, not the other way around. It allows customizing operators (with custom operators), literals (typing), macros (syntax extender) and even type modifiers and semantics. All can be limited to be within a scope.
- **Flexibility**: Removal of artificial barriers allows expressive code to be written in any context, such as a property variable declared in a function scope.
- **Configurability**: Engenide is configurable to limit certain features to allow maximum safety and consistency in the codebase. These configuration is also detectable by the code, which allows developing library suitable for all configuration.
- **Safety**: All behavior in Engenide is defined, and undefined behavior (such as interoperability with C) can be traced back to grepable parts of the source code.
- **Embedability**: All of Engenide can be accessed as a library in C (or any language with C interoperability) which allows Engenide to be used as programmable configuration file.
- **C Interoperability**: Engenide code can be accessed by C, and vice versa, which allows Engenide code to be usable in an existing project.

### 1.3. Philosophy

The main philosophy of Engenide is *"If it makes sense semantically, it is allowed."* This means eliminating restrictions and to add semantic meaning to common operations that otherwise would be invalid.

This freedom, when mastered, will enable creation of beautiful program. It also has a guaranteed potential for misuse. Great care is required to proceed with the language, which makes up for a steeper learning curve.

For teams, Engenide provides several containments to limit the language's liberating features to provide a much tighter scope of collaboration.

### 1.4. Architecture

Engenide Engine is a composition of:

1. **Engenide Processor** (Frontend): Processes source code into bytecode. The processor can accept partial code as well, to facilitate interpreter. The bytecode is fully optimized from the source code for zero overhead.
2. **Engenide Compiler** (Backend #1): Compiles bytecode down to machine-level instructions. It also further optimizes the bytecode for efficient binary.
3. **Engenide Interpreter** (Backend #2): Interprets bytecode live if the instructions are partial, or JIT-compiles the bytecode for interpretation.
4. **Engenide Assembler**: Both Compiler and Interpreter (JIT mode) uses the Assembler to convert bytecode into machine-level instructions.
5. **Engenide Evaluator**: Engenide Processor and Interpreter (Live mode) uses Evaluator to evaluate bytecode. During processing, all code that are isolated from IO are evaluated during compile-time to allow minimal bytecode size. The runtime only needs to deal with IO related code.

## 2. Lexical Structure

### 2.1. Source Encoding

The source code must follow these basic encoding schemes:
- Source code must be in the UTF-8 encoding.
- Newlines must use Unix-style (Line Feed, `\n`) line ending.
- No BOM (Byte Order Mask) in source files.

This is solely to eliminate all complexities of detecting and converting encoding entirely. Though, an implementation of the compiler/interpreter (collectively: engine) may normalize encodings automatically.

### 2.2. Whitespace

Whitespaces, unless in string literals, is only used as token separator and is otherwise insignificant. They are used for aesthetic styling of the source code to make them more readable.

```eng
let variable = value;
```

Here, `let` and `variable` are separated by space. Though, space between the `=` is insignificant.

Whitespaces are useful for code aesthetics, such as indentation, line breaks, and alignment.

```eng
fn main() {
    let country = "Wonderland";
    let state   = "Utopia";
    let city    = "Punkville";

    let address = country + ", "
                + state   + ", "
                + city;

    io.println("Address: ${address}");
};
```

### 2.3. Comments

Comments are used to document the source code. They are ignored by the engine.

Two types of comments are supported:

1. Single-line comments: Single-line comments start with `#` and end at the end of the line.

```eng
# This is a single-line comment.
```

2. Multi-line comments: Multi-line comments start with `#{` and end at `}#`.

```eng
#{
    This is a multi-line comment.
}#
```

Multi-line comments can be nested. The engine counts the occurances of `#{` and `}#` to allow nesting multi-line comments.

```eng
#{
    This is the first-half of the outer multi-line comment.
    #{
        This is the inner multi-line comment.
    }#
    This is the second-half of the outer multi-line comment.
}#
```

This allows super quick comment-out of a block of code which alreacy contains a multi-line comment.

```eng
#{

#{
    @brief Performs integer division and returns both the quotient and remainder.

    Given a numerator and a denominator, this function computes:
        quotient = numerator / denominator
        remainder = numerator %% denominator

    @param numerator    The integer to be divided.
    @param denominator  The integer divisor; must not be zero.
    @return quotient    The integer result of the division.
    @return remainder   The positive remainder of the division.

    @except eng.std.except.invalid_argument
        Thrown when the denominator is zero, because division by zero
        is undefined and unacceptable behavior.

    @note The remainder is always positive due to the wrapping modulo operator (%%),
        which ensures consistent behavior even for negative numerators.

    @example
        ```eng
        # Basic usage with named returns
        let result = divide(29, 12);
        # result.quotient -> 2
        # result.remainder -> 5

        # Tuple unpacking
        let (q, r) = divide(17, 5);
        # q -> 3
        # r -> 2

        # Discarding remainder
        let (q, _) = divide(100, 9);
        # q -> 11
        ```
}#
fn divide(numerator: int, denominator: int) -> quotient: int, remainder: int {
    if denominator == 0 {
        throw eng.std.except.invalid_argument("Denominator cannot be zero.");
    }

    return quotient = numerator / denominator, remainder = numerator %% denominator;
};

}#
```

#### 2.3.1. Comment Evaluation

Engenide code inside the fence block of multi-line comments are compiled and evaluated by default. Linting and formatting are also applied to the code inside the comment block.

```eng
#{
    ```eng
    let x = 10;
    let y = 20;
    let sum = x + y;
    assert!(sum == 30);
    ```
}#
```

If the code inside the comment block produces compile-time or runtime errors, those will be treated as warnings inside the comment block.

```eng
#{
    ```eng
    let x = 10;
    let y = "20";
    let sum = x + y;
    assert!(sum == 30); # Fails at compile-time, produces compile-time warning

    let a = 5;
    let b = 10;
    let product = a * b;
    assert!(product == 60); # Fails at runtime, produces compile-time warning (evaluation is done at compile-time)
    ```
}#
```

To disable evaluation of code inside the comment block, use `eng(.process = false)` on the comment block.

```eng
#{
    ```eng(.process = false)
    let x = 10;
    let y = "20";
    let sum = x + y;
    assert!(sum == 30); # No error/warning produced
    ```
}#
```

Errors can be treated as errors when `.strict = true` is used.

```eng
#{
    ```eng(.strict = true)
    let x = 10;
    let y = 20;
    let sum = x + y;
    assert!(sum == 40); # Fails at runtime, produces compile-time error
    ```
}#
```

### 2.4. Words

Keywords and identifiers follow the same typing conventions:

1. Case-sensitivity: Words are case-sensitive. E.g., `Hello` and `hello` are different words.
2. Start characters: Words must start with `A`-`Z`, `a`-`z` or `_`.
3. Continuation characters: Words can continue with `A`-`Z`, `a`-`z`, `_` or `0`-`9`.

Keywords are words that are reserved and have special meaning. They cannot be used as identifiers.

Identifiers are words that can be used to name entities (such as variables, data types, functions, namespaces, etc.).

```eng
let variable_name = 1;  # Variable declaration
fn function_name() {};  # Function declaration
class structure_name {};   # Structure declaration
```

Here, `let`, `fn` and `class` are keywords while `variable_name`, `function_name` and `structure_name` are identifiers.

Words may also contain Unicode characters. I.e., words may start with Unicode characters with Unicode character class XID_Start and continue with XID_Continue.

```eng
let 半径 = 5.3;

fn वृत्त_का_क्षेत्रफल(त्रिज्या: float) -> float {
    return math.pi * त्रिज्या  2;
};

class круг {
    let радиус: float;
    let позиција_x: float;
    let позиција_y: float;

    fn обем() {
        return 2 * math.pi * радиус;
    };
};
```

Note: Emojis does not contain Unicode character class XID_Start or XID_Continue, hence, they cannot be used as identifiers.

#### 2.4.1. Backtick Words

Enclosing backticks (`` ` ``) around a prose can also be used as a word. This can be used to eliminate naming of entities whose names does not matter, such as test functions.

```eng
import testing: eng.ext.testing;

fn square(num: float) {
    return num  2;
};

@testing.register_test
fn `Test whether square(2) returns 4.`() {
    let result = square(2);
    if (result == 4) {
        io.println("Success: square(2) returned 4.");
    } else {
        io.println("Failure: square(2) did not return 4, but returend ${result}.");
    }
}

fn main() {
    testing.run_tests();
}
```

### 2.5. Operators

An operator is a composition of one or more of the following characters:

```eng
~ ! % ^ & * - + = [ ] \ | < > / ?
```

As well as Unicode characters with Unicode character class Math.

```eng
⌊x⌋ # Floor Operator (if defined)
```

Note: Emojis does not contain Unicode character class Math, hence, they cannot be used as operators.

This allows tighter parsing with the defined set, as well as opportunity to compose a custom operator for domain-specific use cases.

Certain patterns for custom operators are not overloadable due to conflict with syntax markers, such as standalone `[ x ]` for an array declaration.

### 2.6. Punctuations

Punctuations (aka Delimiters) are single-character tokens, specifically any of:

```eng
@ ( ) { } : ; , .
```

These symbols have a special meaning, just like keyword, and are not treated as operators. These serve as syntax markers.

Several operator-like characters may also appear as punctuations, such as array (`[` and `]` for `[ 1, 2, 3 ]`), return arrow (`->` and `=>` for `fn function() -> return_type => expression;`), etc., but many don't overlap with operators in expression.

### 2.7. Literals

Literals represent fixed-values in the source code.

#### 2.7.1. Character Literals

Character literals are identical to string literals with a few distinctions:

1. Character literals are enclosed in `'` as oppose to `"`.
2. Character literals must be a single UTF-32 character.
3. Character literals cannot embed raw or formatted segments like a string literal.

For example,

```eng
'a'
'\n'
'\66'
'🎔'
```

Character literals can also be implicitly casted from/to integers, where the integer is represented the Unicode codepoint.

#### 2.7.2. Boolean Literals

There are two boolean literals: `true` and `false` (both lowercase). These represents true or false values in boolean type.

Boolean literals can also be implicitly casted from/to integers, where non-zero integer is represented as true.

#### 2.7.3. Pointer Literal

There is one pointer literal: `nullptr` (lowercase). It represents null value for pointers to indicate that they don't point to anything.

Pointer literal can also be implicitly casted from/to integers, where the nullptr literal represents zero.

#### 2.7.4. Nullable Literal

There is one null literal: `null` (lowercase). It represents null value for nullable types to indicate that they do not hold a value.

Nullable literall cannot be casted from/to integers, as they are only an indication for no-value state.

### 2.8. Numeric Literals

#### 2.8.1. Typing Convention

Numeric literals follows these typing conventions:

1. Case-insensitivity: Numeric literals are case-insensitive. E.g., `0x2e9c` and `0x2E9C` are same numbers.
2. Start characters: Numeric literals must start with `0`-`9`.
3. Continuation characters: Numeric literals can continue with `0`-`9`, `A`-`Z`, `a`-`z`, `.` or `'`.
4. End characters: Numeric literals must end with `0`-`9`, `A`-`Z` or `a`-`z`.
5. Separators: Numeric literals can contain separator characters (`'`) to improve readability of long numbers, but are ignored by the engine. E.g., `0i0011'1001'1101'0111` and `0i0011100111010111` are same numbers.

```eng
123         # Regular decimal number
0d456       # Also decimal number
12.25       # Also decimal number
789'012'345 # Decimal number with separators
0i1101      # Binary numner
0o646       # Octal number
0x389d      # Hexadecimal number
```

#### 2.8.2. Classification

Numeric literals are classified into two types:

1. Integeral literals: These literals represents integeral values and cannot contain the decimal point (`.`).
2. Floating-point literals: These literals represents floating-point values and must contain one decimal point (`.`) in between the digits.

```eng
135         # Integer literal
13.5        # Floating-point literal
```

Scientific notation is absent in floating-point literals to avoid ambiguity when using non-decimal base in floating-point literals. As a side-effect, it simplifies parsing and encourages the use of exponential operator `**`, which does allow specifying the base for exponent.

```eng
1.23456 * 10 ** 3   # Same as 1.23456e3 or 1234.56
```

#### 2.8.3. Base Specification

Numeric literals can be represented using different bases by providing a prefix. The default base is Decimal.

1. Binary: Base prefix is `0i` and can only contain digits `0` and `1`. E.g., `0i11010011`.
2. Octal: Base prefix is `0o` and can only contain digits `0`-`7`. E.g., `0o137`.
3. Decimal: Base prefix is none or `0d` and can only contain digits `0`-`9`. E.g., `0d390`.
4. Hexadecimal: Base prefix is `0x` and can only contain digits `0`-`9`, `A`-`F` or `a`-`f`. E.g., `0x493f`.

The choice of `0i` over `0b` in binary notation comes from the fact that escape sequence `\b` is reserved for backspace. Numbers with different bases also shows up in escape sequences, so this compromise aims to maintain this consistency.

#### 2.8.4. Special Numeric Literals

There are two special numeric literals for floating-point types: `inf` and `nan` (both lowercase). These represents infinity and not-a-number values respectively.

### 2.9. String Literals

String literals start and end with `"`. Enclosing characters within the delimiters are part of the string, including line endings. String literals are packed and are encoded in UTF-8.

```eng
"This is a string"
```

#### 2.9.1. Escape Sequence

Escape sequences in string literal allows embedding special bytes in the string.

Escape sequences include:

- `\a`: Bell (`\x07`).
- `\b`: Backspace (`\x08`).
- `\e`: ESC (`\x1B`).
- `\f`: Form Feed (`\x0C`).
- `\n`: Line Feed (`\x0A`).
- `\r`: Carriage Return (`\x0D`).
- `\t`: Tab (`\x09`).
- `\v`: Vertical Tab (`\x0B`).

Escaping delimiter symbols:

- `\\`: Escaped backslash.
- `\'`: Escaped quotation mark.
- `\"`: Escaped double quotation mark.
- `\#`: Escaped hash symbol (for escaping raw string segment).
- `\$`: Escaped dollar symbol (for escaping interpolated string segment)

Along with specifying number for the bytes in the literal:

- `\iN`: Binary number for the bytes. E.g., `\i01000001` for `A`.
- `\N` or `\dN`: Decimal number for the bytes. E.g., `\66` for `B`.
- `\oN`: Octal number for the bytes. E.g., `\o102` for `C`.
- `\xN`: Hexadecimal number for the bytes. E.g., `\x44` for `D`.
- `\uN`: A Unicode codepoint. E.g., `\u273f` for `✿`.

#### 2.9.2. Raw Segments

Raw string literals is not a special type of string literal. Rather, the raw segment of the string literal is embedded within a regular string literal. This allows composability for string literals.

The syntax for raw string segment is `#delimiter{Raw string contents.}delimiter#` where delimiter is optional and can be empty.

Raw string segment can be useful to embed string content with multiple escaping characters.

In the raw string segment, the parsing of escape sequence, raw segmentation and interpolation segmentation are disabled.

```eng
"#{This is a raw\nstring segment.}#" # Same as "This is a raw\\nstring segment."
```

```eng
"This is a\nregular string. #{This is an embedded\nraw string segment.}# This is continuation\nof regular string."
```

```eng
"#xyz{Delimiters\nallow #{unambigious termination}# of\nraw string segment}xyz#"
```

Raw string segment can be escapde with a leading `\`.

```eng
"\#{This is not a raw\nstring segment.}#"
```

#### 2.9.3. Interpolation Segments

Interpolated string literals is also not a special type of string literal and is embedded in a regular string literal. The interpolated string segment allows embedding expressions in the string to easily convert it to string and concatenate it in between.

Interpolated string segment starts with `$` and follows these syntaxes:

1. Expression: The expression syntax is `"${expression}"`. It allows embedding expressions in the string. The expression must result in the type that is string-formattable or castable to string without format specification support.

```eng
"The result of 1 + 1 is ${1 + 1}." # Results in "The result of 1 + 1 is 2."
```

2. Formatted Expression: The formatted expression syntax is `$(format){expression}.` It allows embedding expressions in the string. The expression must result in the time that is string-formattable.

```eng
"The result of 2.25 + 0.125 is $(.2f){2.25 + 0.125}." # Results in "The result of 2.25 and 0.125 is 2.37."
```

3. Identifier: The identifier syntax is `$identifier`. It allows embedding identifier in the string. The identifier must result in the type that is string-formattable or castable to string without format specification support.

```eng
"The distance is $distance." # Results in "The distance is 4.325." if distance is 4.325.
```

Nesting both the format and expression is possible.

```eng
"The distance is $(.${precision}f){distance}." # Results in "The distance is 4.32." if distance is 4.32XXX (but not grater than 4.325) and precision is 2.
```

```eng
"This statement is ${with if (truth) be "true"; else be "false"}." # Results in "This statement is true." if truth is true, else "This statement is false."
```

Interpolated string segment can be escaped with a leading `\`.

```eng
"This is \${not interpolated}"
```

#### 2.9.4. Implicit Concatenation

When two or more subsequent string literals are next to each other, they are implicitly concatenated into one.

```eng
"This is a string.\n" "This is part of the same string.\n" "So is this." # Same as "This is a string.\nThis is part of the same string.\nSo is this."
```

This eliminates the need of explicit string concatenation with `+` operator when both the operands are strings.

## 3. Variable Declaration

Variable declaration are used to introduce new variables in the current scope. Variables can be declared by using the `let` keyword using the syntax:

```eng
let identifier: type = value;
let identifier: type;
let identifier = value;
```

The type or the value can be omitted. When the type is omitted, the variable's type is inferred from the value. When the value is omitted, the variable is initialized to default value.

### 3.1. Multiple Declaration

Multiple variables can be declared in a single statement by separating the variables with a comma.

```eng
let a: type = value, b: type = value, c: type = value;
```

When type or value is provided only for the last variable declared, it is assigned to all the variables in the declaration.

```eng
let a, b, c: int = 2;
```

### 3.2. Shadowing

Variables in function scope can be shadowed by other variable of same name in same scope.

```eng
import fs: eng.std.filestream;
import json: nlohmann.json;

let input = fs.input("settings.json");
let input = json.parse(input); # input is now a json object
let input = input[ "indent" ] as int; # input is now int (0 if no indent entry)
let input = input * 3.4; # input is now float
```

### 3.3. Discarded Variable

Variable with the name `_` marks that the value is discarded.

```eng
let quotient, _ = divide(10, 20); # Discard remainder value
```

## 4. Types

The type system is static. Every value has an associated type. Types are not differenciated between primitive types vs. non-primitive types, as every type is treated the same.

### 4.1. Integer Types

Integer types are categorized in two types: signed and unsigned.

Signed integer types holds whole numbers, while unsigned integer types holds zero or positive numbers.

There are many forms of integer types that covers signed vs. unsigned and width of the integer.

| Type     | Signedness | Width (bits)       |
| -------- | ---------- | ------------------ |
| `int`    | Signed     | 32                 |
| `int8`   | Signed     | 8                  |
| `int16`  | Signed     | 16                 |
| `int32`  | Signed     | 32                 |
| `int64`  | Signed     | 64                 |
| `uint`   | Unsigned   | 32                 |
| `uint8`  | Unsigned   | 8                  |
| `uint16` | Unsigned   | 16                 |
| `uint32` | Unsigned   | 32                 |
| `uint64` | Unsigned   | 64                 |
| `sint`   | Signed     | 32                 |
| `sint8`  | Signed     | 8                  |
| `sint16` | Signed     | 16                 |
| `sint32` | Signed     | 32                 |
| `sint64` | Signed     | 64                 |
| `word`   | Signed     | Platform Dependent |
| `uword`  | Unsigned   | Platform Dependent |
| `sword`  | Signed     | Platform Dependent |

```eng
let position_x: int = 32;
```

Fun fact: `int` == `int32` == `sint` == `sint32`. And in most platforms, `int` == `int32` == `sint` == `sint32` == `word` == `sword`.

### 4.2. Floating-point Types

Floating-point types holds real numbers.

There are many forms of floating-point types that cover various width, ranges and precisions.

| Type       | Precision           | Width (bits) |
| ---------- | ------------------- | ------------ |
| `float`    | Double precision    | 64           |
| `float16`  | Half precision      | 16           |
| `float32`  | Single precision    | 32           |
| `float64`  | Double precision    | 64           |
| `float128` | Quadruple precision | 128          |

### 4.3. Character Types

The `char` type holds one Unicode scalar value. Its width is 32 bites and holds the Unicode codepoint directly.

```eng
let ascii_character: char = 'a';
let unicode_character: char = '💖';
```

### 4.4. Boolean TYpes

The `bool` type holds either `true` or `false`. Its width is 8 bits but it cannot sore any value other than those two states.

```eng
let enabled: bool = true;
let success: bool = false;
```

### 4.5. String

Strings represents sequence of characters. They are encoded in UTF-8, and unlike an array of characters, they are packed to minimize memory usage from array of UTF-32 characters.

```eng
let str: string = "Hello, World!";
```

`string` supports seamless packing and unpacking, and iteration.

```eng
let first_letter = str[ 0 ]; # 'H'
let last_letter = str[ -1 ]; # '!'

for (let character in str) { # Iterate over characters
    io.println("Character: ${character}");
}
```

### 4.6. Any Type

The `any` type is a type that can hold values of any data type. It dynamically stores the type information along with the value. The type can be compared dynamically to safely retrieve the value.

```eng
let value: any = 5;
value = 11.5;
value = 'a';
value = false;
value = "string";

if (value is string) {
    let str = value as string;

    io.println("String: ${str}");
}

if (let integer as int = value) {
    io.println("Integer: ${integer}");
}
```

### 4.7. Variants

Variants can be defined by combining two types. A variant holds values of the specified types.

```eng
let number: int | float = 20;
if number is int {
    io.println("Number is an integral value");
} else {
    io.println("Number is an floating-point value");
}
```

Two variant types can be combined with set intersection operator `&` or set union operator `|`.

```eng
let value: (int | float) & (float | string); # value is of type float
let value: (int | float) | (float | string); # value is of type int | float | string
```

### 4.8. Type Conversion

#### 4.8.1. Conversion Types

There are two types of type conversion:

1. Implicit Cast: Define a `cast` function to convert one type to another type implicitly.

```eng
class vector2d {
    let x: float;
    let y: float;
};

class complex {
    let real: float;
    let imag: float;
};

cast(v: vector2d) -> complex {
    return (.real = v.x, .imag = v.y);
};

fn main() {
    let position = vector2d(.x = 10, .y = 20);
    let complex_number: complex = position; # Implicit conversion
};
```

2. Explicit Cast: Define a `into` function to convert one type to another type explicitly.

```eng
class vector2d {
    let x: float;
    let y: float;
};

class complex {
    let real: float;
    let imag: float;
};

into(v: vector2d) -> complex {
    return (.real = v.x, .imag = v.y);
};

fn main() {
    let position = vector2d(.x = 10, .y = 20);
    let complex_number = position as complex; # Explicit conversion
};
```

Defining only `cast` function allows both implicit and explicit conversion. Defining only `into` function allows only explicit conversion.

#### 4.8.2. Numeric Conversion

Integer to floating-point conversion is implicitly allowed. Floating-point to integer conversion is explicitly allowed.

```eng
let integer_value: int = 10;
let float_value: float = integer_value; # Implicit conversion
let another_integer_value: int = float_value as int; # Explicit conversion
```

Float value of infinity can be converted to integer, resulting in the maximum value of the integer type, while negative infinity results in the minimum value of the integer type.

```eng
let inf_float: float = inf;
let max_int: int = inf_float as int; # Results in 2147483647
let neg_inf_float: float = -inf;
let min_int: int = neg_inf_float as int; # Results in -2147483648
```

Float value of nan can be converted to integer, resulting in zero.

```eng
let nan_float: float = nan;
let zero_int: int = nan_float as int; # Results in 0
```

#### 4.8.3. Automatic Multi-conversion

When conversion from type a to type b is defined, and conversion from type b to type c is defined, conversion from type a to type c is automatically defined.

```eng
class type_a {
    let value: int;
};

class type_b {
    let value: float;
};

class type_c {
    let value: string;
};

cast(a: type_a) -> type_b {
    return (.value = a.value as float);
};

cast(b: type_b) -> type_c {
    return (.value = "Value: ${b.value}");
};

fn main() {
    let a = type_a(.value = 42);
    let c: type_c = a; # Automatically converts type_a -> type_b -> type_c

    io.println(c.value); # Outputs: Value: 42.0
};
```

This is only applied for implicit cast conversion. Explicit conversion must be defined separately. For ambiguous conversions, explicit conversion must be used.

### 4.9. Obtaining Size of Types

The `sizeof` keyword is used to obtain the size of a type in bytes.

```eng
let int_size = sizeof int;         # 4
let float64_size = sizeof float64; # 8
let char_size = sizeof char;       # 4
```

### 4.10. Modifiers

#### 4.10.1. Constants

A constant type's value does not change after creation.

```eng
let a: int! = 2;
let b: ! = 3.4; # Type inferred as float!
let c! = 'z';   # Type inferred as char!
```

Reassignment is not allowed on constants.

```eng
a = 3; # Errors out
```

#### 4.10.2. Pointers

A pointer type holds an address of another variable or memory.

```eng
let value = 2;
let pointer: int* = addr value;
*pointer = 4; # Also updates value
let other_pointer* = addr value;
```

Memory can be managed using the `alloc` and `dealloc` statements.

```eng
let pointer = alloc int; # Automatically initialized to 0
*pointer = 3;
dealloc pointer;
```

The `alloc` statement can also take an integer as number of bytes to allocate a void pointer of arbitrary size.

```eng
let pointer = alloc 4; # allocates void* of 4 bytes
*(pointer as int*) = 3;
dealloc pointer;
```

Reallocation is also possible with `realloc`.

```eng
let pointer = alloc 4;
*(pointer as int*) = 3;
realloc pointer, 8; # or `realloc pointer, int64`
*(pointer as int64*) = 7;
```

#### 4.10.3. References

A reference type refers to another variable or memory.

```eng
let value = 3;
let reference: int& = value;
reference = 6; # Updates value
```

References must always point to variable that is guaranteed to live longer than the reference itself, and they cannot be made to point other variables after declaration.

#### 4.10.4. Nullables

A nullable type holds a state whether a value is held and the value it holds.

```eng
let a: int?;
let b: int? = 20;
let c: int? = null;
```

Accessing a nullable type that does not hold a value throws `null_reference` exception.

```eng
let d = a + b + c;
```

Checking for a value existence is possible by comparing it to `null`.

```eng
if a == null {
    a = 10;
}

if b == null {
    b = 20;
}

if c == null {
    c = 30;
}
```

A not-null assertion operator `?!` is used to throw `null_reference` exception if no value is present.

```eng
a?!;
```

A nullable operator `?` is used to perform operations that implicitly converts into `null` if any operation is `null`.

```eng
let e = a +? b +? c; # e is of nullable type `int?`
```

It also works with chained member access.

```eng
class calculator {
    fn add(a: int, b: int) -> int {
        return a + b;
    };
};

let calc: calculator? = null;

let result = calc?.add(10, 20);
```

Null-coalescing operator `??` performs a conditional branch to evaluate an expression if the variabe does not contain any value.

```eng
let result = calc?.add(10, 20) ?? 30; # result is of not-nullable type `int`
```

Exception-coalescing operator `!!` performs a conditional branch to evaluate an expression if the variable does not throw an exception.

```eng
let result = calc?!.add(10, 20) !! 30; # result is of type `int`
```

Exception-to-null operator `!?` performs a conditional branch to convert an exception into null.

```eng
let result = calc?!.add(10, 20)!?; # result is of nullable type `int?`
```

#### 4.10.5. Reference-Counting

A reference-counting type automatically manages the memory of the value it holds by counting the number of references to it. When the reference count drops to zero, the memory is automatically deallocated.

```eng
{
    let value: int&& = 42;
    {
        let another_ref: int& = value;
        io.println("Value inside inner scope: ${*another_ref}");
    } # another_ref goes out of scope here, but value is still valid
    io.println("Value inside outer scope: ${*value}");
} # value goes out of scope here, memory is deallocated
```

#### 4.10.6. Moving Types

A moving type transfers the ownership of the value it holds when assigned or passed to a function. After the transfer, the original variable becomes inaccessible.

```eng
fn take_ownership(data: string) {
    io.println("Data received: ${data}");
};

fn main() {
    let message: string^ = "Hello, World!";
    take_ownership(message);
    # io.println("Message: ${message}"); # Error: message is no longer accessible
};
```

#### 4.10.7. Unique Moving Types

A unique moving type ensures that there is only one reference to the value it holds at any given time. This is useful for managing resources that should not be shared, or to ensure thread-safety.

```eng
fn main() {
    let resource: string^^ = "Unique Resource";

    let another_resource = resource; # Ownership is transferred
    # io.println("Resource: ${resource}"); # Error: resource is no longer accessible

    io.println("Another Resource: ${another_resource}");

    let borrowed_resource: string! & = another_resource; # Borrowing the resource as constant reference
    io.println("Borrowed Resource: ${borrowed_resource}");

    {
        let inner_resource: string& = another_resource; # Borrowing the resource as mutable reference
        io.println("Inner Resource before modification: ${inner_resource}");

        # Cannot access another_resource while inner_resource is borrowed as mutable reference
        # io.println("Another Resource: ${another_resource}"); # Error
    }

    # Now another_resource can be accessed again
    io.println("Another Resource after inner scope: ${another_resource}");
};
```

#### 4.10.8. Swapping Types

One of a cleaver way to implement efficient resource management while still keeping invariants intact is to swap the resources. Using moving type allows this pattern to be implemented easily.

```eng
fn main() {
    let message1: string~ = "Hello";
    let message2: string = "World";

    message2 = message1; # Swap message1 and message2

    io.println("Message 1: ${message1}"); # Outputs "World"
    io.println("Message 2: ${message2}"); # Outputs "Hello"
};
```

#### 4.10.9. Polymorphic Types

A polymorphic type allows a variable to hold values of different derived types from a common base type.

```eng
class animal {
    fn speak() -> string {
        return "Some sound";
    };
};

class dog: animal {
    fn speak() -> string {
        return "Woof!";
    };
};

class cat: animal {
    fn speak() -> string {
        return "Meow!";
    };
};

fn main() {
    let my_pet: animal% = dog();
    io.println("My pet says: ${my_pet.speak()}"); # Outputs "Woof!"

    my_pet = cat();
    io.println("My pet now says: ${my_pet.speak()}"); # Outputs "Meow!"
};
```

#### 4.10.10. Combining Modifiers

Modifiers can be combined to create complex behaviors for types.

```eng
let value: int = 10;
let pointer: int* = addr value;

let const_pointer: int! * = addr value; # Constant pointer to constant integer
let pointer_to_pointer: int* * = addr pointer;
let ref_to_pointer: int* & = pointer;
let nullable_pointer: int* ? = pointer;
```

Certain combinations are not allowed, such as modifying a reference type or a unique moving type.

```
let invalid_ref: int& ! = value; # Error: Cannot modify a reference type
let invalid_unique: int^^ * = addr value; # Error: Cannot modify a unique moving type
```

### 4.11. Arrays

Array is a container for storing multiple values. Arrays are flexible as they can be dynamically resized if their size is not constant, and they can also store values of mixed data types.

Note: We use space inside `[ ]` is required due to limitation in the tokenizer. A continuous `[]` is treated as a single token, and a single `[]` has no meaning by default. We also use space inside it to prevent conflict with `[-1]`, which is treated a `[-` `1` and `]` tokens.

#### 4.11.1. Typed and Untyped

A typed array specifies exactly what type each element must be.
An untyped array has no such restriction and can hold any mixture of types.

```eng
let scores: int[ ] = [ 10, 15, 20 ];    # typed, dynamic-sized
let values: [ ]    = [ 42, 3.14, 'z' ]; # untyped, dynamic-sized
```

Note: Untyped array are equivalent to `any[ ]` as it uses the `any` type as default. This allows composition of different types in the array.

#### 4.11.2. Static-Sized and Dynamic-Sized

A static-sized array has a fixed number of elements.
A dynamic-sized array can grow or shrink at runtime.

```eng
let grid:  int[ 4 ]  = [ 1, 2, 3, 4 ]; # typed, static-sized
let pair:  [ 2 ]     = [ true, 'A' ];  # untyped, static-sized
let names: string[ ] = [ ];            # typed, dynamic-sized
let list:  [ ]       = [ ];            # untyped, dynamic-sized
```

If a static-sized typed array is initialized with fewer elements than its size, the remaining elements are default-initialized.

#### 4.11.3. Accessing Arrays

Elements of the array can be accessed using the subscript operator (`[ ]`) which takes a zero-index to locate the element. The index can be negative as well, where `-1` starts counting backwards from the last.

```eng
let letters     = [ 'a', 'b', 'c', 'd', 'e' ];
let first       = letters[ 0 ];  # 'a'
let second      = letters[ 1 ];  # 'b'
let last        = letters[ -1 ]; # 'e'
let last_second = letters[ -2 ]; # 'd'
```

A subarray can be made by using an int array of indices as the subscript.

```eng
let mid = letters[ [ 1, 2, 3 ] ]; # [ 'b', 'c', 'd' ]
```

Note: Invalid index throws `index_out_of_range` exception.

#### 4.11.4. Resizing Arrays

If the array is dynamically-sized, they can be resized in runtime. There are a few functions, mainly:

1. Insertion: using `array.insert(index, value)` to insert a value at index.
2. Removal: using `array.remove(index)` to remove a value at index.
3. Resizing: using `array.resize(new_size)` to resize the array.

A few helper functions also exists, such as:

1. Insertion at ends: using `array.insert_front(value)` and `array.insert_back(value)`.
2. Removal at ends: using `array.remove_front()` and `array.remove_back()`.

```eng
let values = [ 1, 3, 3, 4, 5 ];

values.insert(1, 2); # values is now [ 1, 2, 3, 3, 4, 5 ]
values.remove(2);    # values is now [ 1, 2, 3, 4, 5 ]

values.resize(10);   # values is now [ 1, 2, 3, 4, 5, 0, 0, 0, 0, 0 ]
```

#### 4.11.5. Count

The size of the array can be obtained using `array.count`.

```eng
let values = [ 1, 2, 3, 4, 5 ];
let values_count = values.count;
```

#### 4.11.6. Existance and Iteration

The `in` keyword can be used to check of an element exists in the array.

```eng
if (element in array) {
    io.println("Element exists in the array.");
}
```

The opposite can be written as:

```eng
if (element !in array) {
    io.println("ELement does not exist in the array.");
}
```

It can also be used to iterate over the array.

```eng
for (let element in array) {
    io.println("Element: ${element}");
}
```

#### 4.11.7. Array Range Generator

Range Generator allows generating array of incremental sequence.

```eng
begin:end:step
```

- begin: Starting value for the sequence.
- end: Stopping value (exclusive) for the sequence.
- step: Incremental value added after each element.

In case begin is greater than end, the range will be empty if step is positive, otherwise it will decrement.

The parameters are optional and can be omitted. The default values are:

- begin: 0 if step is positive, otherwise -1.
- end: infinity if step is positive, otherwise -infinity.
- step: 1.

If the step is omitted, the generator can also be written in the form:

```eng
begin:end
```

Any enumerable type may be used for generation:

```eng
let indices = 0:5;        # [ 0, 1, 2, 3, 4 ]
let odds    = 1:10:2;     # [ 1, 3, 5, 7, 9 ]
let reverse = 9:-1:-1;    # [ 9, 8, 7, 6, 5, 4, 3, 2, 1 ]
let letters = 'a':('z'+1) # [ 'a', 'b', 'c', ... 'x', 'y', 'z' ]
```

Or when passing it to the subscript:

```eng
let values    = [ 1, 2, 3, 4, 5 ];
let subvalues = values[ 1:4 ];  # [ 2, 3, 4 ]
let reversed  = values[ ::-1 ]; # [ 5, 4, 3, 2, 1 ]
```

#### 4.11.8. Array Repeat Generator

Repeat Generator allows array to be repeated a fixed number of times.

```eng
[ array ] * count
```

```eng
let repeats = [ 1, 2, 3 ] * 3; # [ 1, 2, 3, 1, 2, 3, 1, 2, 3 ]
```

Or when passing it to the subscript:

```eng
let values   = [ 1, 2, 3, 4, 5 ];
let repeated = values[ [ 2 ] * 5 ]; # [ 3, 3, 3, 3, 3 ]
```

In case of zero or negative value of `count`, the array will be empty.

```eng
let repeats = [ 1, 2, 3 ] * -2; # [ ]
```

#### 4.11.9. Array Generator Expression

Generation expression allows custom generation of array using `emit`.

```eng
# Prime numbers from 2 to 100
let primes = [ for i in 2:101 {
    if is_prime(i) {
        emit i;
    }
} ];
```

A generator expression may also emit multiple values, and can be composed within a regular array elements.

```eng
let values = [ 1, 2, for i in 3:11 {
    if i % 2 == 0 {
        emit i;
    }
    if i % 3 == 0 {
        emit i;
    }
}, 11, 12, 13 ]; # values is [ 1, 2, 3, 4, 6, 6, 8, 9, 10, 11, 12, 13 ], with 6 being emitted twice
```

#### 4.11.10. Array Packing and Unpacking

Array supports packing and unpacking of elements if the size of the array is fixed.

```eng
let pair: int[ 2 ] = [ 10, 20 ];
let (a, b) = ( pair... ); # Unpack into a tuple
```

```eng
let data = (10, 20);
let pair: [ ] = [ data... ]; # Pack into an array
```

Packing can also happen in parameters using `...` operator.

```eng
fn sum(...values: int) -> int {
    let total = 0;
    for (let value in values) {
        total += value;
    }
    return total;
};

fn main() {
    let result = sum(1, 2, 3, 4, 5); # result is 15
};
```

### 4.12. Tuples

A tuple is a fixed, ordered grouping of values of any data type.

```eng
let tuple: (int, float) = (2, 3.5);
```

Tuple value can be accessed using `tuple[ index ]`.

```eng
let float_value = tuple[ 0 ];
```

It also supports negative indexing and subarray access.

```eng
let float_value = tuple[ -1 ];
let sub_tuple   = tuple[ [ 0, 1 ] ];
let rev_tuple   = tuple[ ::-1 ];
```

Tuples support unpacking. This is used to split the values into variables.

```eng
let (a, b) = tuple;
```

Note: Parenthesis are required for unpacking. If omited,

```eng
let a, b = tuple;
```

This code creates two tuples of same value, not unpacking of a tuple.

Tuples members can also be named for easier access.

```eng
let person: (name: string, age: int) = (.name = "Alice", .age = 30);
let name = person.name;
let age  = person.age;
```

Tuple also supports unpacking into an array.

```eng
let tuple: (int, float, char) = (10, 20.5, 'z');
let array: [ ] = [ tuple... ]; # array is [ 10, 20.5, 'z' ]
```

Members of tuple can be iterated using `for` loop.

```eng
for (let value in tuple) { # value is of type variant of all possible types if tuple holds multiple types, otherwise a specific type
    io.println("Value: ${value}");
}
```

### 4.13. Maps

A map is a collection of key-value pairs, where each key is unique.

```eng
let map: string => int = {
    "one":   1,
    "two":   2,
    "three": 3
};
```

Values in the map can be accessed using `map[ key ]`.

```eng
let value = map[ "two" ]; # 2
```

Non-existent keys throws `key_not_found` exception when accessed.

```eng
let value = map[ "four" ]; # Throws key_not_found exception
```

Values can be inserted using `map.insert(key, value)`.

```eng
map.insert("four", 4); # Adds new key-value pair
```

Values can be updated using `map[ key ] = value`.

```eng
map[ "two" ]  = 22;    # Updates existing key-value pair
```

Values can be removed using `map.remove(key)`.

```eng
map.remove("three"); # Removes key "three"
```

Value's existance can be checked using `in` keyword.

```eng
if ("two" in map) {
    io.println("Key 'two' exists in the map.");
}
```

All the values in the map can be iterated using `for` loop.

```eng
for (let (key, value) in map) {
    io.println("Key: ${key}, Value: ${value}");
}
```

## 5. Statements

### 5.1. Expressions

Expressions can involve values (e.g., variables, literals or expressions), operators or parenthesized expressions.

Every expression has an associated type and is the simplest unit of evaluation and can be used anywhere a value is expected.

#### 5.1.1. Primary Expression

Primary expression involves values directly, either from variables, literals or parenthesized expression.

```eng
1
value
(2 + value * 4)
```

#### 5.1.2. Prefix Operator

It has one operator symbol and one operand in the form of `⊕x`.

```eng
-a
```

#### 5.1.3. Suffix Operator

It has one operator symbol and one operand in the form of `x⊕`.

```eng
a!
```

#### 5.1.4. Unary Combination

In case of two unary operators collide, the operator with higher precedence is evaluated before the operator of lower precedence.

```eng
-a!
```

Here, if `-x` has a higher precedence than `x!`, it will be evaluated as `(-x)!`. Otherwise, `-(x!)`.

#### 5.1.5. Infix Operator

It has one operator symbol and two operands in the form of `x ⊕ y`.

```eng
a + b
```

#### 5.1.6. Chaining

Infix operators can be chained and the order of evaluation is determined by the precedence of the operator.

```eng
a + b * c
```

Here, `b * c` will be evaluated before `a + b` as the `*` operator has a higher precedence compared to `+`.

#### 5.1.7. Associativity

In case of same operators, the associativity will determine the order of evaluation.

```eng
a ** b ** c
```

Here, `b ** c` will be evaluated before `a ** b` as the `**` operator's associativity is right-to-left.

#### 5.1.8. Multi-Part Operator

Multi-part operator is unification of operators with two or more operator symbols. This operator alternates between operator and operand and can contain infinitely many operator symbols.

```eng
# Two operator symbols:
➀ x ➁
➀ x ➁ y
x ➀ y ➁
x ➀ y ➁ z

# Three operator symbols:
➀ x ➁ y ➂
x ➀ y ➁ z ➂
➀ x ➁ y ➂ z
x ➀ y ➁ z ➂ w

# ...so on...
```

In case of overlaps, i.e., Prefix `➀ x`, Suffix `x ➁` or Infix `x ➀ y`, the multi-part operator is resolved as a single atomic operation iff all the conflicts does not have a defined valid operator, or the defined precedence is lower than the multi-part operator.

In other words,
```eng
|x|
```
is evaluated as singular absolute operator if absolute operator has a higher precedence compared to `|x` or `x|`.

#### 5.1.9. Member Access

Member access allows accessing members of a variable using the dot operator (`.`).

```eng
variable.member
```

Member access can be chained as well.

```eng
variable.member1.member2.member3
```

Note: Member access has the lowest precedence among all operators, as opposed to most programming languages. This allows easier composition of operators without needing extra parenthesis.

```eng
variable.*member1.&member2 # Same as &(*(variable.member1).member2) in traditional languages
```

### 5.2. Variable Assignment

Variable assignment assigns a value to a variable.

```eng
variable = value;
```

A compound assignment allows combining an operation with assignment.

```eng
variable ⊕= value;
```

Same as

```eng
variable = variable ⊕ value;
```

Example:

```eng
counter += 1; # Same as counter = counter + 1;
```

A member assignment allows assigning a variable with its own member.

```eng
variable .= member;
```

Same as

```eng
variable = variable.member;
```

Example:

```eng
let point = vec2(.x = 10, .y = 20);
point .= normalized(); # Same as point = point.normalized();
```

When calling a member function that mutates the object itself, the `.:` operator can be used to copy the object first, and then call the member function on the copy.

```eng
let new_variable = variable.:member_function(args);
```

Same as

```eng
let new_variable = with {
    variable_copy = variable;
    variable_copy.member_function(args);
    be variable_copy;
};
```

Example:

```eng
let point = vec2(.x = 10, .y = 20);
let new_point = point.:rotate(45_deg); # Rotates a copy of point by 45 degrees
```

### 5.3. `if` Statement

`if` statement allow branching of code based on the condition.

```eng
if (condition) {
    # code if condition is true
}
```

An `else` block can be attached to run code if the condition is false instead.

```eng
if (condition) {
    # code if condition is true
} else {
    # code if condition is false
}
```

The `if` statement can also contain multiple statements before the condition to contain them in the scope of `if` block and `else` block.

```eng
if (let declaration = value; condition) {
    # code if condition is true
}
```

```eng
if (let declaration = value; let other_decl = other_value; declaration = other_decl; condition) {
    # code if condition is true
}
```

Both can be combined as well.

```eng
if (let declaration = value; condition) {
    # code if condition is true
} else {
    # code if condition is false
}
```

### 5.4. `while` Statement

`while` statement allows repeated execution based on the condition.

```eng
while (condition) {
    # code while condition is true
}
```

An `else` block can also be added if the condition for `while` statement if the loop never ran.

```eng
while (condition) {
    # code while condition is true
} else {
    # code if loop never ran
}
```

A `do` block can also be added before the loop to unconditionally execute the code at least once.

```eng
do {
    # code to execute at least once and while condition is true
} while (condition);
```

`while` statements can also have multiple statemenet before the condtition to contain them in the scope of `while`.

```eng
while (let decaration = value; condition) {
    # code while condition is true
}
```

```eng
while (let decaration = value; condition) {
    # code while condition is true
} else {
    # code if loop never ran
}
```

### 5.5. `for` Statement

`for` statement combines initialization, condition and update statement.

```eng
for (let declaration = value; condition; update) {
    # code for condition with update
}
```

An `else` block can also be added if the loop never ran.

```eng
for (let declaration = value; condition; update) {
    # code for condition with update
} else {
    # code if loop never ran
}
```

`for` statements can also use iteration.

```eng
for (let element in array) {
    # code for elements of array
}
```

### 5.6. `once` and `onward`

Inside loops, `once` executes only on the first iteration, and `onward` on all subsequent iteration.

```eng
while (condition) {
    once {
        # code to be executed on first iteration
    }
    onward {
        # code to be executed on subsequent iteration
    }
}
```

Both can also have an `else` block attached for same semantics.

```eng
while (condition) {
    once {
        # code to be executed on first iteration
    } else {
        # code to be executed on subsequent iteration
    }

    onward {
        # code to be executed on subsequent iteration
    } else {
        # code to be executed on first iteration
    }
}
```

### 5.7. `break` and `cont`

Inside loops, `break` allows early termination of the loop, and `cont` allows early reieration of the loop.

```eng
while (condition) {
    if (another_condition) {
        break;
    }
    if (another_condition) {
        cont;
    }
}
```

They both can take an optional integer to indicate the number of nested loops to affect.

```eng
while (condition) {
    while (inner_condition) {
        if (another_condition) {
            break 2;
        }
        if (another_condition) {
            cont 2;
        }
    }
}
```

### 5.8. `switch` Statement

`switch` selects single execution path based on matching criteria. Cases can be of value comparison, operator form or even arbitrary expression using `$` as placeholder for value.

```eng
switch (value) {
    case 1 {
        # code if value is equal to 1
    }
    case 2 {
        # code if value is equal to 2
    }
    case $ > 2 && $ < 20 {
        # code if value is greater than 2 and less than 20
    }
    case $ in [ 20:30..., 40:50... ] {
        # code if value is between 20 to 29, or 40 to 49
    }
    case is_even($) {
        # code if value is even (i.e., if the is_even function returns true for case)
    }
    case $ is float || $ is int {
        # code if value is of type float or int
    }
    else {
        # code if no case is matched
    }
}
```

Switch cases can also contain statements before the condition to contain them in the scope of `case` block.

```eng
switch (shape) {
    case let c as circle = $; c.radius > 10 {
        # code if shape is a circle and its radius is greater than 10
    }
}
```

### 5.9. `match` And Pattern-Matching

`match` allows conditional destructuring by matching pattern.

```eng
switch (shape) {
    case $ match circle(radius) && radius > 10 {
        # code if shape is a circle and its radius is greater than 10
    }
    case $ match square(let w = .width, let h = .height, .position(let x, let y)) && w + h < 10 {
        # code if shape is a square and sum of its width and height is less than 10
        # also destructures position.x and position.y as x and y
    }
}
```

`match` can also be used in `if`, `while` and `for`.

```eng
if shape match circle(let radius) && radius > 10 {
    # code if shape is a circle and its radius is greater than 10
}
```

`match` isn't just used to extract inner variable, but can also check for equality.

```eng
switch (shape) {
    case $ match circle(let r > 10) {
        # code if shape is a circle and its radius is greater than 10, can still use r
    }
    case $ match square(let w == 5, let h, .position(let x, let y)) && w + h < 10 {
        # code if shape is a square, its width is equal to 5 and sum of its width and height is less than 10, can still use w, h, x and y
    }
}
```

### 5.10. `throw` and `try`-`catch`

Error handling can be done with `throw` and `try`-`catch` statement that allows throwing a value for raising an error and catching it to handle the error.

```eng
try {
    # code that raises an error
    throw 10;
} catch (value: int) {
    # code to handle the error
}
```

The `catch` block is optional, and omiting it would only stop propagation of the exception without handling it.

```eng
try {
    risky_operation();
} # Silence the error
```

Multiple `catch` blocks can be used to handle different errors.

```eng
try {
    risky_operation();
} catch (e: internal_exception) {
    # handle internal_exception
} catch (e: connection_exception) {
    # handle connection_exception
} catch (e: exception) {
    # handle unknown error
}
```

### 5.11. `require` and `comply`

`require` constructs are used to execute tasks that the user must explicitly comply to. It represents a contract between the entity and the user.

```eng
require "C" fn c_function() -> int;

fn main() {
    let value = comply "C" c_function();
};
```

### 5.12. `with` and `be`

All compound and control statements can be made to evaluates to a value using `be` statement. If no `be` statements are executed, the value is evaluated to the default value of the type.

```eng
let value = with if (condition) {
    be 3;
} else {
    be 4;
}; # Semicolon is mandatory as it is considered an expression
```

Type can also be specified for the target result type.

```eng
let value = with: float if (condition) { # Specify expression type for `be` statement
    be 3;
} else {
    be 4;
};
```

More examples with different control structures:

```eng
let value = with while (condition) {
    if (another_condition) {
        be 3;
    }
}; # implicitly defaults to default value (0) if no `be` statements are executed
```

```eng
let value = with {
    if (a) {
        be true;
    }

    for (let b in c) {
        if (b) {
            be true;
        }
    }

    if (d) {
        be false;
    }

    be true;
};
```

### 5.13. `defer` Blocks

`defer` block allows deferring execution of code until the surrounding scope is exited.

```eng
fn main() {
    let file = io.open_file("data.txt");

    defer {
        io.close_file(file); # Ensures file is closed when exiting scope
    };

    # Do something with the file
    let content = io.read_file(file);
    io.println(content);
};
```

### 5.14. Omission

Parenthesis or braces (but not both) can be omitted in all control statements to simplify raeding.

```eng
if condition {
    # code
}

or

if (condition)
    # Single-statement code
```

More examples:

```eng
while (condition) # Single-statement code

for let elm in array { #{ Do something }# }

do things; while condition; else other_things;

if (condition) while (condition) once statement; else statement; else statement; else statement;

switch (value)
    case a {
    } case b {
    } case c {
    } else {
    }

try throw 10;
```

## 6. Functions

Functions defines reusable block of code that works on optional inputs (parameters) and optional outputs (returns).

Functions can be declared anywhere using `fn` keyword.

```eng
fn function_name(parameters) -> returns {
    # function body
};
```

Note: The semicolon after the closing brace is mandatory.

```eng
fn add(a: int, b: int) -> int {
    return a + b;
};
```

### 6.1. Multiple Returns

Multiple values can be returned from the function.

```eng
fn add_sub(a: int, b: int) -> int, int {
    return a + b, a - b;
};

fn main() {
    let (sum, diff) = add_sub(2, 3);
};
```

### 6.2. Naming Returns

Returned variables can be named just like parameters, and allows assignment to specify the return value before implicit return or devalued return.

```eng
fn add_sub(a: int, b: int) -> sum: int, diff: int {
    return sum = a + b, diff = a - b;
};

fn main() {
    let sum = add_sub(2, 3).sum;    # Extracting the sub part
    let result = add_sub(4, 5);     # Result with the type of function's return values
    let diff = result.diff;         # Access function's results
    let (s, d) = add_sub(6, 7);     # Unpacking
};
```

### 6.3. Implicit Returns

Functions without return statement will return default value of the type.

```eng
fn square() -> int {
}; # Returns 0 implicitly
```

Function with named return values will return the value held by the return value.

```eng
fn square(x: int) -> y: int {
    y = x ** 2;
}; # Returns x ** 2 for y
```

The expression for return statement is optional even for non-void functions.

```eng
fn square(x: int) -> y: int {
    y = x ** 2;
    return; # Returns x ** 2 for y
};
```

### 6.4. Return Type Inference

The return type of the function can be inferred based on the consistent return statements in the function body.

```eng
fn cube(x: int) { # Return type of cube is int
    return x ** 3;
};
```

### 6.5. Named Arguments

Functions can be called with specifying the name of the argument for values of each.

```eng
fn mul_div(x: int, y: int) {
    return x * y, x / y;
};

fn main() {
    let (z, w) = mul_div(.y = 3, .x = 6); # (z, w) = (18, 2)
};
```

Positional and named arguments can be mixed. The named arguments are removed from the list of ordered positional arguments when calling the function for the positional arguments to use.

```eng
fn print_values(list: int[ ], sorter = no_sort, filter = all_filter) {
    io.println("Items:");
    for let item in list.sort(sorter).filter(all_filter) {
        io.println(item);
    }
};

fn main() {
    print_values([ 1, 3, 2 ], .sorter = asc_sort); # Print sorted items
    print_values([ 1, 3, 2 ], .filter = remove_even); # Print filtered items
};
```

If the parameter name and argument name are the same, the assignment can be omitted.

```eng
fn main() {
    let x = 5;
    let y = 10;
    let (z, w) = mul_div(.y, .x); # Same as mul_div(.y = y, .x = x)
};
```

### 6.6. Default Parameter Values

Parameters can have default value for them to omit the parameter.

```eng
fn mul_div(x: int, y: int = 1) { # Or `y = 1` with type inference
    return x * y, x / y;
};

fn main() {
    let (z, w) = mul_div(.y = 3, .x = 6); # (z, w) = (18, 2)
};
```

However, the default values are not limited to last parameter.

```eng
fn mul_div(x: int = 4, y: int) {
    return x * y, x / y;
};

fn main() {
    let (z, w) = mul_div(default, 2); # (z, w) = (8, 2)
    (z, w) = mul_div(.x = default, .y = 2); # Same as before
};
```

### 6.7. Overloading

#### 6.7.1. Basic Overloading

Functions can be overloaded with multiple variations by varying parameter type and/or count.

```eng
fn println(x: int) {
    io.println(x);
};

fn println(x: float) {
    io.println(x);
};

fn println(x: int, y: string) {
    io.println("$(${string}){x}");
};
```

#### 6.7.2. Overloading with Named Parameters

Functions can also be overloaded by varying just parameter name as well. In this case, the caller cannot call the overloads just by the positional argument, and is required to specify the argument.

```eng
fn radius(area: float) {
    return (area / math.pi)  0.5;
};

fn radius(circumference: float) {
    return circumference / (2 * math.pi);
};

fn main() {
    let r = radius(.area = 10);
    r = radius(.circumference = 4);
};
```

Note: Default value has no effect on overloadability. However, they can limit the callability of a function with positional argument.

```eng
fn transform(v: vector, m: matrix = matrix()) {
    # ... Transformation ...
};

fn transform(v1: vector, v1: vector = vector()) {
    # ... Transformation ...
};

fn main() {
    let t1 = transform(.v = vector(3, 4, 5)); # Calls first function
    let t2 = transform(.v1 = vector(6, 7, 8)); # Calls second function
};
```

#### 6.7.3. Overload Selection

An overload can be selected without being called by using the overload selector syntax `:[ ... ]` after the function name.

```eng
fn main() {
    let int_printer = println:[ int ];
    int_printer(10); # Prints 10

    let float_printer = println:[ float ];
    float_printer(3.14); # Prints 3.14

    let formatted_printer = println:[ int, string ];
    formatted_printer(20, ".2f"); # Prints 20.00
};
```

Overload selection can also be done with named argument.

```eng
fn main() {
    let get_radius = radius:[ area: float ]; # We must specify parameter name since radius:[ float ] is ambiguous
    let r = get_radius(10);

    let get_circumference = radius:[ circumference ]; # Can also omit type
    r = get_circumference(4);
};
```

#### 6.7.4. Dynamic Overload Dispatch

A variant type can be used to dispatch overloads based on the contained type dynamically.

```eng
fn print_value(x: int) {
    io.println("Integer: ${x}");
};

fn print_value(x: float) {
    io.println("Float: ${x}");
};

fn main() {
    let value: int | float = 10; # Variant containing int

    print_value(value...); # Dispatches to print_value(int)

    value = 3.14; # Variant containing float

    print_value(value...); # Dispatches to print_value(float)
};
```

Multiple variant types can also be used to dispatch overloads with multiple parameters, eliminating the need for manual type checking and casting exponentially.

```eng
fn combine(x: int, y: int) {
    io.println("Sum: ${x + y}");
};

fn combine(x: string, y: string) {
    io.println("Concatenation: ${x + y}");
};

fn combine(x: int, y: string) {
    io.println("Int and String: ${x} - ${y}");
};

fn combine(x: string, y: int) {
    io.println("String and Int: ${x} - ${y}");
};

fn main() {
    let a: int | string = 5;
    let b: int | string = "Hello";

    combine(a..., b...); # Dispatches to combine(int, string)

    a = "World";
    b = 10;

    combine(a..., b...); # Dispatches to combine(string, int)
};
```

Note: This is only possible when all the combination of possible types are covered by overloads. Otherwise, it will result in a compile-time error.

### 6.8. Variadic Arguments

Functions can take a variable number of arguments using `...` syntax. This allows the function to accept any number of arguments of the specified type, or a mix of types. The arguments are collected into an array.

```eng
fn sum(...args: int) -> int { # args is of type `int[ ]`
    let total = 0;
    for let arg in args {
        total += arg;
    }
    return total;
};

fn main() {
    let result = sum(1, 2, 3, 4, 5); # result = 15
    let result2 = sum(10, 20);      # result2 = 30
    let result3 = sum();            # result3 = 0
};
```

Variadic arguments can also be used with named arguments, and not specifying the type make it an untyped variadic argument.

```eng
fn log(message: string, ...args) { # args is of type `any[ ]` or `[ ]`
    io.print("${message} ");
    for let arg in args {
        io.print("${arg} ");
    }
    io.println();
};

fn main() {
    log("Values:", 1, 2, 3); # Prints: Values: 1 2 3
    log("Hello", "World");   # Prints: Hello World
    log("No args");          # Prints: No args
};
```

You can have only one variadic argument, and it can also come in any position in the parameter list.

```eng
fn mixed(a: int, ...args: string, b: float) {
    io.println("a: ${a}");
    for let arg in args {
        io.println("arg: ${arg}");
    }
    io.println("b: ${b}");
};

fn main() {
    mixed(1, "hello", "world", 3.14); # a: 1, arg: hello, arg: world, b: 3.14
};
```

### 6.9. First-Class Functions

Functions are first-class values. Meaning, they can be stored in variables, passed as arguments or returned from functins.

```eng
fn add(x: int, y: int) { return x + y; }
fn sub(x: int, y: int) { return x - y; }
fn mul(x: int, y: int) { return x * y; }
fn div(x: int, y: int) { return x / y; }

fn operation(name: string) {
    return with switch name {
        case "add" { be add; }
        case "sub" { be sub; }
        case "mul" { be mul; }
        case "div" { be div; }
    };
};

fn main() {
    let op = operation("sub");
    let result = op(10, 7); # result = 3
};
```

Functions are nullable by default to allow easier handling of missing functions.

```eng
fn main() {
    let op: fn (x: int, y: int) -> int = operation("mod"); # op is null
    let result = op?(10, 3); # result is null
};
```

### 6.10. Anonymous Function

Anonymous Function are functions without specified name. They are not a special type of function, but rather works the same way.

```eng
let operation = fn (x: int, y: int) -> int { return x + y; };
```

The signature of function can be deduced when the signature is provided by the context (e.g., variable type is known before function usage).

```eng
fn operate(op: fn (x: int, y: int) -> z: int) -> int {
    return op(2, 3);
};

fn main() {
    let value = operate(fn { return z = x + y; }); # Signature of this function is `fn (x: int, y: int) -> z: int`, deduced from context
};
```

Parameters can also be picked individually with different name.

```eng
fn main() {
    let value = operate(fn (a = .a, .b) -> int { return a + b; });
};
```

### 6.11. Explicit Captures

Functions, and by extension, anonymous functions, can explicitly specify the list of local variables that the function needs from the function scope. They can specify capture type (by value, by reference or by const reference).

By default, all local variables that are guaranteed to live longer than the function is captured by reference, and others are captured by value.

```eng
let a, b = (9, 8);
let function1 = fn [ a, b& ] () {};
fn function2 [ a!, b! & ] () {};
```

When a capture group is specified, all the other variables not mentioned in the capture group will not be captured, unless default capture is specified by specifying the capture type without any namee following it.

```eng
let a, b, c = (9, 8, 7);
let function = fn [ !, b& ] () {}; # Capture all by constant, capture b by reference
```

### 6.12. Trailing Parameters

Passing an anonymous function to a function can be represented with a much cleaner syntax by using trailing function syntax.

```eng
fn query(body: fn (db: database) -> commit: bool) {
    let db = connect("localhost", "testdb");
    let commit = body(db);
    if (commit) db.commit();
    db.close();
};

fn main() {
    query(): {
        # Established database (db) is now available in this scope

        let users = db.select("users")
            .where("age" > 18)
            .order_by("name");

        if !users.empty {
            commit = true; # Set the return value for implicit return

            for let user in users {
                user.can_vote = true;
                io.println("[Change]: ${u.name} can now vote their representative.");
            }
        }
    };
};
```

Multiple scope blocks can also be used to chain blocks.

```eng
fn layout(header: fn() -> void, body: fn() -> void, footer: fn() -> void) {
    io.println("[Render: Layout]");
    io.println("  <header>");
    header();
    io.println("  </header>");
    io.println("  <main>");
    body();
    io.println("  </main>");
    io.println("  <footer>");
    footer();
    io.println("  </footer>");
};

fn main() {
    layout(): {
        io.println("Logo + Navigation");
    }, {
        io.println("Content goes here");
    }, {
        io.println("Copyright 2025");
    };
};
```

Name can also be explicitly specified to avoid confusion.

```eng
fn main() {
    layout(): .header {
        io.println("Logo + Navigation");
    }, .body {
        io.println("Content goes here");
    }, .footer {
        io.println("Copyright 2025");
    };
};
```

Trailing function can also contain expression without function body for returning function.

```eng
fn calculate(calculator: fn (x: int) -> y: int) {
    return calculator(2);
};

fn main() {
    let value = calculate(): (x * 2); # 4
};
```

### 6.13. Expression Functions

Functions that consists of a single return statement can be declared as expression functions for conciseness.

```eng
fn add(a: int, b: int) -> int => a + b;
```

This can also be used with anonymous functions.

```eng
let add = fn (a: int, b: int) -> int => a + b;
```

### 6.14. Retaining Local Variables

Local variables can be declared `retain` to allow them to retain their value across function calls.

```eng
fn counter() {
    retain let count = 0;
    return count++;
};

fn main() {
    io.println("Count: ${counter()}"); # Prints "Count: 0"
    io.println("Count: ${counter()}"); # Prints "Count: 1"
    io.println("Count: ${counter()}"); # Prints "Count: 2"
};
```

### 6.15. Pure Functions

Functions can be declared as `pure` to indicate that they have no side effects and their output depends only on their input parameters. This allows for certain optimizations about the function's behavior, such as compile-time evaluation and memoization.

```eng
pure fn square(x: int) -> int {
    return x * x;
};
```

Pure functions cannot contain any side-effecting operations, such as modifying global variables, performing I/O operations, or throwing exceptions. They also cannot contain retaining local variables.

### 6.16. Fake Pure Functions

Functions can be declared as `impure` to falsely indicate that they are pure functions. This is useful when interfacing with external libraries or performing operations that are known to be side-effect free, but cannot be guaranteed by the compiler, or for the programmer to take responsibility for ensuring the function's purity (e.g., caching results). These functions can still be called from another pure function. Same performance optimizations can be applied to these functions as well.

```eng
impure fn cached_fibonacci(n: int) -> int {
    retain let cache: int => int;

    if (cache.contains(n)) {
        return cache[n];
    }

    let result = if (n <= 1) {
        n;
    } else {
        cached_fibonacci(n - 1) + cached_fibonacci(n - 2);
    };

    cache.insert(n, result);
    return result;
};

fn main() {
    let value = cached_fibonacci(10); # value = 55
};
```

### 6.17. Signature Compatibility

A function of a certain signature can be assigned to a variable of another function type even if the signatures are not exactly the same, as long as they are compatible.

A function with fewer parameters can be assigned to a function type with more parameters, but not the opposite.

```eng
fn greet(name: string) {
    io.println("Hello, ${name}!");
};

fn greet_with_age(name: string, age: int) {
    io.println("Name: ${name}, Age: ${age}");
};

fn main() {
    let greeter: fn (string, int) = greet; # Compatible, extra parameter ignored
    greeter("Alice", 30); # Calls greet("Alice")

    greeter = greet_with_age;
    greeter("Bob", 25); # Calls greet_with_age("Bob", 25)
};
```

A function with more return values can be assigned to a function type with fewer return values, but not the opposite.

```eng
fn get_coordinates() -> a: int, b: int {
    return 10, 20;
};

fn get_color() -> a: int, b: int, c: int {
    return 255, 0, 0;
};

fn main() {
    let getter: fn () -> a: int, b: int = get_color; # Compatible, extra return value ignored
    let (x, y) = getter(); # Calls get_color(), x = 255, y = 0

    getter = get_coordinates;
    let (r, g) = getter(); # Calls get_coordinates(), r = 10, g = 20
};
```

This also works with parameter picking with different names.

```eng
fn operate(op: fn (x: int, y: int) -> z: int) -> int {
    return op(2, 3);
};

fn main() {
    let value = operate(fn (x = .a) -> int { return x * 2; }); # Compatible, parameter names differ
    let value = operate(fn (.a) -> int { return a ** a; });
};
```

### 6.18. Binding

Functions can be bound to a variable with specific arguments to create a new function with fewer parameters.

```eng
fn add(a: int, b: int) -> int {
    return a + b;
};

fn main() {
    let add_five = add:(.b = 5); # Binds b to 5
    let result = add_five(10); # Calls add(10, 5), result = 15
};
```

Using placeholder `$` or `$<name>`, parameters can be left unbound to create a new function with those parameters.

```eng
fn quadratic(a: float, b: float, c: float, x: float) -> float {
    return a * x ** 2 + b * x + c;
};

fn main() {
    let quadratic_with_c_12 = quadratic:($, $, 12); # Binds c to 12
    let result = quadratic_with_c_12(1, 2, 3); # Calls quadratic(1, 2, 12, 3)

    let quadratic_with_b_3_c_5 = quadratic:($, 3, 5, .x = $y); # Binds b to 3 and c to 5, and renames x to y
    let result2 = quadratic_with_b_3_c_5(.a = 2, .y = 4); # Calls quadratic(2, 3, 5, 4)
};
```

Using placeholder `$<index>` or `$<index>.<name>`, we can positionally select and rename parameter.

```eng
fn quadratic(a: float, b: float, c: float, x: float) -> float {
    return a * x ** 2 + b * x + c;
};

fn main() {
    let quadratic_with_2_c = quadratic:($1, $0, $2, $3); # Binds $0 to second parameter, $1 to first parameter, $2 to be multiplied by 2
    let result = quadratic_with_2_c(1, 2, 3, 4); # Calls quadratic(2, 1, 3, 4)
};
```

Binding also supports composition and arbitrary expression.

```eng
fn square(x: float) => x ** 2;

fn quadratic(a: float, b: float, c: float, x: float) -> float {
    return a * x ** 2 + b * x + c;
};

fn main() {
    let quadratic_with_2_c = quadratic:($, $ + 2, square($), $); # b is added by 2 before passing, and c is sequared before passing
    let result = quadratic_with_2_c(1, 2, 3, 4); # Calls quadratic(1, 4, 9, 4)
};
```

### 6.19. `ego` Function

`ego` refers to the current function itself. It is useful for recursion or passing the current function as argument.

```eng
fn factorial(n: int) -> int {
    if (n <= 1) {
        return 1;
    } else {
        return n * ego(n - 1); # Recursive call
    }
};

fn main() {
    let result = factorial(5); # result = 120
};
```

It is also useful to recursively call anonymous functions.

```eng
io.println("${fn (n: int) -> int {
    if (n <= 1) {
        return n;
    } else {
        return ego(n - 1) + ego(n - 2); # Recursive call
    }
}()}");
```

### 6.20. Side-Channeling

A value used in expression can also be branched into calling a function using side-channeling operator `<=`.

```eng
fn log(value: int) {
    io.println("Log: ${value}");
};

fn main() {
    let x = 10;
    let y = 20 + x <= log; # Calls log(x) and y = 20 + x
};
```

A placeholder `$` can also be used to specify where the value goes in the function call.

```eng
fn log_with_prefix(prefix: string, value: int) {
    io.println("${prefix}: ${value}");
};

fn main() {
    let x = 10;
    let y = (20 + x) <= log_with_prefix("Value is", $); # Calls log_with_prefix("Value is", 20 + x) and y = 20 + x
};
```

### 6.21. Omission

If the function's return type is omitted and the body consists of a single statement, braces can be omitted.

```eng
fn add(a: int, b: int) return a + b;
```

If the function takes no parameters, the parentheses can also be omitted.

```eng
fn hello {
    print("Hello");
};
```

## 7. Classes

A class is declared with `class` keyword. It allows users to define a type anywhere with members (variables, functions, etc.).

```eng
class class_name {
    # members
};
```

Note: The semicolon after the closing brace is mandatory.

```eng
class point {
    let x: float;
    let y: float;
};
```

### 7.1. Instanciation

Objects are created by declaring a variable of the class type.

```eng
let p: Point;
```

Objects can also be created by specifying the members of the class.

```eng
let p = Point(.x = 2, .y = 4);
```

### 7.2. `this`, `self`, `base` and `loft` Keywords

The `this` keyword refers to the current instance of a class, while `self` refers to the class type.

```eng
class point {
    let x: float;
    let y: float;

    fn move(dx: float, dy: float) {
        this.x += dx;
        this.y += dy;
    };

    fn origin() -> point {
        return self(.x = 0, .y = 0);
    };
};
```

The `base` keyword refers to the base class of the current class in case of inheritance. In case of multiple inheritance, it refers to a variant of all the base classes.

```eng
class colored_point: point, colorable {
    let color: color;

    fn paint(new_color: color) {
        (base as colorable).set_color(new_color); # Calls colorable's set_color
    };
};
```

As `self` is the type of `this` class, `loft` refers to the type of the `base` class(es). In case of multiple inheritance, it refers to a variant type of all the base classes.

```eng
class point3d: point {
    let z: float;

    fn to_2d() -> loft {
        return loft(.x, .y);
    };
};
```

### 7.3. Constructors

Classes can define constructors which runs at initialization of the object. The user can specify parameters for the construction during initialization.

```eng
class device {
    let id: int;
    let name: string;

    ctor(name: string) {
        this.id   = generate_random_id();
        this.name = name;
    };
};
```

```eng
let phone = device("Phone");
```

### 7.4. Constructor as Member Function

The constructor is essentially a special member function. It can be accessed as so:

```eng
let device_maker = device.ctor;
let phone = device_maker("Phone");
```

### 7.5. Default Constructor

Default constructor will be called when no parameter is specified.

```eng
class device {
    let id: int;
    let name: string;

    ctor() {
        this.id   = generate_random_id();
        this.name = "Unknown Device";
    };
};
```

Calling default constructor.

```eng
let tablet: device;
let laptop = device();
```

Note: An existance of parameterized constructor does not prevent default initialization of variable.

```eng
class device {
    let id: int;
    let name: string;

    ctor(name: string) {
        this.id   = generate_random_id();
        this.name = name;
    };
};

fn main() {
    let my_dev = device(); # Predefined default constructor used.
};
```

Note: Member initialization still works regardless of presence/absence of constructors. In such case, the default constructor will be called before the initialization of the members.

```eng
class device {
    let id: int;
    let name: string;

    ctor() {
        this.id   = generate_random_id();
        this.name = "Unknown Device";
    };
};

fn main() {
    let my_dev = device(.name = "My Device");
    io.println("My device ID and name: ${my_dev.id} : ${my_dev.name}"); # Prints "My device name: 102401 : My Device" (assuming generate_random_id() returns 102401)
};
```

The default constructor and member initialization constructor can be deleted using `undef ctor()`.

```eng
class device {
    let id: int;
    let name: string;

    undef ctor;

    ctor(name: string) {
        this.id   = generate_random_id();
        this.name = name;
    };
};

fn main() {
    let my_dev = device(); # Invalid
};
```

### 7.6. Factory Constructors

Constructors can also be named to allow users to explicitly choose which constructor they want to call without relying on overloading, while still allowing overloading-style construction.

```eng
class device {
    let id: int;
    let name: string;

    ctor.from_name(name: string) {
        this.id   = generate_random_id();
        this.name = name;
    };
};

fn main() {
    let my_device = device.from_name("Google Pixel 8a"); # Choose by name
    let someone_elses = device("iPhone 15 Pro"); # Choose by overloading
};
```

### 7.7. Destructors

Destructors are responsible for cleanup after object deinitializaion. They do not take any parameters.

```eng
class connection {
    let db: database;

    ctor() {
        db.connect("system", "system");
    };

    dtor() {
        db.commit();
    };
};

fn main() {
    let conn = connection();

    # Do something with the connection

}; # conn goes out of scope here, and destructor is called to commit the changes
```

Values can be prematurely destroyed by calling `dtor` member function.

```eng
fn main() {
    let conn = connection();

    # Do something with the connection

    conn.dtor(); # Explicitly destroy conn and call destructor here

    # conn is no longer accessible here
};
```

Note that explicitly calling destructor can only be done in same-scope. Conditionally calling destructor is not possible.

### 7.8. Copy Constructor

A copy constructor is responsible for deep-copying an object from another object.

```eng
class music {
    let music_data: int8* = nullptr;
    let music_data_size = 0;

    copy(ref other_music: music) {
        music_data = copy other_music.music_data; # Memory copy with allocation
        if music_data == nullptr {
            throw runtime_error("Failed to allocate memory for music data");
        }

        music_data_size = other_music.music_data_size;
    };

    dtor {
        dealloc music_data;
    };
};

fn main() {
    let music_1 = load_music("Never Gonna Give You Up.flac");

    let music_2 = music_1; # Calls copy constructor
    let music_3: ! & = music_1; # Does not call copy constructor
};
```

The default copy constructor can be deleted using `undef copy`.

```eng
class music {
    let music_data: int8* = nullptr;
    let music_data_size = 0;

    undef copy;

    dtor {
        dealloc music_data;
    };
};

fn main() {
    let music_1 = load_music("Never Gonna Give You Up.flac");

    let music_2 = music_1; # Invalid
};
```

### 7.9. Move Constructor

A move constructor is responsible for transferring ownership of data from another object to this object.

```eng
class music {
    let music_data: int8* = nullptr;
    let music_data_size = 0;

    move(ref other_music: music) {
        music_data = other.music_data; # Copy pointer instead of memory
        music_data_size = other.music_data_size;

        other.music_data = nullptr;
        other.music_data_size = 0;
    };

    dtor {
        dealloc music_data;
    };
};

fn main() {
    let music_1 = load_music("Never Gonna Give You Up.flac");

    let music_2 = move music_1; # Calls move constructor. music_1 name is now inaccessible and effectively non-existent

    music_1; # Error: music_1 is no longer accessible
};
```

The default move constructor can be deleted using `undef move`.

```eng
class music {
    let music_data: int8* = nullptr;
    let music_data_size = 0;

    undef move;

    dtor {
        dealloc music_data;
    };
};

fn main() {
    let music_1 = load_music("Never Gonna Give You Up.flac");

    let music_2 = move music_1; # Invalid
};
```

### 7.10. Swap Constructor

Swapping memory is one of the most cleaver ways to implement efficient resource management while still keeping invariants intact. A class can define a `swap` constructor that takes another object of the same class by reference, and swap the resources of both objects.

```eng
class music {
    let music_data: int8* = nullptr;
    let music_data_size = 0;
};

fn main() {
    let buf1: music~ = music(1024);
    let buf2: music~ = music(2048);

    let buf3: music~ = buf1; # buf1 is now empty and buf3 has 1024 bytes
    let buf4: music~ = buf3; # buf3 is now empty and buf4 has 1024 bytes
    buf4 = buf2; # buf2 has 1024 bytes, buf4 has 2048 bytes
    buf4 = swap buf2; # Manually swap (useful for non-swapping values), buf2 has 2048 bytes, buf4 has 1024 bytes
};
```

The default swap constructor can be deleted using `undef swap`.

```eng
class music {
    let music_data: int8* = nullptr;
    let music_data_size = 0;

    undef swap;
};

fn main() {
    let music_1 = load_music("Never Gonna Give You Up.flac");
    let music_2 = load_music("Never Gonna Let You Down.flac");

    music_2 = swap music_1; # Invalid
};
```

### 7.11. Access Modifiers

Members access from outside can be specified to be either:
1. Public (`pub`, default): The member is accessible everywhere.
2. Personal (`pers`): The member is accessible within the namespace the class is declared in.
3. Protected (`prot`): The member is accessible within the same class and derived classes.
4. Private (`priv`): The member is accessible within the same class.

```eng
class vault {
    priv let password: string;

    prot fn check_code(phrase: string) {
        return phrase == password;
    };

    pers fn unlock_vault() {
        # ...
    };

    pub fn unlock(phrase: string) {
        if (check_code(phrase)) {
            unlock_vault();
        }
    };
};
```

### 7.12. Friend Access

Classes can explicitly specify other entities (classes, properties, functions, etc.) that may access private members of this class.

```eng
class account {
    priv string owner;
    priv double balance;

    friend print_account, print_owner;
};

fn print_account(acc: account) {
    io.println("Account balance: $${acc.balance}");
};

fn print_owner(acc: account) {
    io.println("Account owner: ${acc.owner}, balance: $${acc.balance}");
};
```

Friend access can be restricted to protected and personal as well. If omitted, the default is private access to friend entities.

```eng
class account {
    prot string owner;
    priv double balance;

    friend print_owner, prot print_account;
};

fn print_account(acc: account) {
    io.println("Account balance: $${acc.balance}");
};

fn print_owner(acc: account) {
    io.println("Account owner: ${acc.owner}, balance: $${acc.balance}");
};
```

### 7.13. Inheritance and Polymorphism

Classes supports inheritance, including single inheritance, multi-level inheritance, multiple inheritance or hybrid of them.

```eng
class painter {
    let x: float;
    let y: float;

    virt fn draw() { #{ ... }# };
};

class brush: painter {
    let thickness: float;
    let pattern: pixel_pattern;
    orid fn draw() { #{ ... }# };
};

class pencil: painter {
    let thickness: float;
    let shape: pixel_shape;
    orid fn draw() { #{ ... }# };
};

fn main() {
    let my_painter: painter% = brush();

    my_painter.draw(); # Calls brush.draw();
};
```

The `%` symbol indicates that the variable is a polymorphic reference, allowing it to hold any derived class of the base class.

Classes also supports specifying the access modifier for inheriting, respecting the following order: `pub` -> `pers` -> `prot` -> `priv`.

```eng
class scrubber: prot painter, priv eraser {
    orid fn draw() { #{ ... }# };
    orid fn undraw() { #{ ... }# };
};
```

### 7.14. Virtual and Override

Members, including functions and variable, can be declared as `virt`. Virtual members can be overriden by derived classes.

```eng
class painter {
    let x: float;
    let y: float;

    virt fn draw() { #{ ... }# };
};

class brush: painter {
    let thickness: float;
    let pattern: pixel_pattern;
    virt orid fn draw() { #{ ... }# };
};
```

Note: Only virtual members can be overriden. And overriding is explicit.

Virtual properties:

```eng
import math: eng.std.math;

class painter {
    virt let x: prop: float;
    virt let x: prop: float;
};

class brush: painter {
    let center_x: float;
    let center_y: float;
    let radius: float;
    let angle: float;

    orid let x: prop: float {
        get() { return center_x + radius * math.cos(angle); }
        set(value: float) { center_x = radius * math.cos(angle) - value; }
    };

    orid let y: prop: float {
        get() { return center_x + radius * math.sin(angle); }
        set(value: float) { center_x = radius * math.sin(angle) - value; }
    };
};
```

### 7.15. Diamond Inheritance

By default, a diamond-inheritance uses copies of members of the grandbase clase in each of the base classes of a class. It can be resolved using `base as base_type` since `base` is a value of variant of all the base classes.

```eng
class first {
    let value: int;

    ctor {
        value = 10;
    };
};

class second: first {
    ctor {
        value += 20;
    };
};

class third: first {
    ctor {
        value += 30;
    };
};

class fourth: second, third {
    ctor {
        (base as second).value += 40;
        (base as second).value += 50;
    };
};

fn main() {
    let f = fourth();

    io.println("Value of fourth: ${fourth.(base as second).value} and ${fourth.(base as third).value}"); # Prints: Value of fourth: 70 and 90
};
```

The two copies can be eliminated into one by catalyzing the `first` grandbase class for both of our `second` and `third` base classes:

```eng
class first {
    let value: int;

    ctor {
        value = 10;
    };
};

class second: first {
    ctor {
        value += 20;
    };
};

class third: first {
    ctor {
        value += 30;
    };
};

class fourth: cata first(second, third) {
    ctor {
        base.value += 40;
        base.value += 50;
    };
};

fn main() {
    let f = fourth();

    io.println("Value of fourth: ${fourth.base.value}"); # Prints; Value of fourth: 150
};
```

### 7.16. Abstract Classes

Classes with virtual members without an implementation to fall back is considered an abstract class. An abstract class can still be used to create values. The virtual members are not resolved and `null`.

```eng
class abstract_class {
    virt fn virtual_function() -> void;
};

fn main() {
    let abstract_value = abstract_class();
    # abstract_value.virtual_function here is null. Calling null function causes `null_reference` exception to be thrown.
};
```

A polymorphic abstract class can be used, which resolves to concrete base with an implementation.

```eng
class abstract_class {
    virt fn virtual_function() -> void;
};

class concrete_class: abstract_class {
    orid fn virtual_function() {
        io.println("Hello, World!");
    };
};

fn main() {
    let abstract_value: abstract_class% = concrete_class();
    abstract_value.virtual_function(); # Prints "Hello, World!"
};
```

### 7.17. Retaining Instance Variables

Instance variables can be declared `retain` to allow them to retain their value across different instances.

```eng
class user {
    retain let id_counter = 0;
    let id = id_counter++;
    let name: string;
};

fn main() {
    let u1 = user(.name = "Alice");
    let u2 = user(.name = "Bob");
    let u3 = user(.name = "Charles");

    io.println("User: name: ${u1.name}, ID: ${u1.id}"); # Prints "User: name: Alice, ID: 0"
    io.println("User: name: ${u2.name}, ID: ${u2.id}"); # Prints "User: name: Bob, ID: 1"
    io.println("User: name: ${u3.name}, ID: ${u3.id}"); # Prints "User: name: Charles, ID: 2"
};
```

They can also restrict access using `priv`, `prot` or `pers`.

### 7.18. Member Functions as First-Class Citizens

Member functions can be treated as first-class values, meaning they can be assigned to variables, passed around, and called independently of their instances.

Example:

```eng
class calculator {
    fn add(a: int, b: int) -> int {
        return a + b;
    };
};

let calc = calculator();
let add_func = calc.add;

let result = add_func(2, 3); # Calls calc.add(2, 3)
```

### 7.19. Mutable Constant Instances

Mutable members can mutate its value even if an instance of the class is a constant.

```eng
class dataset {
    let data: prop {
        let values = [ 1, 2, 3, 4, 5 ];

        get {
            return values;
        };

        set(new_values) {
            values = new_values;
            is_sum_cached = false;
        };
    };

    mut let is_sum_cached = false;
    mut let cached_sub = 0;

    fn get_sum() {
        if (!is_sum_cached) {
            cached_sub = sum(data);
            is_sum_cached = true;
        };
        return cached_sub;
    };
};

fn main() {
    let my_set: dataset!;

    io.println("My set's sum of data: ${my_set.get_sum()}");
};
```

You may also declare member to be mutable only when the instance is constant using `immut`.

```eng
class counter {
    immut let count = 0;

    fn increment() {
        count++; # Invalid if instance is mutable
    };
};

fn main() {
    let my_counter: counter!; # Constant instance

    my_counter.increment(); # Valid

    let another_counter: counter; # Mutable instance

    another_counter.increment(); # Invalid (cannot call this function on mutable instance)
};
```

### 7.20. Class Reopening

Classes can be extended without creating a new name for it by defining the class using the same name.

`vector.eng`:
```eng
export class vector {
    let x: int;
    let y: int;
};

export fn length(v: vector) {
    return v.x ** 2 + v.y ** 2;
};
```

`main.eng`:
```eng
import vector, length;

class vector { # Extend vector to add z component
    let z: int;
};

fn cross(v1: vector, v2: vector) {
    return vector(
        .x = v1.y * v2.z - v1.z * v2.y;
        .y = v1.z * v2.x - v1.x * v2.z;
        .z = v1.x * v2.y - v1.y * v2.x;
    );
};
```

Since `int` is a class, we can also do this:

```eng
class int {
    let cache_ast: ast;
    fn parse(expression: string) {
        # parse expression and cache ast into cache_ast
        return this;
    };

    fn evaluate() -> int {
        return cache_ast.evaluate();
    };
};

fn main() {
    let value: int = int.parse("1 + 1").evaluaet();
    io.println("Value: $value");
};
```

### 7.21. Class Unpacking

Accessible members of a class can be destructured into variables when using multi-variable declaration.

```eng
import date: eng.std.date;

class image {
    let name: string;
    let last_mod: date;
    let width: int;
    let height: int;
    let pixels: pixel[ ];
};

fn main() {
    let img = load_image("./Sunshine and Rainbows.png");
    let (w, h, px) = img.(width, height, pixels);
};
```

Or implicitly by specifying all public members:

```eng
import date: eng.std.date;

class image {
    let name: string;
    let last_mod: date;
    let width: int;
    let height: int;
    let pixels: pixel[ ];
};

fn main() {
    let img = load_image("./Sunshine and Rainbows.png");
    let (n, lm, w, h, px) = img;
};
```

### 7.22. Anonymous Class Declaration

Classes can be used without providing a name for the class by using them anonymously in the code.

```eng
fn main() {
    let button = class: node {
        orid fn draw() {
            draw_rec(10, 10, 80, 20, "Click me!");
        };
    }();

    render(button);
};
```

## 8. Namespaces

Namespaces can be used to group related entities for organizing the codebase. They are declared using `ns` keyword.

```eng
ns maths {
    fn add(a: int, b: int) return a + b;
    fn sub(a: int, b: int) return a - b;
};
```

Use with qualification:

```eng
fn main() {
    let result = maths.add(1, 1);
    let result = maths.sub(4, 2);
};
```

Namespace can be declared in any scope, not just global, including function, control flow, classes, etc.

```eng
fn main() {
    ns maths {
        fn add(a: int, b: int) return a + b;
        fn sub(a: int, b: int) return a - b;
    };

    let result = maths.add(1, 1);
    let result = maths.sub(4, 2);
};
```

### 8.1. Dotted Declaration

Namespaces can be implicitly nested using dotted declaration symtax. Instead of:

```eng
ns outer {
    ns inner {
        let value = 10;
    };
};
```

Declaring inner namespace can be done using dotted declaration:

```eng
ns outer.inner {
    let value = 10;
};
```

Using dotted declaration for anything is possible, not just namespaces.

```eng
let outer.inner.value = 10;

fn outer.inner.action() -> void {
    io.println("Performing action...");
};

class outer.inner.record {
    let id: int;
    let name: string;
};
```

They are equivalent to:

```eng
ns outer {
    ns inner {
        let value = 10;

        fn action() -> void {
            io.println("Performing action...");
        };

        class record {
            let id: int;
            let name: string;
        };
    };
};
```

### 8.2. Extension

A namespace can extend other namespaces. The existing namespace contents becomes aliases in the new namespace.

```eng
ns base {
    fn greet() { print("Hello"); };
};

ns extended: base {
    fn farewell() { print("Goodbye"); };
};
```

### 8.3. Access Specifiers

Just like classes, namespaces can also have access specifiers: Public, Private and Protected (note: Personal is invalid in context of Namespace, as it would be equivalent to private).

```eng
ns utils {
    # Only usable in utils namespace.
    priv fn helper_printer(str: string) {
        io.println("Helper: $string");
    };

    # Only usable in utils namespace or any namespace that extends utils.
    prot fn printer(str: string) {
        helper_printer(string);
    };

    # Allow access by any code (default).
    pub fn print(str: string) {
        printer(string);
    };
};

ns color_utils: utils {
    fn print_colored(str: string) {
        printer("\x1b[31m$string");
    };
};
```

Specifying friend namespaces, classes or functions is also possible to allow access to protected or private members.

```eng
ns utils {
    # Only usable in utils namespace.
    priv fn helper_printer(str: string) {
        io.println("Helper: $string");
    };

    # Only usable in utils namespace or any namespace that extends utils.
    prot fn printer(str: string) {
        helper_printer(string);
    };

    # Allow access by any code (default).
    pub fn print(str: string) {
        printer(string);
    };

    friend priv color_utils;
};

ns color_utils: utils {
    fn print_colored(str: string) {
        helper_printer("\x1b[31m$string");
    };
};
```

### 8.4. Implicit Contents

Code entities can be implicitly encapsulated into a namespace by declaring a namespace without body:

```eng
ns components;

class button { #{ ... }# }; # Actual name: components.button
class label { #{ ... }# }; # Actual name: components.label
class tooltip { #{ ... }# }; # Actual name: components.tooltip
```

This is possible only in global scope or namespace scope.

### 8.5. Spilling Content

Namespace contents can be spilled into the outer scope to use the contents without having to specify the namespace.

```eng
import io: eng.std.io;

fn main() {
    ns: io; # Spill contents into main's scope
    println("Hello, World!"); # Same as io.println("Hello, World!")
};
```

## 9. Importing and Exporting

Importing and exporting allows working using multiple files and dependencies.

`adder.eng`:
```eng
export ns adder; # Note: does not need to be the name of the file

fn add_10(x: int) { return x + 10; };
```

`main.eng`:
```eng
import adder; # Name of the export

fn main() {
    let value = adder.add_10(20); # 30
};
```

Note for CLI users: all the files that provide exports needs to be provided for resolution.

Exporting other entities also works, not just namespaces.

`adder.eng`:
```eng
export fn add_10(x: int) { return x + 10; };
export fn add_20(x: int) { return x + 20; };
export fn add_30(x: int) { return x + 30; };
export fn add_40(x: int) { return x + 40; };
```

`main.eng`:
```eng
import add_10, add_20, add_30, add_40;

fn main() {
    let value = add_10(20); # 30
    let value = add_20(20); # 40
    let value = add_30(20); # 50
    let value = add_40(20); # 60
};
```

It does not matter where the file is located. The import syntax always looks for the import name, not the file location.

Importing contents into a user defined namespace is also possible:

`adder.eng`:
```eng
export ns utils.math.adder;

fn add_10(x: int) { return x + 10; };
```

`main.eng`:
```eng
import adder: utils.math.adder;

fn main() {
    let value = adder.add_10(20); # 30
};
```

Or, import contents to global:

`main.eng`:
```eng
import: utils.math.adder;

fn main() {
    let value = add_10(20); # 30
};
```

Importing and Exporting is only possible in global scope.

## 10. Enumerators

Enumerators allows declaring multiple named constants without specifying value.

```eng
enum colors {
    red,
    green,
    blue; # A semicolon is mandatory
};

fn main() {
    io.println("Red: ${colors.red}");     # Prints "Red: 0"
    io.println("Green: ${colors.green}"); # Prints "Green: 1"
    io.println("Blue: ${colors.blue}");   # Prints "Blue: 2"
};
```

### 10.1. Enums as Classes

Enums are a special type of class, where named declarations are instances of the type of the enum. By default, enums inherit `int`. But we can also inherit any other type.

```eng
enum colors: string {
    black   = "\x1b[30m",
    red     = "\x1b[31m",
    green   = "\x1b[32m",
    yellow  = "\x1b[33m",
    blue    = "\x1b[34m",
    magenta = "\x1b[35m",
    cyan    = "\x1b[36m",
    white   = "\x1b[37m",
    reset   = "\x1b[0m";
};

fn main() {
    io.println("black: ${colors.black}Text${colors.reset}");       # Prints "black: Text" in black
    io.println("red: ${colors.red}Text${colors.reset}");           # Prints "red: Text" in red
    io.println("green: ${colors.green}Text${colors.reset}");       # Prints "green: Text" in green
    io.println("yellow: ${colors.yellow}Text${colors.reset}");     # Prints "yellow: Text" in yellow
    io.println("blue: ${colors.blue}Text${colors.reset}");         # Prints "blue: Text" in blue
    io.println("magenta: ${colors.magenta}Text${colors.reset}");   # Prints "magenta: Text" in magenta
    io.println("cyan: ${colors.cyan}Text${colors.reset}");         # Prints "cyan: Text" in cyan
    io.println("white: ${colors.white}Text${colors.reset}");       # Prints "white: Text" in white
};
```

All the enum values are of type that inherits string, so using members from the parent is also possible.

```eng
# ... Same enum class from earlier ...

fn main() {
    io.println("Count of black: ${colors.black.count}"); # string.count
};
```

The base type is inferred by the values of the enum members.

### 10.2. Enum Members

Since enum is a type of class, introducing new members in enum is possible.

```eng
enum colors {
    black   = 30,
    red     = 31,
    green   = 32,
    yellow  = 33,
    blue    = 34,
    magenta = 35,
    cyan    = 36,
    white   = 37,
    reset   = 0;

    fn as_aec() { # AEC = ANSI Escape Code
        return "\x1b[${this}m"; # Use this to access current enum value
    };
};

fn main() {
    io.println("Color as AEC: ${colors.green.as_aec()}Text${colors.black.as_aec()}"); # Prints "Color as AEC: Text" in green
};
```

### 10.3. Inheriting Enums

Inheriting from another enum inherits its value type as well as all the enum members of the enum.

```eng
enum colors {
    reset = 0;

    fn as_aec() {
        return "\x1b[${this}m";
    };
};

enum bg_colors: colors {
    bg_black   = 30,
    bg_red     = 31,
    bg_green   = 32,
    bg_yellow  = 33,
    bg_blue    = 34,
    bg_magenta = 35,
    bg_cyan    = 36,
    bg_white   = 37;
};

enum fg_colors: colors {
    fg_black   = 40,
    fg_red     = 41,
    fg_green   = 42,
    fg_yellow  = 43,
    fg_blue    = 44,
    fg_magenta = 45,
    fg_cyan    = 46,
    fg_white   = 47;
};

fn colorize(value: string, fg: fg_colors, bg: bg_colors) {
    return "${fg.as_aec()}${bg.as_aec()}${value}${colors.reset.as_aec()}";
};

fn colorize(value: string, color: colors) { # Accept any color
    return "${color.as_aec()}${value}${colors.reset.as_aec()}";
};
```

### 10.4. Default Value

By default, the default value of an enum instance if no initialization was specified is the first value member in the enum. The default value can be specified using `default = member` syntax in the enum.

```eng
enum colors {
    red,
    green,
    blue;

    default = green;
};
```

### 10.5. Member Generation

Enum members, in case if `int`, `float`, `char` or `bool`, without values specified are auto generated by taking the previous value and adding 1 to it. And for the first value, it defaults to the default value of the type.

```eng
enum values {
    quadruple, # 0
    double,    # 1
    single,    # 2
    half,      # 3
    quarter;   # 4
};
```

This behavior can be customized by using `first` and `next`.

```eng
enum values: float {
    quadruple, # 4
    double,    # 2
    single,    # 1
    half,      # 0.5
    quarter;   # 0.25

    first() {
        return 4;
    };

    next(prev) {
        return prev / 2;
    };
};
```

Bitmasks can be cleanly generated using the generators.

```eng
enum window_flags {
    resizable,
    transparent,
    msaa_4x_hint,
    maximized,
    minimized,
    run_background;

    first() {
        return 1;
    };

    next(prev) {
        return prev * 2;
    };
};
```

### 10.6. Member Iteration

Enum members can be iterated over by their appearance in the list. In case of inhereted values, they appear before the current members.

```eng
enum values {
    one = 1,
    two,
    zero = 0,
    three = 3,
    four;
};

fn main() {
    # Prints
    # Enum value: 1
    # Enum value: 2
    # Enum value: 0
    # Enum value: 3
    # Enum value: 4
    for let value in values {
        io.println("Enum value: ${value}");
    };
};
```

### 10.7. Enums as Sum Types

Enums can also be used as sum types by defining members with associated data.

```eng
enum shape {
    circle {
        let radius: float;
    },
    rectangle {
        let width: float;
        let height: float;
    },
    triangle {
        let base: float;
        let height: float;
    };
};

fn area(s: shape) {
    switch s {
        case $ match circle(let r = .radius) {
            return 3.14159 * r * r;
        }
        case $ match rectangle(let w = .width, let h = .height) {
            return w * h;
        }
        case $ match triangle(let b = .base, let h = .height) {
            return 0.5 * b * h;
        }
    }
}
```

## 11. Properties

Properties allows using getter/setter as if they were variables. They provide a way to express intent seamlessly.

```eng
class vec2 {
    let x: float;
    let y: float;
};

op add(a: vec2 "+" b: vec2) -> vec2 {
    return vec2(.x = a.x + b.x, .y = a.y + b.y);
};

op sub(a: vec2 "-" b: vec2) -> vec2 {
    return vec2(.x = a.x - b.x, .y = a.y - b.y);
};

fn main() {
    let start = vec2(2.0, 3.0);
    let end = vec2(4.0, 5.0);

    let dir: prop: vec2 {
        get() -> vec2 {
            return end - start;
        };
        set(value: vec2) -> void {
            end = start + value;
        };
    };

    io.println("My line's direction: ${dir.x}, ${dir.y}");

    dir = vec2(6, 7);

    io.println("After changing my line's dir to 6, 7:");
    io.println("My line's start coordinate: ${start.x}, ${start.y}");
    io.println("My line's end coordinate: ${end.x}, ${end.y}");

    dir.x = 8; # Also works: creates a new vec2 to set.
};
```

### 11.1. Properties as Class

Properties are a special type of class that overloads all operators to go through getters and setters. They allow adding members to the type as well, support inheritance and polymorphism.

```eng
prop age_type {
    let _age = 0;

    get() { return _age; }
    set(value) { _age = value; }
};

let age: age_type;
```

### 11.2. Read-Only And Write-Only Properties

Properties can be made read-only by removing the setter, and write-only by removing the getter.

```eng
let global_transformation: prop { # Cannot set transformation, it is read-only.
    get {
        return global.transform(transformation);
    };
};
```

```eng
let current_password: prop { # Cannot get password, it is write-only.
    set(new_pswd: string) {
        password = new_pswd;
    };
};
```

## 12. Operator Overloading

Operator Overloading provides a way to overload existing operator with custom behavior or define new operators.

```eng
class vec2 {
    let x: float;
    let y: float;
};

op add(a: vec2 "+" b: vec2) -> vec2 {
    return vec2(.x = a.x + b.x, .y = a.y + b.y);
};

op sub(a: vec2 "-" b: vec2) -> vec2 {
    return vec2(.x = a.x - b.x, .y = a.y - b.y);
};
```

This overloads existing infix operators `+` and `-`.

### 12.1. Operator Types

There are 4 types of operators:

1. Prefix Operator

    ```eng
    op negation("-" value: float) {
        return negate(value);
    };
    ```

2. Suffix Operator

    ```eng
    op factorial(value: float "!") {
        return calculate_factorial(value);
    };
    ```

3. Infix Operator

    ```eng
    op addition(a: float "+" b: float) {
        return add(a, b);
    };
    ```

4. Multi-Part Operator

    ```eng
    op absolute("|" a: float "|") {
        return abs(a);
    };

    op index(a: map "[" b: string "]") {
        return a.at(b);
    };
    ```

### 12.2. Custom Operators

Defining custom operators requires specifying precedence as relative to other operator. And in case of infix operator, specifying associativity is also required. Only the valid operator symbols are allowed to be used when defining a custom operator.

```eng
# Operator (Left Associativy: <, Right Associativity: >) (Operator Function) (Lower Precedence: <, Higher Precedence: >, Equal Precedence: ==) [Existing Operator Function] (Syntax)

operator > titration > eng.lang.op.exponentiation (a: float "^^" b: float) {
    return titrate(a, b);
};
```

This defines a custom operator `^^` that performs titration (repeated exponentiation) of first operand with second operand. This new operator is higher precedence than exponential operator `**`, and is right-associative.

### 12.3. Auto Generation

Operators are not automatically generated. Meaning, defining `<` and `==` does not automatically generate `!=`, `>=`, `>` or `<=`. To make it ease to define operators, use the `comparison` macro.

```eng
eng.lang.gen.comparison!(): (a: float, b: float) {
    return a - b;
};
```

`eng.lang.gen.comparison` is a macro that takes a function (in this case, a trailing function) that generates operators using return value of the function as result of comparison.

If the return value is greater than 0, the operator `>` and `!=` will result in truth.

If the return value is equal to 0, the operators `==`, `<=` and `>=` will result in truth.

If the return value is less than 0, the operators `<` and `!=` will result in truth.

### 12.4. Overloading Operators for Functions

Operators can also be overloaded for functions as well, allowing function combinators.

```eng
op compose(a: fn (int) -> int "∘" b: fn (int) -> int) -> fn (int) -> int {
    return fn (x: int) -> int {
        return a(b(x));
    };
};

fn main() {
    fn add_2(x: int) -> int {
        return x + 2;
    };

    fn multiply_3(x: int) -> int {
        return x * 3;
    };

    let add_then_multiply = multiply_3 ∘ add_2;

    let result = add_then_multiply(4);
};
```

A specific function can be overloaded as well.

```eng
fn double(x: int) -> int {
    return x * 2;
};

op doubler(x: int ">" double) -> int {
    return double(x);
};

fn main() {
    let result = 5 > double;
};
```

## 13. Literal Typing

Literal typing allows customizing the type of the literal in code.

```eng
# Convert degrees to radians
lit deg(value: int | float) {
    return value * math.pi / 180.0;
};

fn main() {
    float value = 90_deg;
    io.println("Value: ${value}"); # Prints "Value: 1.570796327"
};
```

Customizing literals works on integer literals, floating point literals, string literals, character literals, array literals and tuple literals.

```eng
class point {
    let x: int;
    let y: int;
};

lit pt(value: (int, int)) {
    return point(value[ 0 ], value[ 1 ]);
};

lit pts(values: (point | (int, int))[ ]) {
    return values.map: {
        if value is point {
            return value as point;
        } else {
            let value = value as (int, int);
            return point(value[ 0 ], value[ 1 ]);
        }
    };
};

fn main() {
    let point = (1, 2)_pt;
    let points = [ point, (3, 4) ]_pts;
};
```

## 14. Custom Type Modifiers

Custom modifiers can be defined using the `mod` keyword. This allows defining new behaviors for types.

```eng
mod logged<class type "/"> {
    let value: type;

    ctor(value: type) {
        io.println("Creating logged value: ${value}");
        this.value = value;
    };

    dtor() {
        io.println("Destroying logged value: ${this.value}");
    };

    copy(new_value: logged<type>) {
        io.println("Copying logged value: ${new_value.value}");
        this.value = new_value.value;
    };

    copy(new_value: type) {
        io.println("Copying logged value from raw value: ${new_value}");
        this.value = new_value;
    };

    move(new_value: logged<type> &) {
        io.println("Moving logged value: ${new_value.value}");
        this.value = new_value.value;
        new_value.value = type(); # Reset moved-from value
    };

    move(new_value: type &) {
        io.println("Moving logged value from raw value: ${new_value}");
        this.value = new_value;
        new_value = type(); # Reset moved-from value
    };

    swap(other: logged<type> &) {
        io.println("Swapping logged values: ${this.value} <-> ${other.value}");
        let temp = this.value;
        this.value = other.value;
        other.value = temp;
    };

    get() -> type {
        io.println("Accessing logged value: ${this.value}");
        return value;
    };

    set(new_value: type) {
        io.println("Updating logged value from ${this.value} to ${new_value}");
        value = new_value;
    };
};

fn main() {
    let value: int/ = 42;
    value = 100;
    value -= 10;
    io.println("Final value: ${value}");

    #{
        Output:
        Creating logged value: 42
        Updating logged value from 42 to 100
        Accessing logged value: 100
        Updating logged value from 100 to 90
        Accessing logged value: 90
        Final value: 90
        Destroying logged value: 90
    }#
};
```

## 15. Macros

There are three types of macros:

### 15.1. Declarative Macros

Macros that are declared using pattern matching to generate code based on input patterns.

```eng
macro my_swap(a: var "my_swap" b: var) {
    return eng.quote.quote! {
        {
            ($a, $b) = ($b, $a);
        }
    };
};

fn main() {
    let x = 10;
    let y = 20;

    x my_swap y; # Swaps values of x and y

    io.println("x: ${x}, y: ${y}"); # Prints: x: 20, y: 10
};
```

### 15.2. Attribute Macros

Macros that are applied to code entities to modify their behavior or add additional functionality.

```eng
macro @component:<component_type: fn (...children) -> element>() {
    let component_name = eng.meta.function_name(component_type);
    return component_type + eng.quote.quote! {
        fn ${component_name}_wrapped(...children) -> element {
            let elem = $component_type(...children);
            elem.classes += " $component_name";
            return elem;
        };
    };
};

@component # Also generates button_wrapped function
fn button(on_click: fn -> void, ...children) -> element {
    return element("button", .on_click = on_click, .children = children);
};

fn main() {
    let btn = button("Click me!"): .on_click = fn {
        io.println("Button clicked!");
    };
};
```

### 15.3. Engine Macros

Macros that take raw source code as input and generate code based on it.

```eng
# Grammar for List Comprehension from Python:
#
# comp: mapping for_if_clause
#
# mapping: expression
#
# for_if_clause:
#     | 'for' pattern 'in' expression ( 'if' expression )*
#
# pattern: name (',' name)*

class comprehension: eng.syn.parser, eng.quote.quoter {
    let mapping: mapping;
    let for_if_clause: for_if_clause;

    fn parse(input: eng.syn.parse_stream) -> comprehension {
        let mapping = input.parse:<mapping>();
        let for_if_clause = input.parse:<for_if_clause>();
        return comprehension(.mapping, .for_if_clause);
    };

    fn quote(code: eng.quote.code_stream&) {
        code.extend(eng.quote.quote! {
            [
                for let item in ${for_if_clause.iterable} {
                    if (true && ${&& (${for_if_clause.conditions})}) {
                        emit $mapping;
                    }
                }
            ]
        });
    };
};

class mapping: eng.syn.parser, eng.quote.quoter {
    let expression: eng.syn.expression;

    fn parse(input: eng.syn.parse_stream) -> mapping {
        let expression = input.parse:<eng.syn.expression>();
        return mapping(.expression);
    };

    fn quote(code: eng.quote.code_stream&) {
        expression.quote(code);
    };
};

class for_if_clause: eng.syn.parser {
    let pattern: pattern;
    let iterable: eng.syn.expression;
    let conditions: condition[ ];

    fn parse(input: eng.syn.parse_stream) -> for_if_clause {
        let _ = input.parse:<eng.syn.token![ for ]>();
        let pattern = input.parse:<pattern>();
        let _ = input.parse:<eng.syn.token![ in ]>();
        let iterable = input.parse:<eng.syn.expression>();
        let conditions = parse_zero_or_more:<condition>(input, condition());
        return for_if_clause(.pattern, .iterable, .conditions);
    };
};

fn parse_zero_or_more:<class parser: eng.syn.parser>(input: eng.syn.parse_stream, parser: eng.syn.parser) -> parser[] {
    let results: parser[ ] = [ ];

    while let result = input.parse:<parser>() {
        results += result;
    };

    return result;
};

class pattern: eng.syn.parser, eng.quote.quoter {
    let pattern: eng.syn.pattern;

    fn parse(input: eng.syn.parse_stream) -> pattern {
        let pattern = input.parse(eng.syn.pattern.parse_single);
        return pattern(.pattern);
    };

    fn quote(code: eng.quote.code_stream&) {
        pattern.quote(code);
    };
};

class condition: eng.syn.parser, eng.quote.quoter {
    let expression: eng.syn.expression;

    fn parse(input: eng.syn.parse_stream) -> condition {
        let _ = input.parse:<eng.syn.token![ if ]>();
        let expression = input.parse:<eng.syn.expression>();
        return condition(.expression);
    };

    fn quote(code: eng.quote.code_stream&) {
        expression.quote(code);
    };
};

macro list_comp! [input] {
    let input = eng.syn.tokenize(input);
    let comprehension = eng.syn.parse_string:<comprehension>(input);
    return eng.quote.quote! {
        $comprehension
    };
};

fn main() {
    let evens_and_squares = list_comp! [ (x, x * x) for x in [ 1, 2, 3, 4, 5 ] if x % 2 == 0 ];

    #{
        The above expands to:

        ```eng
        let evens_and_squares = [
            for let item in [ 1, 2, 3, 4, 5 ] {
                if true && (item % 2 == 0) {
                    emit (item, item * item);
                }
            }
        ];
        ```
    }#

    io.println("Evens and their squares: ${evens_and_squares}"); # Prints: Evens and their squares: [ (2, 4), (4, 16) ]
};
```

## 16. Coroutines

### 16.1. Cooperative Usage

Coroutines are functions that can pause and resume their execution, allowing for cooperative multitasking and asynchronous programming.

```eng
import io: eng.std.io;
import time: eng.std.time;

async fn countdown(seconds: int) {
    for let i = seconds; i > 0; i-- {
        yield i;
        time.sleep(1); # Simulate asynchronous wait
    };

    io.println("Countdown complete!");
};

fn main() {
    let counter = countdown(5);

    while probe counter {
        let value = await counter;
        io.println("Countdown: ${value}");
    };

    #{
        Alternatively, using for-await loop:
        for let value await in counter {
            io.println("Countdown: ${value}");
        };
    }#
};
```

Note: Exceptions propagate through `await` points, allowing error handling in asynchronous code, even though coroutine functions are stackless.

### 16.2. Multiple Coroutine Tasks

Coroutine tasks are concurrent, and blocking only occurs at `await` points. Multiple coroutine tasks can be awaited simultaneously using `await (task1 || task2 || ...)` and `await (task1 && task2 && ...)` for awaiting any or all, along with `probe (task1 || task2 || ...)` and `probe (task1 && task2 && ...)` for probing any or all.

```eng
fn main() {
    let counter1 = countdown(5);
    let counter2 = countdown(3);

    while probe (counter1 || counter2) {
        let (value1, value2) = await (counter1 && counter2);

        if value1 != null {
            io.println("Counter 1: ${value1}");
        };

        if value2 != null {
            io.println("Counter 2: ${value2}");
        };
    };
};
```

### 16.3. Cancelling Coroutines

Coroutine functions can also be cancelled using `cease` keyword.

```eng
fn main() {
    let counter = countdown(10);

    while probe counter {
        let value = await counter;
        io.println("Countdown: ${value}");

        if value == 3 {
            cease counter; # Cancel the countdown when it reaches 3
            io.println("Countdown cancelled!");
        }
    };
};
```

### 16.4. Calling Non-Coroutine Functions Concurrently

Non-coroutine functions can be called concurrently using `async` keyword.

```eng
fn heavy_computation(x: int) -> int {
    time.sleep(2); # Simulate heavy computation
    return x * x;
};

fn main() {
    let task1 = async heavy_computation(5);
    let task2 = async heavy_computation(10);

    let result1 = await task1;
    let result2 = await task2;

    io.println("Result 1: ${result1}"); # Prints: Result 1: 25
    io.println("Result 2: ${result2}"); # Prints: Result 2: 100
};
```

## 17. Multi-threading

### 17.1. Creating Threads

Threads can be created using `fork` keyword, which runs the code in a separate thread. The `join` keyword is used to wait for the thread to finish.

```eng
fn main() {
    let thread = fork {
        for let i = 1; i <= 5; i++ {
            io.println("Thread: ${i}");
            time.sleep(1); # Simulate work
        };
    };

    io.println("Main thread is doing other work...");

    join thread; # Wait for the created thread to finish
    io.println("Thread has completed.");
};
```

Creating threads that resolve to a value can be done using `fork expression` syntax.

```eng
fn compute_sum(start: int, end: int) -> int {
    let sum = 0;
    for let i = start; i <= end; i++ {
        sum += i;
        time.sleep(1); # Simulate work
    };
    return sum;
};

fn main() {
    let thread = fork compute_sum(1, 5); # Creates a thread to compute sum from 1 to 5

    io.println("Main thread is doing other work...");
    let result = join thread; # Wait for the created thread to finish and get the result
    io.println("Sum from thread: ${result}"); # Prints: Sum from thread: 15
};
```

Thread ID can be obtained using `id` member.

```eng
fn main() {
    let thread = fork {
        io.println("Thread ID: ${this.id}"); # Prints the thread ID
    };

    io.println("Main Thread ID: ${this.id}"); # Prints the main thread ID

    join thread; # Wait for the created thread to finish
};
```

Checking if thread is alive can be done using `alive` keyword.

```eng
fn main() {
    let thread = fork {
        time.sleep(3); # Simulate work
    };

    while alive thread {
        io.println("Thread is still running...");
        time.sleep(1);
    };

    io.println("Thread has completed.");
};
```

### 17.2. Shared Memory

Shared memory between threads can be achieved using two mechanisms: `mutex` and `atomic` types.

```eng
fn main() {
    mutex counter_mutex {
        let counter = 0;
    };

    let thread1 = fork {
        for let i = 0; i < 1000; i++ {
            lock counter_mutex;
            counter += 1;
            unlock counter_mutex;
        };
    };

    let thread2 = fork {
        for let i = 0; i < 1000; i++ {
            lock counter_mutex;
            counter += 1;
            unlock counter_mutex;
        };
    };

    join thread1;
    join thread2;

    io.println("Final counter value: ${counter}"); # Prints: Final counter value: 2000
};
```

Automatic locking and unlocking can be done using `defer` keyword.

```eng
lock counter_mutex;
defer unlock counter_mutex;
counter += 1;
```

Alternatively, mutex can take a block directly to indicate critical section.

```eng
counter_mutex: fn {
    counter += 1;
};
```

Atomic types provide lock-free shared memory access for basic types.

```eng
fn main() {
    atomic let counter: int = 0;

    let thread1 = fork {
        for let i = 0; i < 1000; i++ {
            counter += 1;
        };
    };

    let thread2 = fork {
        for let i = 0; i < 1000; i++ {
            counter += 1;
        };
    };

    join thread1;
    join thread2;
};
```

### 17.3. Memory Ordering

Atomic operations support memory ordering to control visibility of memory operations across threads.

```eng
atomic let flag: bool = false;
atomic let data: int = 0;

fn writer_thread() {
    data = 42; # Sequentially consistent write by default
    rel flag = true; # Release operation (guarantees prior writes are visible)
};

fn reader_thread() {
    if acq flag { # Acquire operation (guarantees subsequent reads see prior writes)
        let value = data; # Sequentially consistent read by default
        io.println("Data: ${value}"); # Prints: Data: 42
    };
};

fn main() {
    let writer = fork writer_thread;
    let reader = fork reader_thread;

    join writer;
    join reader;
};
```

Other ordering includes `rlx` (relaxed), `seq` (sequentially consistent) and `ar` (acquire-release).

### 17.4. Thread-Local Storage

Thread-local storage allows defining variables that are unique to each thread using `par` keyword.

```eng
par let counter: int = 0;

fn increment_counter() {
    for let i = 0; i < 100; i++ {
        counter += 1;
    };
    io.println("Thread-local counter: ${counter}");
};

fn main() {
    let thread1 = fork increment_counter;
    let thread2 = fork increment_counter;

    join thread1;
    join thread2;
};
```

### 17.5. Thread Pools

Thread pools can be created using `pool` keyword to manage a pool of worker threads.

```eng
fn main() {
    let workers = pool 4;

    for let i = 0; i < 10; i++ {
        workers fork {
            io.println("Task ${i} is being processed by thread.");
            time.sleep(1); # Simulate work
        };
    }

    join workers; # Wait for all tasks to complete
};
```

Accessing the number of threads running in the pool can be done using `threads.count` member.

```eng
io.println("Number of threads in pool: ${workers.threads.count}");
```

Total capacity of the pool can be accessed using `capacity` member.

```eng
io.println("Thread pool capacity: ${workers.capacity}");
```

Individual threads in the pool can be accessed using `threads[index]`.

```eng
let first_thread = workers.threads[0];
io.println("First thread ID: ${first_thread.id}");
join first_thread; # Join only the first thread in worker, removing it from the pool after completion
```

## 18. Generics and Concepts

### 18.1. Generics

Generics allows defining functions, classes and other entities that can operate on different types without being tied to a specific type.

```eng
fn my_swap:<class type>(a: type&, b: type&) {
    (a, b) = (b, a);
};

fn main() {
    let x = 10;
    let y = 20;

    my_swap:<int>(x, y);

    io.println("x: ${x}, y: ${y}"); # Prints: x: 20, y: 10

    let str1 = "Hello";
    let str2 = "World";

    my_swap:<string>(str1, str2);

    io.println("str1: ${str1}, str2: ${str2}"); # Prints: str1: World, str2: Hello

    # Using type inference

    let a = 3.14;
    let b = 1.59;

    my_swap(a, b); # Type inferred as float

    io.println("a: ${a}, b: ${b}"); # Prints: a: 1.59, b: 3.14
};
```

### 18.2. Concepts

Generics can also be constrained using concepts to restrict the types that can be used with the generic entity.

```eng
concept addable {
    retain fn add(a: self, b: self) -> self;
};

fn sum:<class type: addable>(a: type, b: type) -> type {
    return type.add(a, b);
};

class my_number {
    let value: int;

    retain fn add(a: my_number, b: my_number) -> my_number {
        return my_number(.value = a.value + b.value);
    };
};

class not_a_number {
    let name: string;
};

fn main() {
    let num1 = my_number(.value = 10);
    let num2 = my_number(.value = 20);

    let result = sum(num1, num2);
    io.println("Sum: ${result.value}"); # Prints: Sum: 30

    let non_num1 = not_a_number(.name = "Alice");
    let non_num2 = not_a_number(.name = "Bob");

    # The following line would cause an error because not_a_number does not satisfy the addable concept.
    #let invalid_result = sum(non_num1, non_num2);
};
```

### 18.3. Concepts on Classes

Constraints can also be applied to class definitions.

```eng
concept comparable {
    fn less_than(a: self, b: self) -> bool;
};

class pair: comparable {
    let first: int;
    let second: int;

    # This will error if not implemented
    retain fn less_than(a: pair, b: pair) -> bool {
        return a.first < b.first;
    };
};
```

### 18.4. `auto` and Constrained `auto`

Use of `auto` keyword allows a concept to define a weaker constraint that can be satisfied by any type that has the required members.

```eng
concept has_length {
    fn length() -> auto;
};

fn print_length:<class type: has_length>(obj: type) {
    io.println("Length: ${obj.length()}");
};

class my_string {
    let value: string;

    fn length() -> int {
        return value.count;
    };
};

class vector {
    let x: float;
    let y: float;

    fn length() -> float {
        return math.sqrt(x ** 2 + y ** 2);
    };
};

fn main() {
    let str_obj = my_string(.value = "Hello, World!");
    print_length(str_obj); # Prints: Length: 13

    let vec_obj = vector(.x = 3.0, .y = 4.0);
    print_length(vec_obj); # Prints: Length: 5.0
};
```

A constrained `auto (type1, type2, ...)` can also be used to define a concept that requires any of the specified types.

```eng
concept numeric {
    fn add(a: self, b: self) -> auto (int, float);
};

fn sum:<class type: numeric>(a: type, b: type) -> auto (int, float) {
    return type.add(a, b);
};

class my_int {
    let value: int;

    fn add(a: my_int, b: my_int) -> int {
        return a.value + b.value;
    };
};

class my_float {
    let value: float;

    fn add(a: my_float, b: my_float) -> float {
        return a.value + b.value;
    };
};
```

### 18.5. Concepts as Polymorphic Interfaces

Concepts can also be used outside of generics to become polymorphic interfaces.

```eng
concept printable {
    fn print() -> void;
};

fn print_if_printable(obj: printable%) {
    obj.print();
};

class my_printable {
    let value: string;

    fn print() -> void {
        io.println(value);
    };
};

fn main() {
    let printable_obj = my_printable(.value = "Hello, Printable!");
    print_if_printable(printable_obj); # Prints: Hello, Printable!

    class non_printable {
        let data: int;
    };

    let non_printable_obj = non_printable(.data = 42);

    # The following line would cause an error because non_printable does not satisfy the printable concept.
    #print_if_printable(non_printable_obj);
};
```

### 18.6. Arbitrary Constraints

Concepts can also define arbitrary constraints using `where` clause.

```eng
concept numeric_32_64 {
    where sizeof self == 4 || sizeof self == 8; # Only allow int and float types
};

concept signed_numeric {
    # Using built-in concepts
    where eng.type.is_numeric:<self>;
    where eng.type.is_signed:<self>;
};

concept triangular_matrix {
    where self.rows == 3 && self.columns == 3; # Note: self.rows and self.columns must also exist as members
};
```

## 19. Array Operations

### 19.1. Element-wise Operations

Arrays support advanced array-programming operations such as element-wise arithmetic, comparison and logical operations. They work only on arrays of same size.

```eng
let a = [ 1, 2, 3 ];
let b = [ 4, 5, 6 ];

let c = a [+] b;    # c is [ 5, 7, 9 ]
let d = a [*] b;    # d is [ 4, 10, 18 ]
let e = a [==] b;   # e is [ false, false, false ]
```

If the arrays are of different sizes, you can use `[+>` or `<+]` variants to use minimum of two (shortest of two, excluding remaining elements) or maximum of two (longest of two, including remaining elements as-is).

```eng
let a = [ 1, 2, 3 ];
let b = [ 4, 5 ];
let c = a [+> b;   # c is [ 5, 7, 3 ]
let d = a <+] b;   # d is [ 5, 7 ]
let e = a [*> b;   # e is [ 4, 10, 3 ]
let f = a <*] b;   # f is [ 4, 10 ]
```

### 19.2. Array Pipeline

Array pipeline provides a way to chain multiple array operations (combinators) together in a readable manner. Each combinator takes the array from the previous step as input and produces a new array as output.

```eng
import: eng.std.arrayops; # Global import

# Sample arrays
let nums1 =         [ 1, 2, 3, 4, 5 ];
let nums2 =         [ 6, 7, 8, 9, 10 ];
let nums3 =         [ 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 ];
let orderless =     [ 3, 1, 4, 5, 2 ];
let duplicates =    [ 3, 1, 4, 3, 2, 1, 5, 4 ];
let str =           "arrays!";
let str2 =          "are cool!";

# Basic combinators
let mapped =        nums1 -> map(): fn (x) => x * x;            # [ 1, 4, 9, 16, 25 ]
let filtered =      nums1 -> filter(): fn (x) => x % 2 == 0;    # [ 2, 4 ]
let sorted =        orderless -> sort();                        # [ 1, 2, 3, 4, 5 ]
let uniqued =       duplicates -> unique();                     # [ 3, 1, 4, 2, 5 ]

# Advanced combinators
let take_first_2 =  nums1 -> take_first(2);                     # [ 1, 2 ]
let take_last_2 =   nums1 -> take_last(2);                      # [ 4, 5 ]
let drop_first_2 =  nums1 -> drop_first(2);                     # [ 3, 4, 5 ]
let drop_last_2 =   nums1 -> drop_last(2);                      # [ 1, 2, 3 ]
let reduced_sum =   nums1 -> reduce(0): fn (a, b) => a + b;     # 15
let grouped =       nums3 -> group(2):                          # [ [ 1, 2 ], [ 2, 3 ], [ 3, 3 ], [ 4, 4 ], [ 4, 4 ], [ 5, 5 ], [ 5, 5 ], [ 5 ] ]
let grouped_by =    nums3 -> group_by(): fn (a, b) => a == b;   # [ [ 1 ], [ 2, 2 ], [ 3, 3, 3 ], [ 4, 4, 4, 4 ], [ 5, 5, 5, 5, 5 ] ]
let flattened =     grouped_by -> flatten();                    # [ 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 ]
let slided =        nums1 -> slide(3);                          # [ [ 1, 2, 3 ], [ 2, 3, 4 ], [ 3, 4, 5 ] ]
let nthed =         nums1 -> nth(2);                            # [ 1, 3, 5 ]
let zipped =        (nums1, nums2) -> zip();                    # [ (1, 6), (2, 7), (3, 8), (4, 9), (5, 10) ]
let adjacented =    nums1 -> adjacent(): fn (a, b) => a * b;    # [ 3, 5, 7, 9 ]
let enumerated =    str -> enumerate();                         # [ (0, 'a'), (1, 'r'), (2, 'r'), (3, 'a'), (4, 'y'), (5, 's'), (6, '!') ]
let joined =        (str, str2) -> join(" ");                   # "arrays! are cool!"

# Parallel combinators
let sqr_n_sqrt =    (nums1, nums1)
    -> (map(): fn (x) => x * x, map(): fn (x) => math.sqrt(x)); # ([ 1, 4, 9, 16, 25 ], [ 1.0, 1.4142135, 1.7320508, 2.0, 2.2360679 ])
```

Note: Several combinators can also take optional addition parameters:
- `group()` can also take `step` parameter to specify the step size between groups, and also `reverse` parameter to indicate whether to group from the end (groups nor resulting array themselves are not reversed).
    - Note: `step` larger than `size` will effectively create gaps between groups.
- `slide()` can also take `step` parameter to specify the step size between slides.
- `nth()` can also take `offset` parameter to specify the starting index for n-th selection.

Example: Sushi for two:

```eng
# Our sushies
let sushi = [ 1, 2, 2, 1, 2, 2, 2, 1, 1 ];

# Solution
let solution = sushi
    -> group_by(): (x == y)
    -> map(): (x.count)
    -> adjacent(): min
    -> max() * 2; # 4
```

These combinators are non-exhaustive. There are several other combinators such as `differ`, `indices_of`, `deltas`, `singles`, `keys` (first in pair), `values` (last in pair), etc. in the standard library. Several combinators are also parallelized for performance. They all work with lazy arrays and produce lazy arrays where applicable.

### 19.3. Placeholder Pipeline

An alternative pipeline operator `|>` can be used with a placeholder `$` to indicate the input array. In case of an array of tuples, the `$0`, `$1`, ... can be used to indicate an array of first, second, ... elements of the tuples respectively.

```eng
let values = [ 1, 2, 3, 4, 5 ];
let crazy = values
    |> zip($, $ [*] $)  # [ (1, 1), (2, 4), (3, 9), (4, 16), (5, 25) ]
    |> $0 [+] $1        # [ 2, 6, 12, 20, 30 ]
    |> ($, $ [*] 2);    # [ (2, 4), (6, 12), (12, 24), (20, 40), (30, 60) ]
    |> $1               # [ 4, 12, 24, 40, 60 ]
    -> max();           # 60
```

Let's make our sushi solution faster using `|>` operator:

```
# Solution2, faster
let solution2 = sushi
    -> adjacent(): (x != y)
    -> enumerate()
    -> indices()
    |> [ 0 ] + $ + [ sushi.count ]
    -> adjacent(): (x - y)
    -> adjacent(): (x <? y)
    -> max() * 2; # 4
```

### 19.4. Custom Combinators

Custom combinators can be defined by overloading the `->` or `|>` operators for combinators function.

```eng
fn double(value: int) => value * 2;

op double_combinator(input: int "->" double) { # Automatically parallelizable
    return double(input);
};

fn main() {
    let nums = [ 1, 2, 3, 4, 5 ];
    let doubled = nums -> double; # [ 2, 4, 6, 8, 10 ]

    io.println("Doubled: ${doubled}"); # Prints: Doubled: [ 2, 4, 6, 8, 10 ]
};
```

A more complex, unparallelizable combinator takes array as input, and parallelizing it is manual.

```eng
fn scan_left(arr: bool[], target: bool, predicate: fn (bool, bool) -> bool) -> bool[] {
    let result = bool[ ];
    let accumulator = false;

    for let item in arr {
        accumulator = predicate(accumulator, item);
        result += accumulator;
    };

    return result;
};

op scan_left_combinator(input: bool[] "->" scan_left) {
    return scan_left:(input); # Bind input to first parameter, returning a function that takes remaining parameters.
};

fn filter_out_html_tags(input: string) -> string {
    return input
        -> map(): (x in "<>")
        |> adjacent($, $ -> scan_left(true): (x != y)): (x || y)
        |> zip($, input)
        -> filter(): fn (pair) => !pair[ 0 ]
        -> map(): fn (pair) => pair[ 1 ];
};
```

## 20. Undefining Entities

Every entity defined in Engenide can be undefined using `undef` keyword. This includes functions, classes, variables, namespaces, operators, macros, concepts, etc.

```eng
fn my_function() {
    io.println("Hello, World!");
};

fn main() {
    my_function(); # Prints: Hello, World!

    undef my_function;

    my_function(); # Error: my_function is not defined
};
```

Undefining is scope-aware. Undefining an entity in a scope only removes it from that scope and inner scopes, but not from outer scopes.

```eng
fn my_function() {
    io.println("Hello, World!");
};

fn main() {
    my_function(); # Prints: Hello, World!

    {
        undef my_function;

        my_function(); # Error: my_function is not defined
    };

    my_function(); # Prints: Hello, World!
};
```

## 21. Interoperability with C

Engenide programs can be interoperated with C or external C-linkage functions as so:

`main.c`:
```c
#include <stdio.h>

extern int square(int value);

int main(void) {
	int squared_value = square(10);
	printf("Squared value: %d\n", squared_value);
}
```

`square.eng`:
```eng
@c_export
fn square(value: int) {
	return value ** 2;
};
```

Or the other way around:

`square.c`:
```c
int square(int value) {
	return value * value;
}
```

`main.eng`:
```eng
import io: eng.std.io;

@c_import
fn square(value: int) -> int;

fn main() {
	let squared_value = comply "C" square(10); # Calling C from Engenide requires complying to "C" requirement.
	io.println("Squared value: ${squared_value}");
};
```

Classes can also be interoperated with C structs if used with `@c_struct` attribute.

`main.eng`:
```eng
import io: eng.std.io;

@c_struct
class point {
    let x: float;
    let y: float;
};

@c_import
fn translate_point(p1: point, p2: point) -> point;

@c_export
fn scale_point(p: point, factor: float) -> point {
    return point(.x = p.x * factor, .y = p.y * factor);
};

# Example - Engenide
fn main() {
    let p1 = point(.x = 1.0, .y = 2.0);
    let p2 = point(.x = 3.0, .y = 4.0);

    let translated_point = comply "C" translate_point(p1, p2);
    io.println("Translated Point: (${translated_point.x}, ${translated_point.y})");

    let scaled_point = scale_point(p1, 2.0);
    io.println("Scaled Point: (${scaled_point.x}, ${scaled_point.y})");
};
```

`main.c`:
```c
#include <stdio.h>

typedef struct {
    float x;
    float y;
} point;

point translate_point(point p1, point p2) {
    point result;
    result.x = p1.x + p2.x;
    result.y = p1.y + p2.y;
    return result;
}

extern point scale_point(point p, float factor);

// Example - C
int main(void) {
    point p1 = {1.0f, 2.0f};
    point p2 = {3.0f, 4.0f};

    point translated_point = translate_point(p1, p2);
    printf("Translated Point: (%.2f, %.2f)\n", translated_point.x, translated_point.y);

    point scaled_point = scale_point(p1, 2.0f);
    printf("Scaled Point: (%.2f, %.2f)\n", scaled_point.x, scaled_point.y);
}
```

## 22. Manual Memory Management

Engenide provides manual memory management capabilities through the `alloc`, `dealloc`, and `realloc` keywords. They can optionally take a pager to allocate memory from a specific memory allocator.

```eng
let ptr = alloc 100; # Allocate 100 bytes of memory
# Use the allocated memory...
dealloc ptr; # Deallocate the memory
```

Reallocating memory can be done using `realloc` keyword.

```eng
let ptr = alloc 100; # Allocate 100 bytes of memory
# Use the allocated memory...
ptr = realloc ptr, 200; # Reallocate to 200 bytes
# Use the reallocated memory...
dealloc ptr; # Deallocate the memory
```

Custom pagers can be defined by implementing the `eng.memory.pager` concept.

```eng
class my_pager: eng.memory.pager {
    fn allocate(size: int) -> void* {
        # Custom allocation logic
    };

    fn deallocate(ptr: void*) {
        # Custom deallocation logic
    };

    fn reallocate(ptr: void*, new_size: int) -> void* {
        # Custom reallocation logic
    };
};

fn main() {
    let pager = my_pager();

    let ptr = alloc pager, 100; # Allocate 100 bytes using custom pager
    # Use the allocated memory...
    dealloc pager, ptr; # Deallocate the memory using custom pager
};
```

## 23. Reflection

### 23.1. Type Introspection

Type introspection allows inspecting type information at runtime.

```eng
fn main() {
    let type_info = eng.reflect.type_info:<int>;

    io.println("Type Name: ${type_info.name}");
    io.println("Size: ${type_info.size}");
};
```

Type introspection can also be used on user-defined types.

```eng
class person {
    let name: string;
    let age: int;

    fn greet() {
        io.println("Hello, my name is ${this.name} and I am ${this.age} years old.");
    };
};

fn main() {
    let type_info = eng.reflect.type_info:<person>;

    io.println("Class Name: ${type_info.name}");
    io.println("Members:");
    for let member in type_info.members {
        io.println(" - ${member.name}: ${member.type_name}");

        if member.category == eng.reflect.member_category.property {
            io.println("   (Property)");
        } else if member.category == eng.reflect.member_category.field {
            io.println("   (Field)");
        }
    };

    io.println("Members:");
    for let member in type_info.member {
        io.println(" - ${member.name}()");
    };
};
```

### 23.2. Dynamic Invocation

Dynamic invocation allows invoking member function dynamically at runtime.

```eng
fn main() {
    let person_type = eng.reflect.type_info:<person>;
    let person_instance = person(.name = "Alice", .age = 30);

    let greet_member = person_type.get_member("greet") as eng.reflect.member_function;
    greet_member.invoke(person_instance);
};
```

Using dynamic invocation with member functions that take parameters and return values.

```eng
class calculator {
    fn add(a: int, b: int) -> int {
        return a + b;
    };
};

fn main() {
    let calculator_type = eng.reflect.type_info:<calculator>;
    let calculator_instance = calculator();

    let add_member = calculator_type.get_member("add") as eng.reflect.member_function;
    let result = add_member.invoke(.instance = calculator_instance, .args = (5, 10)).result as int;

    io.println("Result of addition: ${result}"); # Prints: Result of addition: 15
};
```

Members can also be accessed dynamically.

```eng
fn main() {
    let person_type = eng.reflect.type_info:<person>;
    let person_instance = person(.name = "Bob", .age = 25);

    let name_field = person_type.get_member("name");
    let name_value = name_field.get_value(person_instance) as string;

    io.println("Name: ${name_value}"); # Prints: Name: Bob
};
```

### 23.3. Reflecting Enum Types

Reflecting enum types allows inspecting enum members at runtime.

```eng
enum colors {
    red,
    green,
    blue;
};

fn main() {
    let enum_type = eng.reflect.type_info:<colors>;

    io.println("Enum Name: ${enum_type.name}");
    io.println("Members:");
    for let member in enum_type.members {
        if member.category == eng.reflect.member_category.enum_member {
            io.println(" - ${member.name}: ${member.value}");
        }
    };
};
```

## 24. Compile-time Evaluation

`static` keyword allows defining compile-time constants and functions that must be fully evaluated at compile-time.

```eng
static fn factorial(n: int) -> int {
    if n <= 1 {
        return 1;
    } else {
        return n * factorial(n - 1);
    };
};

fn main() {
    static let fact_5 = factorial(5); # Evaluated at compile-time

    io.println("Factorial of 5: ${fact_5}"); # Prints: Factorial of 5: 120
};
```

Note: Constant functions may include side-effects, such as I/O operations, global mutation and even calling foreign C code. These side-effects are executed at compile-time when the constant function is evaluated.

```eng
static fn greet() -> string {
    io.print("Enter your name: ");
    let name = io.scanln();
    io.println("Hello, ${name} from compile-time!");
    return name;
};

fn main() {
    let name = greet();
    io.println("Hello, ${name} from runtime!");
};
```

Test run:

```bash
$ eng compile
Enter your name: Alice
Hello, Alice from compile-time!
$ eng run
Hello, Alice from runtime!
```

Note: If compile-time evaluation fails, it results in a compile-time error.

Using `pure` and `static` together allows defining functions that are both pure and compile-time evaluable for guarantees that no side-effects occur in those functions.

```eng
pure static fn square(n: int) -> int {
    return n * n;
};
```

All entities code may be evaluated at compile-time regardless of whether they are marked `static` or not. To ensure an entity is not evaluated at compile-time, it can be marked with `dynamic` keyword.

```eng
dynamic fn get_current_time() -> string {
    return time.now().to_string();
};

fn main() {
    let current_time = get_current_time();
    io.println("Current time: ${current_time}");
};
```

## 25. Tooling

### 25.1. CLI Usage

#### 25.1.1. Create a Project

```
$ eng new my-awesome-project
```

This will generate `project.eng` and `src/main.eng`. The `project.eng` is the project's configuration and metadata program that is responsible for everything from building your project, testing, packaging and any other configurations needed.

```eng
# my-awesome-project Project Configuration

import project: eng.project;

project.id = "my_awesome_project";
project.name = "My Awesome Project";
project.version = "1.0.0";
project.description = "A sample Engenide project";
project.author = "Anstro Pleuton";
project.license = "MIT";

let hello_world = project.add_executable("hello_world");
hello_world.sources = ["src/main.eng"];
hello_world.destination = "build"; # Default: "build"
hello_world.standard = "eng-25"; # Default: "latest"
hello_world.entry = "main()"; # Default: "main()"

project.default_run_target = hello_world;
```

This will also generate the main Engenide file containing the entry point (configurable with `project.eng`):

```eng
# Hello World - Engenide

import io: eng.std.io;

fn main() {
	io.println("Hello, World!");
};
```

#### 25.1.2. Build the project

1. Using compiler:

```
$ eng compile
$ eng run # or eng run hello_world or ./build/hello_world
```

2. Using interpreter:

```
$ eng interpret # or eng interpret hello_world
```

3. Sharing bytecode:

In source machine:
```
$ eng process # Generates build/hello_world.bc
```

In target machine
```
$ eng assemble hello_world.bc -o hello_world # Compile bytecode to native
$ eng evaluate hello_world.bc # Interpret bytecode directly
```

#### 25.1.3. Use toolchain without a Project

1. Using compiler:

```
$ eng compile main.eng -o hello_world
```

2. Using interpreter:

```
$ eng interpret main.eng
```

1. Sharing bytecode:

```
$ eng process main.eng -o hello_world.bc # Generates hello_world.bc
$ eng assemble hello_world.bc -o hello_world # Compile bytecode to native
$ eng evaluate hello_world.bc # Interpret bytecode directly
```

### 25.2. Project Configuration

The `project.eng` file is the main and only configuration file for an Engenide project. It is a full Engenide program that uses the `eng.project` module to define the project structure, build targets, dependencies, and other configurations.

Note: The `project.eng` file is executed at build time, so it can include any valid Engenide code. The entire language is available for use in the `project.eng` file, including I/O. Use with care or break all CI/CD pipelines!

#### 25.2.1. Project Metadata

Project metadata includes information about the project such as name, version, description, author, license, and other relevant details.

`project.eng`:
```eng
import project: eng.project;

project.name = "My Awesome Project";
```

#### 25.2.2. Build Targets

Build targets define the output artifacts of the project, such as executables, libraries, or modules. Each target can have its own source files, dependencies, build options, and output settings.

`project.eng`:
```eng
let my_executable = project.add_executable("my_executable");
my_executable.sources = ["src/main.eng", "src/utils.eng"];
my_executable.destination = "build/bin";
my_executable.standard = "eng-25";
my_executable.entry = "main()";
```

#### 25.2.3. Dependencies

Dependencies can be added to the project to include external libraries or modules.

```eng
let some_library = project.add_dependency("some_library", "1.2.3"); # Fetches from https://packages.engenide.org/archive/some_library/1.2.3
my_executable.add_dependency(some_library);
```

Fetching from third-party repositories:

```eng
let some_third_party_lib = project.add_net_dependency("some_third_party_lib", "https://thirdparty.repo.com/some_third_party_lib/1.0.0.zip"); # Or path
```

Git projects are also supported:

```eng
let git_lib = project.add_get_dependency("git_lib", .commit = "a3f9c2e", "https://github.com/user/repo.git"); # Uses commit hash or branch name or tag name
```

Adding dependency from local path:

```eng
let local_lib = project.add_local_dependency("local_lib", "./libs/local_lib.zip"); # Relative path or shell path allowed (~/projects/local_lib/build/local_lib.zip)
```

Note for custom dependency types: Path/zip must contain a valid Engenide project with `project.eng` file.

#### 25.2.4. Configuring Dependencies

Dependencies can be expose certain configuration options to the consumers. These options can be set in the `project.eng` file of the consumer project.

Dependency `project.eng` (some_library):
```end
export fn configure(feature_xyz: bool = false) {
    if feature_xyz {
        # ... Enable feature_xyz
    };
};
```

Consumer `project.eng`:
```eng
let some_library = project.add_dependency("some_library", "1.2.3");
some_library.configure(.feature_xyz = true);
```

#### 25.2.5. Packaging and Publishing

To publish a project, the project must be packaged first.

```
$ eng package # Generates build/my_awesome_project-1.0.0.zip with all necessary files
$ eng publish # Publishes to Engenide Package Repository (requires registration and authentication)
```

Warning: All the source files will be included in the package by default. Proprietary code are prohibited from being published to official Engenide Package Repository.

Note: The official Engenide Package Repository is reserved for already-popular open-source projects. For other projects, using a custom package repository is recommended and encouraged.

#### 25.2.6. Custom Repository

Setting up and using a custom package repository is straightforward.

1. In remote server:

```
$ eng repository setup # Sets up a new package repository, generating necessary files and configurations (such as repository.eng and archive directory)
```

2. Publisher `project.eng` (some_library):

```eng
project.publish_repository = eng.project.repository("https://my.custom.repo.com"); # Must point to path containing a valid repository.eng
```

3. Publishing package to custom repository:

```
$ eng publish # Publishes to https://my.custom.repo.com
```

4. Consumer `project.eng`:

```eng
let some_library = project.add_net_dependency("some_library", "https://my.custom.repo.com/some_library/1.0.0.zip");
```

#### 25.2.7. Language Presets

Engenide supports language presets to customize the language features and behaviors. Presets can be used to enable or disable specific features, set default behaviors, and configure language settings. It is helpful for teams to maintain consistent coding styles and practices across the project.

```eng
project.preset = eng.project.presets.strict; # Enables strict mode with additional checks and restrictions (NASA-grade safety)
```

Other presets include:
- `eng.project.presets.express` - Default preset with all features enabled.
- `eng.project.presets.strict` - Strict preset with maximum safety checks and restrictions.
- `eng.project.presets.balanced` - Balanced preset with a mix of safety and flexibility.

Custom presets can also be defined by creating a preset with specific features and behaviors.

```eng
let my_custom_preset = eng.project.preset(
    .compile_time_side_effects = false, # Disallow side-effects during compile-time evaluation
    .implicit_type_conversions = false, # Disallow implicit type conversions
    .operator_overloading .= builtin_only # Allow only built-in operator overloading (no custom operators)
);
```

Or changes can be made to existing presets.

```eng
let my_strict_preset = eng.project.presets.strict;
my_strict_preset.implicit_type_conversions = true; # Allow implicit type conversions while keeping other strict mode benefits
```

Using custom preset:

```eng
project.preset = my_custom_preset;
```

#### 25.2.8. Presets as Language Constructs

Presets can be used within the code itself selectively to enable or disable certain features in specific scopes. The `policy` keyword is used to apply a preset to a specific block of code.

```eng
policy eng.project.presets.strict {
    fn safe_function() {
        # Strict mode features enabled here
        let x: int = policy (eng.project.presets.express) 10 + 20.5; # Implicit conversion allowed here
    };
};
```

Or can be applied globally for the entire file by defining at the top of the file.

```eng
policy eng.project.presets.strict;

fn main() {
    # Entire file is under strict mode
};
```

## 26. Plugin System

Engenide supports a plugin system that allows extending the language capabilities by adding custom plugins. Plugins can be used to add new features, modify existing behaviors, or integrate with external tools, libraries or other languages.

Plugins access the internals of the Engenide Engine through a well-defined API.

Plugins are not part of Engenide. All plugins are third-party and maintained separately by their respective authors.

Plugins are useful where macros are insufficient, such as adding new semantics or new types of interoperability.

Plugin system is under development and will be documented in future versions.

### 26.1. Example Plugins

1. **Java Interop Plugin** - A plugin that allows interoperability with JVM code, enabling calling Java methods and using Java classes from Engenide.

```eng
@java_import
class MyJavaClass {
    let myJavaField: int;
    fn myJavaMethod(param: int) -> int;
};

fn main() {
    let java_instance = comply "Java" MyJavaClass();
    let result = comply "Java" java_instance.myJavaMethod(42);
    io.println("Result from Java: ${result}");
};
```

```java
public class MyJavaClass {
    public int myJavaField;

    public int myJavaMethod(int param) {
        return param * myJavaField;
    }
}
```

Or, the opposite way:

```java
public class Main {
    public static void main(String[] args) {
        my_eng_class engInstance = new my_eng_class();
        int result = engInstance.my_eng_method(42);
        System.out.println("Result from Engenide: " + result);
    }
}
```

```eng
@java_export
class my_eng_class {
    let my_eng_field: int;

    fn my_eng_method(param: int) -> int {
        return param + my_eng_field;
    };
};
```

2. **Borrow Checker Plugin** - A plugin that implements a borrow checker similar to Rust's borrow checker to ensure memory safety at compile-time.

```eng
fn borrow_string(s: &mut string) {
    s += " from borrow checker!";
};

fn own_string(s: string) {
    io.println(s);
};

fn main() {
    let mut my_string = string("Hello, World!");

    {
        let ref1 = &my_string; # Immutable borrow
        io.println(ref1);
    };

    let ref2 = &mut my_string; # Mutable borrow
    ref2 += " Welcome to Engenide!";
    io.println(ref2);

    drop ref2; # End mutable borrow

    borrow_string(&mut my_string); # Valid mutable borrow
    own_string(my_string); # Ownership moved
};
```

## 27. Appendix A - List of Keywords

1. `acq` - Acquiring memory ordering for atomic operations.
2. `alive` - Checks if a thread is running.
3. `alloc` - Allocates a memory block on the heap.
4. `ar` - Acquiring and releasing memory ordering for atomic operations.
5. `as` - Converts a value to a different type; Obtains a value of a variant type.
6. `async` - Declares a function as a coroutine.
7. `atomic` - Declares an atomic variable for lock-free shared memory access.
8. `auto` - Infers the type of a variable or return type of a function; Defines a weakly constrained concept.
9. `await` - Pauses execution of a coroutine until the awaited coroutine terminates.
10. `base` - Refers to the base class instance in inheritance; Refers to a variant value in multiple inheritance.
11. `be` - Resolves a value in a `with`-`be` block.
12. `break` - Exits from a loop or switch statement.
13. `case` - Defines a case in a switch statement; Substitutes the value in a matching expression.
14. `cast` - Defines an implicit or explicit casting function.
15. `cata` - Catalyzes a grandbase class to facilitate base classes without duplication.
16. `catch` - Defines an exception handler block.
17. `cease` - Cancels a coroutine; Cancels a thread.
18. `class` - Declares a class type.
19. `comply` - Complies to a `require` requirement.
20. `concept` - Declares a concept for generics constraints.
21. `cont` - Continues to the next iteration of a loop.
22. `copy` - Explicitly copies a value; Defines a copy constructor for a class.
23. `ctor` - Defines a constructor for a class.
24. `dealloc` - Deallocates a memory block from the heap.
25. `default` - Defines a default value for a type; Specifies the default value of an enum type.
26. `defer` - Defers execution of a block until the surrounding scope exits.
27. `detach` - Detaches a thread, allowing it to run independently.
28. `do` - Starts a do-while loop.
29. `dtor` - Defines a destructor for a class.
30. `dynamic` - Declares an entity as non-compile-time evaluable.
31. `ego` - Refers to the current function.
32. `else` - Defines the else block in an `if`-`else`, `while`-`else` or `for`-`else` statement; Defines a default case in a switch statement.
33. `emit` - Emits a value in a generator expression.
34. `enum` - Declares an enumeration type.
35. `export` - Exports a function, class or variable or namespace.
36. `first` - Defines a generator for first value in an enumerator member.
37. `fn` - Declares a function.
38. `for` - Starts a for loop.
39. `fork` - Creates a thread to run a function parallelly.
40. `friend` - Declares a friend function or class in a class or namespace.
41. `get` - Defines a getter for a property.
42. `if` - Starts an if statement.
43. `immut` - Declares a mutable member in a class that can only be mutated from immutable instance.
44. `import` - Imports a function, class, variable or namespace.
45. `impure` - Declares a function as fake pure.
46. `in` - Checks if a value is in a collection; Iterates over elements in a for loop.
47. `into` - Defines an explicit-only casting function.
48. `is` - Checks if a value is of a specific type.
49. `join` - Joins a thread, waiting for it to terminate.
50. `let` - Declares a variable, constant or a member.
51. `lit` - Declares a literal typing function.
52. `lock` - Locks a mutex for thread synchronization.
53. `loft` - Refers to the base class type in inheritance; Refers to a variant type in multiple inheritance.
54. `macro` - Declares a macro.
55. `match` - Starts a match expression.
56. `move` - Moves a value, transferring ownership; Defines a move constructor for a class.
57. `mut` - Declares a mutable member in a class.
58. `mutex` - Declares a mutex for thread synchronization.
59. `next` - Defines a generator for next value in an enumerator member.
60. `ns` - Declares a namespace.
61. `once` - Defines a first-iteration block in a `for` or `while` loop.
62. `onward` - Defines a subsequent-iteration block in a `for` or `while` loop.
63. `op` - Declares an operator overload.
64. `orid` - Overrides a virtual member function in a derived class.
65. `pers` - Defines a personal-access (namespace-visible) member in a class.
66. `policy` - Applies a language preset to a block. expression or entire file.
67. `priv` - Defines a private-access (class-visible) member in a class.
68. `probe` - Probes if a coroutine can be awaited without blocking.
69. `prop` - Declares a property type.
70. `prot` - Defines a protected-access (class and derived-visible) member in a class.
71. `pub` - Defines a public-access (world-visible) member in a class.
72. `pure` - Declares a function as side-effect-free.
73. `realloc` - Reallocates a memory block on the heap.
74. `rel` - Releasing memory ordering for atomic operations.
75. `require` - Declares a requirement for `comply` statement.
76. `retain` - Defines a static variable; Defines a static function defined in a class.
77. `return` - Returns a value from a function.
78. `rlx` - Relaxed memory ordering for atomic operations.
79. `self` - Refers to the current class type in a class definition.
80. `set` - Defines a setter for a property.
81. `seq` - Sequentially consistent memory ordering for atomic operations.
82. `sizeof` - Obtains the size of a type in bytes.
83. `static` - Declares a compile-time constant or function.
84. `swap` - Swaps two values; Defines a swap constructor for a class.
85. `switch` - Starts a switch statement.
86. `this` - Refers to the current class instance in a class definition.
87. `throw` - Throws an exception.
88. `try` - Starts a try block for exception handling.
89. `undef` - Undefines an entity.
90. `unlock` - Unlocks a mutex for other threads to access.
91. `virt` - Defines a virtual member function in a class.
92. `where` - Defines arbitrary constraints in a concept definition.
93. `while` - Starts a while loop.
94. `with` - Starts a `with`-`be` block.
95. `yield` - Pauses execution of a coroutine and yields a value.

## 28. Appendix B - List of Built-in Operators

These operators are ranked from highest precedence to lowest precedence (higher number = lower precedence).

1. `*x`, `/x`
2. `+x`, `-x`
3. `!x`, `~x`
4. `x!`, `x%`, `x%%`, `x%%%`
5. `++x`, `--x`
6. `x++`, `x--`
7. `x << y`, `x >> y`
8. `x <<< y`, `x >>> y`
9. `x <& y`, `x <| y`, `x >& y`, `x >| y`
10. `x ^ y`
11. `x & y`, `x | y`
12. `x <? y`, `x >? y`, `x <=? y`, `x >=? y`
13. `x ** y`
14. `x // y`
15. `x % y`, `x %% y`
16. `x * y`, `x / y`
17. `x + y`, `x - y`
18. `|x|`
19. `x[ y ]`
20. `x == y`, `x != y`
21. `x < y`, `x > y`, `x <= y`, `x >= y`
22. `x && y`, `x || y`
23. `x -> y`, `x |> y`
24. `x = y`

Variants of the operators also exist for different purposes.
1. All the binary operators also has their shorthand assignment counterparts by adding a `=` suffix to the operator symbol, e.g., `x += y` (addition_assignment). In case of conflicts (`x <= y`), a double `=` is used instead (e.g., `x <=== y` for less_than_equals_assignment).
2. All the operators also has their nullable counterparts by adding a `?` suffix (or prefix for assignments) to the operator symbol, e.g., `x +? y` (nullable_addition), `x ==? y` (nullable_equality), `x ?= y` (nullable_assignment), etc.
3. All the operators also has their array-element-wise counterparts enclosing the operator symbol with `[` and `]`, or `[` and `>`, or `<` and `]`, e.g., `x [+] y` (array_addition), `x <==] y` (array_equality_short), `x [||?> y` (array_nullable_logical_and_long), etc.

Operator descriptions:
1. `*x` - Unary prefix `*` operator (`multiplicative_identity`; `dereference`) that:
   - Dereferences a pointer to obtain the value it points to.
   - Identity operator for numeric types (no-op).
2. `/x` - Unary prefix `/` operator (`reciprocal`) that:
   - Computes the reciprocal of a numeric value.
3. `+x` - Unary prefix `+` operator (`additive_identity`) that:
   - Identity operator for numeric types (no-op).
4. `-x` - Unary prefix `-` operator (`negation`) that:
   - Negates a numeric value.
5. `!x` - Unary prefix `!` operator (`logical_not`) that:
   - Performs logical NOT operation on a boolean value.
6. `~x` - Unary prefix `~` operator (`bitwise_not`) that:
   - Performs bitwise NOT operation on an integer value.
7. `x!` - Unary suffix `!` operator (`factorial`) that:
   - Computes the factorial of an unsigned integer value.
8. `x%` - Unary suffix `%` operator (`percent`) that:
   - Computes the percentage value of a numeric value (divides by 100).
9. `x%%` - Unary suffix `%%` operator (`permille`) that:
    - Computes the permille value of a numeric value (divides by 1000).
10. `x%%%` - Unary suffix `%%%` operator (`permyriad`) that:
     - Computes the permyriad value of a numeric value (divides by 10000).
11. `++x` - Unary prefix `++` operator (`pre_increment`) that:
   - Increments a numeric value by 1 and returns the incremented value.
12. `--x` - Unary prefix `--` operator (`pre_decrement`) that:
    - Decrements a numeric value by 1 and returns the decremented value.
13. `x++` - Unary suffix `++` operator (`post_increment`) that:
    - Returns the current value and then increments it by 1.
14. `x--` - Unary suffix `--` operator (`post_decrement`) that:
    - Returns the current value and then decrements it by 1.
15. `x << y` - Binary infix `<<` operator (`left_shift`) that:
    - Shifts the bits of `x` to the left by `y` positions.
16. `x >> y` - Binary infix `>>` operator (`right_shift`) that:
    - Shifts the bits of `x` to the right by `y` positions.
17. `x <<< y` - Binary infix `<<<` operator (`left_rotate`) that:
    - Rotates the bits of `x` to the left by `y` positions.
18. `x >>> y` - Binary infix `>>>` operator (`right_rotate`) that:
    - Rotates the bits of `x` to the right by `y` positions.
19. `x <& y` - Binary infix `<&` operator (`left_shift_zero`) that:
    - Shifts the bits of `x` to the left by `y` positions, filling with zeros.
20. `x <| y` - Binary infix `<|` operator (`left_shift_one`) that:
    - Shifts the bits of `x` to the left by `y` positions, filling with ones.
21. `x >& y` - Binary infix `>&` operator (`right_shift_zero`) that:
    - Shifts the bits of `x` to the right by `y` positions, filling with zeros.
22. `x >| y` - Binary infix `>|` operator (`right_shift_one`) that:
    - Shifts the bits of `x` to the right by `y` positions, filling with ones.
23. `x ^ y` - Binary infix `^` operator (`bitwise_xor`) that:
    - Performs bitwise XOR operation between `x` and `y`.
24. `x & y` - Binary infix `&` operator (`bitwise_and`) that:
    - Performs bitwise AND operation between `x` and `y`.
25. `x | y` - Binary infix `|` operator (`bitwise_or`) that:
    - Performs bitwise OR operation between `x` and `y`.
26. `x <? y` - Binary infix `<?` operator (`minimum`) that:
    - Returns the minimum of `x` and `y`.
27. `x >? y` - Binary infix `>?` operator (`maximum`) that:
    - Returns the maximum of `x` and `y`.
28. `x <=? y` - Binary infix `<=?` operator (`minimum_equals`) that:
    - Returns the minimum of `x` and `y`, or `x` if they are equal.
29. `x >=? y` - Binary infix `>=?` operator (`maximum_equals`) that:
    - Returns the maximum of `x` and `y`, or `x` if they are equal.
30. `x ** y` - Binary infix `**` operator (`exponentiation`) that:
    - Raises `x` to the power of `y`.
31. `x // y` - Binary infix `//` operator (`flooring_division`) that:
    - Performs flooring division of `x` by `y`.
32. `x % y` - Binary infix `%` operator (`modulus`) that:
    - Computes the modulus of `x` by `y`.
33. `x %% y` - Binary infix `%%` operator (`wrapping_modulus`) that:
    - Computes the wrapping modulus of `x` by `y`.
34. `x * y` - Binary infix `*` operator (`multiplication`) that:
    - Multiplies `x` by `y`.
35. `x / y` - Binary infix `/` operator (`division`) that:
    - Divides `x` by `y`.
36. `x + y` - Binary infix `+` operator (`addition`) that:
    - Adds `x` and `y`.
37. `x - y` - Binary infix `-` operator (`subtraction`) that:
    - Subtracts `y` from `x`.
38. `|x|` - Multi-part operator (`absolute`) that:
    - Computes the absolute value of `x`.
39. `x[ y ]` - Multi-part operator (`indexing`) that:
    - Accesses the element at index `y` in collection `x`.
40. `x == y` - Binary infix `==` operator (`equality`) that:
    - Checks if `x` is equal to `y`.
41. `x != y` - Binary infix `!=` operator (`inequality`) that:
    - Checks if `x` is not equal to `y`.
42. `x < y` - Binary infix `<` operator (`less_than`) that:
    - Checks if `x` is less than `y`.
43. `x > y` - Binary infix `>` operator (`more_than`) that:
    - Checks if `x` is greater than `y`.
44. `x <= y` - Binary infix `<=` operator (`less_than_equals`) that:
    - Checks if `x` is less than or equal to `y`.
45. `x >= y` - Binary infix `>=` operator (`more_than_equals`) that:
    - Checks if `x` is greater than or equal to `y`.
46. `x && y` - Binary infix `&&` operator (`logical_and`) that:
    - Performs logical AND operation between `x` and `y`.
47. `x || y` - Binary infix `||` operator (`logical_or`) that:
    - Performs logical OR operation between `x` and `y`.
48. `x -> y` - Binary infix `->` operator (`pipeline`) that:
    - Performs array pipeline operation, passing each element of array `x` to function `y`.
49. `x |> y` - Binary infix `|>` operator (`placeholder_pipeline`) that:
    - Performs placeholder pipeline operation, passing `x` to function `y` where `$` is used as placeholder.
50. `x = y` - Binary infix `=` operator (`assignment`) that:
    - Assigns the value of `y` to `x`.

## 29. Appendix C - List of Syntax Markers

1. `# comment` - Defines a single-line comment.
2. `#{ multi-line comment }#` - Defines a multi-line comment.
3. `$` - Used as a placeholder in placeholder pipeline operator; Used as parameter placeholder in function binding.
4. `$index.name` - Used as indexed parameter renaming placeholder in function binding.
5. `$index` - Used as index placeholder in array pipeline operator; Used as parameter index placeholder in function binding.
6. `$name` - Used as a parameter renaming placeholder in function binding.
7. `(.parameter = value)` - Used to specify named parameters in function calls.
8. `(.parametervalue)` - Same as `(.parametervalue = parametervalue)`.
9. `(name1: type1, name2: type2)` - Defines a named tuple type; Defines named parameters in function type.
10. `(parentheses)` - Parenthesized expression to group expressions.
11. `(tuple_item1, tuple_item2)` - Defines a tuple literal.
12. `(type1, type2)` - Defines a tuple type; Defines parameter list in function type.
13. `...pack` - Collects remaining variadic parameters into an array.
14. `:<generics>` - Specifies generic type arguments for generic types or functions.
15. `@attribute` - Applies an attribute to an entity.
16. `[ array ]` - Defines an array literal or array type.
17. `` `backtick identifier` `` - Defines a word using the enclosed prose as the identifier.
18. `entity .= member` - Same as `entity = entity.member`.
19. `entity .=? member` - Same as `if (entity) entity .= member`.
20. `entity .?= member` - Same as `entity = entity.?member`.
21. `entity .?=? member` - Same as `if (entity) entity .?= member`.
22. `entity.member` - Accesses member of an entity.
23. `entity: parent` - Specifies base class of a class; Annotates type of a an expression.
24. `exception !! default_value` - Provides a default value if an exception occurs.
25. `exception_to_null?!` - Converts an exception to null if an exception occurs.
26. `fn -> return_type` - Specifies the return type of a function.
27. `fn => expression` - Defines a single-expression function.
28. `function(parameters)` - Calls a function with parameters.
29. `function:(binding_values)` - Binds parameters to a function, returning a callable function.
30. `item1, item2` - Comma-separated list of items (e.g., in function parameters, array literals, tuple literals, etc.).
31. `null ?? default_value` - Provides a default value if the value is null.
32. `null_to_exception!?` - Converts a null value to an exception if the value is null.
33. `range_start:range_end:step` - Defines a range with a specific step value.
34. `range_start:range_end` - Defines a range with default step value of 1.
35. `side <= channeling` - Defines a function that side-channels (branches) a value to another function.
36. `statement;` - Terminates a statement.
37. `type1 | type2` - Defines a variant type.
38. `unpack...` - Unpacks a static array or tuple into individual list of comma-separated values.
39. `{ compound }` - Defines a block of code or a composite literal.
40. `{ map_key: map_value }` - Defines a map literal.

