#include "modulus.h"
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace fhe {
    enum class scheme_type { bfv, ckks, bgv };

    class EncryptionParameters {
    public:
        EncryptionParameters(scheme_type scheme) noexcept : scheme_(scheme) {}

        inline void
        set_poly_modulus_degree(std::size_t poly_modulus_degree) noexcept {
            poly_modulus_degree_ = poly_modulus_degree;
        }

        inline void
        set_coeff_modulus(const std::vector<Modulus> &coeff_modulus) noexcept {
            coeff_modulus_ = coeff_modulus;
        }

        inline void set_plain_modulus(Modulus plain_modulus) {
            if (scheme_ != scheme_type::bfv && scheme_ != scheme_type::bgv)
                throw std::logic_error("plain_modulus cannot be set for CKKS");
            plain_modulus_ = plain_modulus;
        }

    private:
        scheme_type scheme_;
        std::size_t poly_modulus_degree_ = 0;
        std::vector<Modulus> coeff_modulus_;
        Modulus plain_modulus_;
    };
}// namespace fhe