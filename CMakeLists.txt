cmake_minimum_required(VERSION 4.0)

project(engenide
    LANGUAGES CXX
    VERSION 0.1.0
    DESCRIPTION "Engenide is a general-purpose systems language between C++ and Rust."
    HOMEPAGE_URL "https://github.com/anstropleuton/engenide.git"
)

find_package(ICU REQUIRED COMPONENTS uc)

add_subdirectory(source)
