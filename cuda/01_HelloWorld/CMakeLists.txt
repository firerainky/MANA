cmake_minimum_required(VERSION 3.22)

project(HelloWorld LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)

add_executable(HelloWorld main.cu)