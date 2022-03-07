#ifndef __SYANTEN_ENUM__
#define __SYANTEN_ENUM__
#include "common.h"
#include "mjenum.h"
#include "vector"
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

namespace syanten{
    using namespace mjenum;
    std::map<uint32_t, std::tuple<int, int, int, int>> load_syanten_map();
    int _checkNormalSyanten(hand_t& hand, int fuuro_num);
    int NormalSyanten(hand_t& raw_hand, int fuuro_num);
    int KokusiSyanten(hand_t& raw_hand);//国士シャンテン
    int TiitoituSyanten(hand_t& raw_hand);//チートイシャンテン
    EXPORT int get_syanten(hand_t& raw_hand, int fuuro_num);
    extern std::map<uint32_t, std::tuple<int, int, int, int>> syanten_map;
}
#endif