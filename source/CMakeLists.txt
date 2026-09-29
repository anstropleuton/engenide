add_library(engenide
    ../include/engenide/source_code.hpp
    source_code.cpp
    eng_utils.hpp
)

target_compile_features(engenide PUBLIC cxx_std_23)

target_include_directories(engenide PUBLIC ../include)

target_link_libraries(engenide PRIVATE ICU::uc)

add_executable(eng
    main.cpp
)

target_link_libraries(eng PRIVATE engenide)
