cmake_minimum_required(VERSION 3.22)

project(MemoryPool)

set(CMAKE_CXX_STANDARD 17)

# find_package(Threads)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

add_executable(mp_test01_normal test01_normal.cpp)
add_executable(mp_test02_pmr_pool test02_pmr_pool.cpp)

# target_link_libraries(mp_test01_normal ${CMAKE_THREAD_LIBS_INIT})