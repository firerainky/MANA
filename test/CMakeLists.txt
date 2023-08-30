add_executable(mana_tests iter_tests.cc create_obj_tests.cc template_tests.cc)

target_link_libraries(mana_tests PRIVATE GTest::GTest)