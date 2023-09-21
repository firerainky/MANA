#include <cstdint>
#include <vector>

namespace fhe {
    class Plaintext {
    public:
        using pt_coeff_type = std::uint64_t;

    private:
        std::vector<pt_coeff_type> data_;
    };
}// namespace fhe