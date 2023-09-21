#include <cstdint>
#include <vector>

namespace fhe {
    class Ciphertext {
    public:
        using ct_coeff_type = std::uint64_t;

    private:
        std::vector<ct_coeff_type> data_;
    };
}// namespace fhe