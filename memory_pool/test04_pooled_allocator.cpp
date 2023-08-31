#include "container_op_test.h"
#include "pooled_allocator.h"
#include <thread>
#include <unordered_set>

using namespace std;

using TestType =
        unordered_set<int, hash<int>, equal_to<int>, pooled_allocator<int>>;
thread_local TestType s;

int main() {
    thread t{[] {}};
    t.join();

    test_container(s);
}
