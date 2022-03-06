//#include <torch/torch.h>
//#include "model.hpp"

#include <iostream>
#include "core.h"
#include "mjenum_loader.h"
int main() {
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
    mjcore.search();
    return 0;
}