#include "hero.h"
#include <iostream>

template<typename T>
void Hero<T>::superpower() {
    std::cout << "Hero superpower" << std::endl;
}

template class Hero<int>;