set(BENCHMARK_MAIN pqc_benchmark)
set(BENCHMARK_SOURCES benchmark.cpp)
set(BENCHMARK_INCLUDES ./)

add_executable(${BENCHMARK_MAIN} ${BENCHMARK_SOURCES})
target_link_libraries(${BENCHMARK_MAIN} PRIVATE
                                                benchmark::benchmark)