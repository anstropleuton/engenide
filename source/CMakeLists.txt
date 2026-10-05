configure_file(
    ../include/engenide/eng_config.hpp.in
    "${CMAKE_BINARY_DIR}/generated/eng_config.hpp"
)

add_library(engenide
    "${CMAKE_BINARY_DIR}/generated/eng_config.hpp"
    ../include/engenide/source_code.hpp
    utils.hpp
    plat_utils.hpp
    plat_utils.cpp
    source_code.cpp
)

target_compile_features(engenide PUBLIC cxx_std_23)

target_include_directories(engenide PUBLIC ../include "${CMAKE_BINARY_DIR}/generated")

target_link_libraries(engenide PRIVATE ICU::uc)

add_executable(eng main.cpp)

target_link_libraries(eng PRIVATE engenide CLI11::CLI11)
