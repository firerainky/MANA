add_executable(mana_tests iter_tests.cc create_obj_tests.cc template_tests.cc arith_tests.cc)

# memoryLeakDetectorPocTest.cpp memoryleak_detect/memoryLeakDetectorBase.cpp)

target_link_libraries(mana_tests PRIVATE GTest::GTest warp)
# target_include_directories(mana_tests PRIVATE memoryleak_detect ./)