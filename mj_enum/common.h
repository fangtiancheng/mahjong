#ifndef __COMMON__
#define __COMMON__
#include <tuple>
#include <fstream>
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


#endif