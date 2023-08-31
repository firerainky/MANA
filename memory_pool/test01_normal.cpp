#include "container_op_test.h"
#include <thread>
#include <unordered_set>

using namespace std;

using TestType = unordered_set<int>;

int main() {
    thread t{[] {}};
    t.join();

    TestType s;
    test_container(s);
}
