cmake_minimum_required(VERSION 3.22)

project(MANA)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(Tools)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_MODULE_PATH}")

add_clang_format_target()

add_executable(MANA main.cpp)

add_clang_tidy_to_target(MANA)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(memory_pool)
add_subdirectory(geek_bang_cpp)