cmake_minimum_required (VERSION 2.8.11)

project (aoc1)

add_compile_definitions(OPENCV_VERSION=${OpenCV_VERSION})
add_compile_definitions(AOC1DIR="${CMAKE_CURRENT_LIST_DIR}")

add_executable (aoc1 main.cpp)
