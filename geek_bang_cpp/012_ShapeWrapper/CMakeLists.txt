cmake_minimum_required(VERSION 3.22)

project(ShapeWrapper VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(ShapeWrapper shape_wrapper.cc)
target_include_directories(ShapeWrapper PRIVATE ../common)