cmake_minimum_required(VERSION 3.40)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
  message(
    FATAL_ERROR
      "Prevented in-tree build. Please create a build directory outside of current project and run cmake"
  )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(AOC_2025)

set(CMAKE_CXX_STANDARD 20)

# First build submodules
add_subdirectory("ext/argh")
add_subdirectory("ext/fmt")
add_subdirectory("common")

# Then the riddles
add_subdirectory("day1")
add_subdirectory("day2")
# add_subdirectory("day3") add_subdirectory("day4") add_subdirectory("day5")
# add_subdirectory("day6") add_subdirectory("day7") add_subdirectory("day8")
# add_subdirectory("day9") add_subdirectory("day10")
