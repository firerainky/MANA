# This example is from https://github.com/xiaoweiChen/CMake-Cookbook/blob/master/content/chapter4/4.1-chinese.md

# Set minimum CMake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Project name and language
project(ctest-example LANGUAGES CXX)

# Required C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PythonInterp REQUIRED)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)

# Example library
add_library(sum_integers sum_integers.cpp)

# Main code
add_executable(sum_up main.cpp)
target_link_libraries(sum_up sum_integers)

# Testing binary
add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test sum_integers)

# Enable testing functionality
enable_testing()

# Define tests
add_test(
  NAME bash_test
  COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh $<TARGET_FILE:sum_up>
)

add_test(
  NAME cpp_test
  COMMAND $<TARGET_FILE:cpp_test>
)

add_test(
  NAME python_test/long
  COMMAND ${PYTHON_EXECUTABLE} test.py --executable $<TARGET_FILE:sum_up>
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_test(
  NAME python_test/short
  COMMAND ${PYTHON_EXECUTABLE} test.py --short --executable $<TARGET_FILE:sum_up>
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
