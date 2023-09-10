#include <gtest/gtest.h>
#include <vector>

namespace mana {
    TEST(Iterators, TraverseTest) {
        std::vector<int> v = {1, 2, 3, 4, 5};
        for (auto e: v) { std::cout << e << std::endl; }

        for (auto iter = v.begin(); iter != v.end(); ++iter) {
            std::cout << *iter << std::endl;
        }
    }

    TEST(Iterators, AdvanceTest) {
        std::vector<int> vec = {1, 2, 3, 4, 5};

        // Declaring iterator to a vector.
        std::vector<int>::iterator iter = vec.begin();

        // Using advance() to increment iterator position. Points to 4.
        advance(iter, 3);

        std::cout << "The position of iterator after advancing is: ";
        std::cout << *iter << "\n";
    }

    TEST(Iterators, NextPrevTest) {
        std::vector<int> vec = {1, 2, 3, 4, 5};

        auto beginIter = vec.begin();
        auto endIter = vec.end();

        // Using next() to return new iterator
        auto nextIter = next(beginIter, 3);
        auto prevIter = prev(endIter, 3);

        EXPECT_EQ(*nextIter, 4);
        EXPECT_EQ(*prevIter, 3);
    }

    TEST(Iterators, InserterTest) {
        std::vector<int> vec = {1, 2, 3, 4, 5};
        std::vector<int> vec1 = {10, 20, 30};

        auto it = vec.begin();
        advance(it, 3);

        copy(vec1.begin(), vec1.end(), inserter(vec, it));

        std::cout << "The new vector after inserting elements is: ";
        for (auto it: vec) { std::cout << it << " "; }
        std::cout << "\n";
    }
}// namespace mana