#include "shape.h"
#include <cstdio>
#include <utility>

int main() {
    puts("main()");
    Result &&r = std::move(process_shape(Circle(), Triangle()));
    puts("something else");
    r.doSomething();
}