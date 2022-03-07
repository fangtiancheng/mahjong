//#include <torch/torch.h>
//#include "model.hpp"

#include <iostream>
#include "core.h"
#include "mjenum.h"
int main() {
//    mjenum::gen_dat_file();
//    return 0;
    MJCore mjcore;
    hand_t h = {
            0,
            3, 1, 1, 1, 1, 1, 1, 1, 3,
            0,
            1, 0, 0, 0,0,0,0,0,0,
            0,
            0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0
    };
    mjcore.set_hand(h);
    mjcore.dfs(RED_M5, 0);
    return 0;
}