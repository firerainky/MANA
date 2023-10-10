#include <gtest/gtest.h>
#include <stdexcept>

std::uint64_t negateMod(std::uint64_t value, std::uint64_t modulus) {
    if (modulus == 0) { throw std::logic_error("Modulus should not be zero."); }
    if (value >= modulus) {
        throw std::logic_error(
                "Value should not be greater than or equal to modulus.");
    }

    // My easy version
    // if (value == 0) return value;
    // else { return modulus - value; }

    // SEAL version
    std::int64_t non_zero = (value != 0);
    std::uint64_t mask = static_cast<std::uint64_t>(-non_zero);
    return (modulus - value) & mask;
}

TEST(Arith, StaticCastAnIntToUInt) {
    EXPECT_THROW(negateMod(5, 0), std::logic_error);
    EXPECT_THROW(negateMod(5, 4), std::logic_error);
    EXPECT_THROW(negateMod(5, 5), std::logic_error);

    EXPECT_EQ(negateMod(0, 5), 0);
    EXPECT_EQ(negateMod(3, 5), 2);
    EXPECT_EQ(negateMod(2, 5), 3);
}