#include <gtest/gtest.h>
#include <vector>

namespace mana {
    TEST(Tutor, IterTest) {
        std::vector<int> v = {1, 2, 3, 4, 5};
        for (auto e: v) { std::cout << e << std::endl; }

        for (auto iter = v.begin(); iter != v.end(); ++iter) { std::cout << *iter << std::endl; }
    }
}// namespace mana