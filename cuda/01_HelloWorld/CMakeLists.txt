cmake_minimum_required(VERSION 3.22)

project(HelloWorld LANGUAGES CXX C CUDA)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CUDA_ARCHITECTURES 70 72 75 80 86 89 90)

add_executable(HelloWorld main.cu)