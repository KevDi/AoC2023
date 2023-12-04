cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source")
endif()

project("Day04" VERSION 1.0.0 LANGUAGES CXX)

add_library(day04 game.h game.cpp)
add_library("AOC2023::Day04" ALIAS "day04")

target_compile_features(day04 PUBLIC cxx_std_17)

if(MSVC)
    target_compile_options(day04 PRIVATE /W4 /WX)
else()
    target_compile_options(day04 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_executable(day04_TEST day04_test.cpp day04_test_runner.cpp)

find_package(GTest REQUIRED)

target_link_libraries(day04_TEST PRIVATE GTest::gmock AOC2023::Day04)

# add_custom_command(
#     TARGET day02_TEST POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_CURRENT_SOURCE_DIR}/resources
#             ${CMAKE_BINARY_DIR}/bin/resources
# )

include(GoogleTest)
gtest_discover_tests(day04_TEST WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(day04_MAIN day04.cpp)

target_link_libraries(day04_MAIN PRIVATE AOC2023::Day04)

add_custom_command(
    TARGET day04_MAIN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/bin/resources
)