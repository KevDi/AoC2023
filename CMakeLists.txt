cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source")
endif()

project("AdventOfCode" VERSION 1.0.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC) 
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

option(DAY01 "Build Week 2" OFF)
option(DAY02 "Build Week 3" OFF)
option(DAY03 "Build Week 4" OFF)
option(DAY04 "Build Week 5" OFF)
option(DAY05 "Build Week 6" OFF)
option(DAY06 "Build Week 7" OFF)
option(DAY07 "Build Week 8" OFF)
option(DAY08 "Build Week 9" OFF)
option(DAY09 "Build Week 10" OFF)
option(DAY10 "Build Week 11" OFF)
option(DAY11 "Build Week 12" OFF)
option(DAY12 "Build Week 13" OFF)
option(DAY13 "Build Week 14" OFF)
option(DAY14 "Build Week 15" OFF)
option(DAY15 "Build Week 16" OFF)
option(DAY16 "Build Week 17" OFF)
option(DAY17 "Build Week 18" OFF)
option(DAY18 "Build Week 19" OFF)
option(DAY19 "Build Week 20" OFF)
option(DAY20 "Build Week 21" OFF)
option(DAY21 "Build Week 22" OFF)
option(DAY22 "Build Week 23" OFF)
option(DAY23 "Build Week 24" OFF)
option(DAY24 "Build Week 25" OFF)

include(CTest)
enable_testing()

if(DAY01)
    add_subdirectory(day01)
endif()

if(DAY02)
    add_subdirectory(day02)
endif()

if(DAY03)
    add_subdirectory(day03)
endif()

if(DAY04)
    add_subdirectory(day04)
endif()

if(DAY05)
    add_subdirectory(day05)
endif()

if(DAY06)
    add_subdirectory(day06)
endif()

if(DAY07)
    add_subdirectory(day07)
endif()

if(DAY08)
    add_subdirectory(day08)
endif()

if(DAY09)
    add_subdirectory(day09)
endif()

if(DAY10)
    add_subdirectory(day10)
endif()

if(DAY11)
    add_subdirectory(day11)
endif()

if(DAY12)
    add_subdirectory(day12)
endif()

if(DAY13)
    add_subdirectory(day13)
endif()

if(DAY14)
    add_subdirectory(day14)
endif()

if(DAY15)
    add_subdirectory(day15)
endif()

if(DAY16)
    add_subdirectory(day16)
endif()

if(DAY17)
    add_subdirectory(day17)
endif()

if(DAY18)
    add_subdirectory(day18)
endif()

if(DAY19)
    add_subdirectory(day19)
endif()

if(DAY20)
    add_subdirectory(day20)
endif()

if(DAY21)
    add_subdirectory(day21)
endif()

if(DAY22)
    add_subdirectory(day22)
endif()

if(DAY23)
    add_subdirectory(day23)
endif()

if(DAY24)
    add_subdirectory(day24)
endif()
