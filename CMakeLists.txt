cmake_minimum_required(VERSION 3.22)

project(MANA)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(Tools)

add_executable(MANA main.cpp)

add_clang_tidy_to_target(MANA)