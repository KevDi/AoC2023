cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source")
endif()

project("Day15" VERSION 1.0.0 LANGUAGES CXX)

add_executable(day15_MAIN day15.cpp)

add_custom_command(
    TARGET day15_MAIN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/resources
            ${CMAKE_BINARY_DIR}/bin/resources
)

