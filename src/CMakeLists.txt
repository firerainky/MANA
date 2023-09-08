add_library(warp SHARED hero.cc)

target_include_directories(warp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})