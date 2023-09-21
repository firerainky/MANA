#include "plaintext.h"
#include <gtest/gtest.h>

namespace fhe {
    TEST(plaintextTests, createPlaintexts) { Plaintext pt = Plaintext(6); }

}// namespace fhe