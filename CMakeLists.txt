cmake_minimum_required(VERSION 4.0)

project(engenide
    LANGUAGES CXX
    VERSION 0.1.0
    DESCRIPTION "Engenide is a general-purpose systems language between C++ and Rust."
    HOMEPAGE_URL "https://github.com/anstropleuton/engenide.git"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_CLANG_TIDY "Run clang-tidy during build" OFF)

if (ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
  set(CLANG_TIDY_CMD "${CLANG_TIDY_EXE}")
  if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    list(APPEND CLANG_TIDY_CMD
      "--extra-arg=-Xclang" "--extra-arg=-fcxx-exceptions"
      "--extra-arg=-Xclang" "--extra-arg=-fexceptions")
  endif ()
endif ()

find_package(ICU REQUIRED COMPONENTS uc)
find_package(CLI11 CONFIG REQUIRED)

add_subdirectory(source)
