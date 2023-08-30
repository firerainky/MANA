#include <gtest/gtest.h>

TEST(CreateObj, ObjPointerIsNotNullWhenDecalred) {
    class A {
    public:
        A(int a) {}
    };

    A *a;
    EXPECT_NE(a, nullptr);
}

TEST(CreateObj, InitArrayWithAuto) {
    std::array arr{1, 2, 3};
    EXPECT_EQ(arr.size(), 3);
}