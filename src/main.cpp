//#include <torch/torch.h>
//#include "model.hpp"

#include <iostream>
#include "core.h"
#include "mjenum.h"
int main() {
//    mjenum::gen_dat_file();
//    return 0;
    mjenum::dump_wind_map(character_map, "dump_wind_map.dat");
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
//    auto [_,__,___,key] = mjenum::hand_to_index(h);
//    std::cout << "key = " << key << std::endl;
//    std::cout << character_map.at(key) << std::endl;
//    return 0;
//    mjenum::dump_num_map(number_map, "dump_num_map.dat");
    mjcore.set_hand(h);
    mjcore.dfs(RED_M5, 0);
    return 0;
}