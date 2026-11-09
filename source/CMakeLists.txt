configure_file(
    ../include/engenide/eng_config.hpp.in
    "${CMAKE_BINARY_DIR}/generated/eng_config.hpp"
)

add_library(engenide
    lexer.cpp
    plat_utils.cpp
    source_code.cpp
)

target_compile_features(engenide PUBLIC cxx_std_23)

target_compile_options(engenide PRIVATE
    $<$<CXX_COMPILER_FRONTEND_VARIANT:GNU>:-Wall -Wextra -Wpedantic -Wno-braced-scalar-init -Wno-missing-designated-field-initializers>
    $<$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>:/W4>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>>:-Wno-braced-scalar-init -Wno-missing-designated-field-initializers>
    $<$<CXX_COMPILER_ID:MSVC>:/permissive->
)

target_include_directories(engenide PUBLIC ../include "${CMAKE_BINARY_DIR}/generated")

target_link_libraries(engenide PRIVATE ICU::uc)

add_executable(eng main.cpp)

target_compile_options(eng PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
)

target_link_libraries(eng PRIVATE engenide CLI11::CLI11)

if (ENABLE_CLANG_TIDY)
    set_target_properties(engenide eng PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_CMD}")
endif ()
