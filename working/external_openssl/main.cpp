#include <openssl/rand.h>
#include <iostream>

int main() {
    unsigned char buffer[16];
    RAND_bytes(buffer, sizeof(buffer));

    std::cout << "Random bytes generated using OpenSSL: ";
    for (int i = 0; i < sizeof(buffer); ++i) {
        std::cout << std::hex << static_cast<int>(buffer[i]);
    }
    std::cout << std::endl;

    return 0;
}
