# This example is from https://github.com/xiaoweiChen/CMake-Cookbook/blob/master/content/chapter4/4.1-chinese.md

# Set minimum CMake version
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# Project name and language
project(ctest-example LANGUAGES CXX)

# Required C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(PythonInterp REQUIRED)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)

# Example library
add_library(sum_integers sum_integers.cpp)

# Main code
add_executable(sum_up main.cpp)
target_link_libraries(sum_up sum_integers)

option(ENABLE_UNIT_TESTS "Enalbe unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if (ENABLE_UNIT_TESTS)
  # The below unit tests things are from https://github.com/xiaoweiChen/CMake-Cookbook/blob/master/content/chapter4/4.3-chinese.md
  # But not the very same, the example above is using FetchContent_GetProperties(googletest) and other stuff to retry if fetch content failed.
  # If we want to see error googletest log, we need to add additional arguments while executing `ctest`
  # Because of this, it's not necessary to combine ctest and google test if our tests are only organized with googletest
  include(FetchContent)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
  )
  FetchContent_MakeAvailable(googletest)

  add_library(GTest::GTest INTERFACE IMPORTED)
  target_link_libraries(GTest::GTest INTERFACE gtest_main)

  add_executable(gg_test "")
  target_sources(gg_test PRIVATE ggtest.cpp)
  target_link_libraries(gg_test PRIVATE sum_integers GTest::GTest)

  enable_testing()
  add_test(
    NAME google_test
    COMMAND $<TARGET_FILE:gg_test>)
endif()

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
