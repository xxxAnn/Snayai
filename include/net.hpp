#include "snayai.hpp"

namespace snayai {
    namespace net {
        class Net : public torch::nn::Module {
            public:
                Net(std::pair<int, int> gridSize);

                void train(torch::Tensor target, torch::Tensor inputs);

                std::pair<int, int> size;
                torch::nn::Linear input_layer{nullptr};
                torch::nn::Linear hidden_layer1{nullptr};
                torch::nn::Linear output_layer{nullptr};
                
                torch::Tensor forward(torch::Tensor x);

            private:
                int counter = 0;
        };
    }
}