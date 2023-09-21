#include <cstdint>
#include <vector>

namespace fhe {
    class Plaintext {
    public:
        using pt_coeff_type = std::uint64_t;

        Plaintext(pt_coeff_type coeff0) { data_.emplace_back(coeff0); }

    private:
        std::vector<pt_coeff_type> data_;
    };
}// namespace fhe