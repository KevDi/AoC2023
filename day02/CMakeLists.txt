cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source")
endif()

project("2" VERSION 1.0.0 LANGUAGES CXX)

add_library(day02 game.h game.cpp)
add_library("AOC2023::Day02" ALIAS "day02")

target_compile_features(day02 PUBLIC cxx_std_17)

if(MSVC)
    target_compile_options(day02 PRIVATE /W4 /WX)
else()
    target_compile_options(day02 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_executable(day02_TEST day02_test.cpp day02_test_runner.cpp)

find_package(GTest REQUIRED)

target_link_libraries(day02_TEST PRIVATE GTest::gmock AOC2023::Day02)

# add_custom_command(
#     TARGET day02_TEST POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_CURRENT_SOURCE_DIR}/resources
#             ${CMAKE_BINARY_DIR}/bin/resources
# )

include(GoogleTest)
gtest_discover_tests(day02_TEST WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(day02_MAIN day02.cpp)

target_link_libraries(day02_MAIN PRIVATE AOC2023::Day02)

add_custom_command(
    TARGET day02_MAIN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/bin/resources
)