#include <iostream>
#include <string>

class EasyPart {
    friend inline std::ostream &operator<<(std::ostream &os,
                                           const EasyPart &e) {
        return os << "Print whatever we want.\n";
    }
};

int main() {
    EasyPart p;
    std::cout << p;
}