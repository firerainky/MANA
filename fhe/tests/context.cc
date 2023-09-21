#include "context.h"
#include <gtest/gtest.h>

namespace fhe {
    TEST(contextTests, createContext) {
        EncryptionParameters params = EncryptionParameters(scheme_type::bfv);
        params.set_poly_modulus_degree(4096);
        params.set_coeff_modulus({Modulus(40961)});
        params.set_plain_modulus(Modulus(40961));
        Context context = Context(params);
    }
}// namespace fhe