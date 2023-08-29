#include <gtest/gtest.h>

TEST(CreateObj, ObjPointerIsNotNullWhenDecalred) {
    class A {
    public:
        A(int a) {}
    };

    A *a;
    EXPECT_NE(a, nullptr);
}