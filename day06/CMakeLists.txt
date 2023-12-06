cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source")
endif()

project("Day06" VERSION 1.0.0 LANGUAGES CXX)

add_library(day06 race.h race.cpp)
add_library("AOC2023::Day06" ALIAS "day06")

target_compile_features(day06 PUBLIC cxx_std_17)

if(MSVC)
    target_compile_options(day06 PRIVATE /W4 /WX)
else()
    target_compile_options(day06 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_executable(day06_TEST day06_test.cpp day06_test_runner.cpp)

find_package(GTest REQUIRED)

target_link_libraries(day06_TEST PRIVATE GTest::gmock AOC2023::Day06)

# add_custom_command(
#     TARGET day02_TEST POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_CURRENT_SOURCE_DIR}/resources
#             ${CMAKE_BINARY_DIR}/bin/resources
# )

include(GoogleTest)
gtest_discover_tests(day06_TEST WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(day06_MAIN day06.cpp)

target_link_libraries(day06_MAIN PRIVATE AOC2023::Day06)

add_custom_command(
    TARGET day06_MAIN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/bin/resources
)