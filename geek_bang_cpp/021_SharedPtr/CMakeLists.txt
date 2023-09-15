cmake_minimum_required(VERSION 3.22)

project(SharedPtr VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(SharedPtr shared_ptr.cc)
target_include_directories(SharedPtr PRIVATE ../common)