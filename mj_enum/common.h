#ifndef __COMMON__
#define __COMMON__
#include <tuple>
#include <fstream>
#include <iostream>
#include <array>
#include <set>
#include <string>
#define DEBUG
//#define DEBUG printf("\"%s:%d\"\n", __FILE__, __LINE__);
using hand_t = std::array<int, 9>;
const std::array<std::string, 25> seq_to_string = {
        "1, 1, 1",
        "2, 2, 2",
        "3, 3, 3",
        "4, 4, 4",
        "5, 5, 5",
        "6, 6, 6",
        "7, 7, 7",
        "8 ,8, 8",
        "9, 9, 9",
        "1, 2, 3",
        "2, 3, 4",
        "3, 4, 5",
        "4, 5, 6",
        "5, 6, 7",
        "6, 7, 8",
        "7, 8, 9",
        "1, 1",
        "2, 2",
        "3, 3",
        "4, 4",
        "5, 5",
        "6, 6",
        "7, 7",
        "8, 8",
        "9, 9"
};
//using seq_t = int;
enum seq_t{
    _000 = 0,
    _111,
    _222,
    _333,
    _444,
    _555,
    _666,
    _777,
    _888,
    _012 = 9,
    _123,
    _234,
    _345,
    _456,
    _567,
    _678,
    _11 = 16,
    _22,
    _33,
    _44,
    _55,
    _66,
    _77,
    _88,
    _99
};
bool add(hand_t& h){
    DEBUG
    int idx = 0;
    while(++(h[idx]) == 5){
        DEBUG
        h[idx] = 0;
        idx++;
        if(idx >= 9){
            return false;
        }
    }
    return true;
}

uint32_t hand_encoder(const hand_t& h){
    // 手牌编码器
    uint32_t ans = 0;
    for(int i=0; i<9;i++){
        ans <<= 3;
        ans |= (h[i] & 0b111);
    }
    return ans;
}

hand_t hand_decoder(uint32_t code){
    hand_t result;
    for(int i=8;i>=0; i--){
        result[i] = code & 0b111;
        code >>= 3;
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const std::set<std::tuple<std::multiset<seq_t>, bool>>& x){
    os << '{';
    for(auto item=x.cbegin(); item!=x.cend();item++){
        os << "[";
        auto [it, have_pair] = *item;
        for(auto ptr=it.cbegin();ptr!=it.cend();ptr++){
            //            os << '(' << seq_to_string[(int)*ptr] << ')' << ", ";
            os << (int)*ptr << ", ";
        }
        os << "], ";
    }
    os << '}';
    return os;
}

std::ostream& operator << (std::ostream& os, const hand_t& h){
    for(int i=0; i< 9;i++){
        os<< h[i];
    }
    return os;
}

#endif