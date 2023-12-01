cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source")
endif()

project("Day01" VERSION 1.0.0 LANGUAGES CXX)

if(MSVC) 
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/day01)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/day01)
endif()

add_executable(day01 day01.cpp)

target_compile_features(day01 PUBLIC cxx_std_17)

if(MSVC)
    target_compile_options(day01 PRIVATE /W4 /WX)
else()
    target_compile_options(day01 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()