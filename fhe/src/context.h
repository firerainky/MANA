#include "encryptionparams.h"
#include <vector>

namespace fhe {
    class Context {
    public:
        class ContextData {
        private:
            EncryptionParameters params_;
        };

        explicit Context(EncryptionParameters params) noexcept {
            // context_data_arr_.emplace_back(std::move(params));
            context_data_arr_ = std::vector<ContextData>{};
        }

    private:
        std::vector<ContextData> context_data_arr_;
    };
}// namespace fhe