cmake_minimum_required(VERSION 3.22)

project(ReduceInteger LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CUDA_ARCHITECTURES 70 72 75 80 86 89 90)

add_executable(ReduceInteger reduce_integer.cu)