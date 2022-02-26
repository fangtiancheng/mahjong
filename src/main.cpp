#include <torch/torch.h>
#include "model.hpp"
#include <iostream>

int main() {
    torch::Device device = torch::cuda::is_available() ? torch::kCUDA : torch::kCPU;
    torch::Tensor tensor = torch::eye(3).to(device);
    std::cout << tensor << std::endl;
}