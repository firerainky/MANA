add_executable(fhe_tests plaintext.cc ciphertext.cc context.cc modulus.cc)

target_link_libraries(fhe_tests PRIVATE GTest::GTest fhe_lib)