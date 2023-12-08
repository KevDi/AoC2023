cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source")
endif()

project("Day07" VERSION 1.0.0 LANGUAGES CXX)

add_library(day07 hand.h hand.cpp)
add_library("AOC2023::Day07" ALIAS "day07")

target_compile_features(day07 PUBLIC cxx_std_17)

if(MSVC)
    target_compile_options(day07 PRIVATE /W4 /WX)
else()
    target_compile_options(day07 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_executable(day07_TEST day07_test.cpp day07_test_runner.cpp)

find_package(GTest REQUIRED)

target_link_libraries(day07_TEST PRIVATE GTest::gmock AOC2023::Day07)

# add_custom_command(
#     TARGET day02_TEST POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_CURRENT_SOURCE_DIR}/resources
#             ${CMAKE_BINARY_DIR}/bin/resources
# )

include(GoogleTest)
gtest_discover_tests(day07_TEST WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(day07_MAIN day07.cpp)

target_link_libraries(day07_MAIN PRIVATE AOC2023::Day07)

add_custom_command(
    TARGET day07_MAIN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/bin/resources
)