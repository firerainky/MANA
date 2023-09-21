#include "modulus.h"
#include <gtest/gtest.h>

namespace fhe {
    TEST(ModulusTests, createModulus) {
        Modulus m0;
        ASSERT_TRUE(m0.is_zero());

        Modulus m1(1);
        ASSERT_FALSE(m1.is_zero());
    }
}// namespace fhe