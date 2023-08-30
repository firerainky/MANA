#include <gtest/gtest.h>

// Function template
template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

// Class template
template<typename T>
class A {
public:
    A(T a) {}
};

TEST(TemplateTests, SimplestTemplates) {
    // Function template
    EXPECT_EQ(max(1, 2), 2);
    EXPECT_EQ(max(1.0, 2.0), 2.0);

    // Class template
    A<int> a(1);
    A<double> b(1.0);
}