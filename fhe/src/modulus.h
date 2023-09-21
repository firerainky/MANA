#include <cstdint>

namespace fhe {
    class Modulus {
    public:
        Modulus(std::uint64_t value = 0) noexcept : value_(value) {}
        inline bool is_zero() { return value_ == 0; }

    private:
        std::uint64_t value_ = 0;
    };
}// namespace fhe