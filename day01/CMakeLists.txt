cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source")
endif()

project("Day01" VERSION 1.0.0 LANGUAGES CXX)

add_library(day01 day01.cpp)
add_library("AOC2023::Day01" ALIAS "day01")

target_compile_features(day01 PUBLIC cxx_std_17)

if(MSVC)
    target_compile_options(day01 PRIVATE /W4 /WX)
else()
    target_compile_options(day01 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_executable(day01_TEST day01_test.cpp day01_test_runner.cpp)

find_package(GTest REQUIRED)

target_link_libraries(day01_TEST PRIVATE GTest::gmock AOC2023::Day01)

add_custom_command(
    TARGET day01_TEST POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/bin/resources
)

include(GoogleTest)
gtest_discover_tests(day01_TEST)

add_executable(day01_MAIN day01_main.cpp)

target_link_libraries(day01_MAIN PRIVATE AOC2023::Day01)

add_custom_command(
    TARGET day01_MAIN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/bin/resources
)