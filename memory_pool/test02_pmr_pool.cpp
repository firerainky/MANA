#if __has_include(<memory_resource>)

#include "container_op_test.h"
#include <memory_resource>
#include <thread>
#include <unordered_set>

using namespace std;

using TestType = pmr::unordered_set<int>;
pmr::unsynchronized_pool_resource res;
pmr::polymorphic_allocator<int> a{&res};

int main() {
    thread t{[] {}};
    t.join();

    TestType s{a};
    test_container(s);
}

#endif