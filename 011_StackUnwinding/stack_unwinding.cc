#include <stdio.h>

/**
 * https://time.geekbang.org/column/article/169225
 */

class Obj {
public:
    Obj() { printf("Obj::Obj()\n"); }
    ~Obj() { printf("Obj::~Obj()\n"); }
};

void foo(int n) {
    Obj obj;
    if (n == 42) { throw "Life, the universe and everything."; }
}

int main() {
    // 在对象生命周期的时候，自动调用它的析构函数，就是 C++ 管理对象的方式
    // 这就是 Stack unwinding, 栈展开
    try {
        foo(41);
        foo(42);
    } catch (const char *s) { puts(s); }
}