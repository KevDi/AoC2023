cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source")
endif()

project("Day03" VERSION 1.0.0 LANGUAGES CXX)

add_library(day03 engine.h engine.cpp)
add_library("AOC2023::Day03" ALIAS "day03")

target_compile_features(day03 PUBLIC cxx_std_17)

if(MSVC)
    target_compile_options(day03 PRIVATE /W4 /WX)
else()
    target_compile_options(day03 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_executable(day03_TEST day03_test.cpp day03_test_runner.cpp)

find_package(GTest REQUIRED)

target_link_libraries(day03_TEST PRIVATE GTest::gmock AOC2023::Day03)

# add_custom_command(
#     TARGET day02_TEST POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_CURRENT_SOURCE_DIR}/resources
#             ${CMAKE_BINARY_DIR}/bin/resources
# )

include(GoogleTest)
gtest_discover_tests(day03_TEST WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(day03_MAIN day03.cpp)

target_link_libraries(day03_MAIN PRIVATE AOC2023::Day03)

add_custom_command(
    TARGET day03_MAIN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/bin/resources
)