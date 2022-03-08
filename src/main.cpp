//#include <torch/torch.h>
//#include "model.hpp"

#include <iostream>
#include <ctime>
#include "core.h"
#include "mjenum.h"
int main() {
    MJCore mjcore;
    hand_t h = {
            0,
            1, 1, 1, 1, 1, 1, 1, 1, 3,
            0,
            1, 0, 0, 0,0,0,0,0,0,
            0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,2,0
    };
    mjcore.set_hand(h);
    clock_t start_time = clock();
    mjcore.dfs(RED_M5, 0);
    clock_t end_time = clock();
    std::cout << "time = " << (end_time - start_time)/(double) CLOCKS_PER_SEC << std::endl;
    return 0;
}
