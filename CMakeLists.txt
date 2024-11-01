cmake_minimum_required(VERSION 3.29)
project(TinyLittleURLUtils C)

set(CMAKE_C_STANDARD 23)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

include(CTest)
enable_testing()

add_library(tiny_url_encoder_lib src/tiny_url_encoder.c src/tiny_url_encoder.h)

add_executable(assert_tiny_url_encoder test/assert_tiny_url_encoder.c)
target_link_libraries(assert_tiny_url_encoder tiny_url_encoder_lib)

add_test(test_tiny_url_encoder assert_tiny_url_encoder)
