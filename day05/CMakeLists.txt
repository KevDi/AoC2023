cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source")
endif()

project("Day05" VERSION 1.0.0 LANGUAGES CXX)

# add_library(day05 almanac.h almanac.cpp)
# add_library("AOC2023::Day05" ALIAS "day05")

# target_compile_features(day05 PUBLIC cxx_std_17)

# if(MSVC)
#     target_compile_options(day05 PRIVATE /W4 /WX)
# else()
#     target_compile_options(day05 PRIVATE -Wall -Wextra -pedantic -Werror)
# endif()

# add_executable(day05_TEST day05_test.cpp day05_test_runner.cpp)

# find_package(GTest REQUIRED)

# target_link_libraries(day05_TEST PRIVATE GTest::gmock AOC2023::Day05)

# # add_custom_command(
# #     TARGET day02_TEST POST_BUILD
# #     COMMAND ${CMAKE_COMMAND} -E copy_directory
# #             ${CMAKE_CURRENT_SOURCE_DIR}/resources
# #             ${CMAKE_BINARY_DIR}/bin/resources
# # )

# include(GoogleTest)
# gtest_discover_tests(day05_TEST WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(day05_MAIN day05.cpp)

#target_link_libraries(day05_MAIN PRIVATE AOC2023::Day05)

add_custom_command(
    TARGET day05_MAIN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/bin/resources
)