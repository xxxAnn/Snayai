#include "snayai.hpp"
#include <torch/torch.h>

snayai::net::Net::Net(std::pair<int, int> gridSize) {
    size = gridSize;
    // Predicts the expected reward for each action
    // Input [
    //    food_forward, food_left, food_right,
    //    wall_forward, wall_left, wall_right,
    // ]
    // Output [expected_reward_straight, expected_reward_left, expected_reward_right]
    input_layer = register_module("input_layer", torch::nn::Linear(6, 128));
    hidden_layer1 = register_module("hidden_layer", torch::nn::Linear(128, 32));
    output_layer = register_module("output_layer", torch::nn::Linear(32, 3));

}


torch::Tensor snayai::net::Net::forward(torch::Tensor x) {
    x = torch::relu(input_layer->forward(x));
    x = hidden_layer1->forward(x); 
    x = output_layer->forward(x);
    return x;
}

void snayai::net::Net::train(torch::Tensor target, torch::Tensor inputs) {
    torch::optim::Adam optimizer(parameters(), 1e-3);

    optimizer.zero_grad();
    torch::Tensor output = forward(inputs);
    torch::Tensor l = torch::nn::functional::mse_loss(output, target);

    l.backward();
    optimizer.step();
}