#ifndef __COMMON__
#define __COMMON__
#include <array>
#include <vector>
#include <set>
#include <optional>
#include <map>
#include <tuple>
typedef std::array<int, 37> hand_t;

// seq_t: 0-36是刻子数量(杠子也算刻子),37-57是顺子数量,58-94是杠子数量
// seq_t[RED_?5] > 0表示有红宝牌, seq_t[k]表示面子数量
typedef std::array<int, 95> seq_t;

enum tile_t{
    RED_M5 = 0, // whether has red M5
    M1, M2, M3, M4, M5, M6, M7, M8, M9,
    RED_P5 = 10, // whether has red P5
    P1, P2, P3, P4, P5, P6, P7, P8, P9,
    RED_S5 = 20, // whether has red S5
    S1, S2, S3, S4, S5, S6, S7, S8, S9,
    East = 30, South, West, North,
    White, Green, Red
};

const std::set<int> orphans = {1,9,11,19,21,29,30,31,32,33,34,35,36}; // 幺九
const std::set<int> greens = {S2, S3, S4, S6, S8, Green}; // 纯绿
const std::set<int> terminals = {1,9,11,19,21,29}; // 老头
const std::array<std::tuple<int, int, int>, 95> id_to_seq = {
        std::tuple<int, int, int>(RED_M5, RED_M5, RED_M5),
        std::tuple<int, int, int>(1, 1, 1),
        std::tuple<int, int, int>(2, 2, 2),
        std::tuple<int, int, int>(3, 3, 3),
        std::tuple<int, int, int>(4, 4, 4),
        std::tuple<int, int, int>(5, 5, 5),
        std::tuple<int, int, int>(6, 6, 6),
        std::tuple<int, int, int>(7, 7, 7),
        std::tuple<int, int, int>(8, 8, 8),
        std::tuple<int, int, int>(9, 9, 9),
        std::tuple<int, int, int>(RED_P5, RED_P5, RED_P5),
        std::tuple<int, int, int>(11, 11, 11),
        std::tuple<int, int, int>(12, 12, 12),
        std::tuple<int, int, int>(13, 13, 13),
        std::tuple<int, int, int>(14, 14, 14),
        std::tuple<int, int, int>(15, 15, 15),
        std::tuple<int, int, int>(16, 16, 16),
        std::tuple<int, int, int>(17, 17, 17),
        std::tuple<int, int, int>(18, 18, 18),
        std::tuple<int, int, int>(19, 19, 19),
        std::tuple<int, int, int>(RED_S5, RED_S5, RED_S5),
        std::tuple<int, int, int>(21, 21, 21),
        std::tuple<int, int, int>(22, 22, 22),
        std::tuple<int, int, int>(23, 23, 23),
        std::tuple<int, int, int>(24, 24, 24),
        std::tuple<int, int, int>(25, 25, 25),
        std::tuple<int, int, int>(26, 26, 26),
        std::tuple<int, int, int>(27, 27, 27),
        std::tuple<int, int, int>(28, 28, 28),
        std::tuple<int, int, int>(29, 29, 29),
        std::tuple<int, int, int>(30, 30, 30),
        std::tuple<int, int, int>(31, 31, 31),
        std::tuple<int, int, int>(32, 32, 32),
        std::tuple<int, int, int>(33, 33, 33),
        std::tuple<int, int, int>(34, 34, 34),
        std::tuple<int, int, int>(35, 35, 35),
        std::tuple<int, int, int>(36, 36, 36),
        std::tuple<int, int, int>(1, 2, 3),
        std::tuple<int, int, int>(2, 3, 4),
        std::tuple<int, int, int>(3, 4, 5),
        std::tuple<int, int, int>(4, 5, 6),
        std::tuple<int, int, int>(5, 6, 7),
        std::tuple<int, int, int>(6, 7, 8),
        std::tuple<int, int, int>(7, 8, 9),
        std::tuple<int, int, int>(11, 12, 13),
        std::tuple<int, int, int>(12, 13, 14),
        std::tuple<int, int, int>(13, 14, 15),
        std::tuple<int, int, int>(14, 15, 16),
        std::tuple<int, int, int>(15, 16, 17),
        std::tuple<int, int, int>(16, 17, 18),
        std::tuple<int, int, int>(17, 18, 19),
        std::tuple<int, int, int>(21, 22, 23),
        std::tuple<int, int, int>(22, 23, 24),
        std::tuple<int, int, int>(23, 24, 25),
        std::tuple<int, int, int>(24, 25, 26),
        std::tuple<int, int, int>(25, 26, 27),
        std::tuple<int, int, int>(26, 27, 28),
        std::tuple<int, int, int>(27, 28, 29),
        // 下面是：是否包含杠子，比如我杠了4个M2，那么id_to_seq[1]和id_to_seq[1+34+21]都是1
        std::tuple<int, int, int>(RED_M5, RED_M5, RED_M5), // 没意义，仅仅对齐内存
        std::tuple<int, int, int>(1, 1, 1),
        std::tuple<int, int, int>(2, 2, 2),
        std::tuple<int, int, int>(3, 3, 3),
        std::tuple<int, int, int>(4, 4, 4),
        std::tuple<int, int, int>(5, 5, 5),
        std::tuple<int, int, int>(6, 6, 6),
        std::tuple<int, int, int>(7, 7, 7),
        std::tuple<int, int, int>(8, 8, 8),
        std::tuple<int, int, int>(9, 9, 9),
        std::tuple<int, int, int>(RED_P5, RED_P5, RED_P5), // 没意义，仅仅对齐内存
        std::tuple<int, int, int>(11, 11, 11),
        std::tuple<int, int, int>(12, 12, 12),
        std::tuple<int, int, int>(13, 13, 13),
        std::tuple<int, int, int>(14, 14, 14),
        std::tuple<int, int, int>(15, 15, 15),
        std::tuple<int, int, int>(16, 16, 16),
        std::tuple<int, int, int>(17, 17, 17),
        std::tuple<int, int, int>(18, 18, 18),
        std::tuple<int, int, int>(19, 19, 19),
        std::tuple<int, int, int>(RED_S5, RED_S5, RED_S5), // 没意义，仅仅对齐内存
        std::tuple<int, int, int>(21, 21, 21),
        std::tuple<int, int, int>(22, 22, 22),
        std::tuple<int, int, int>(23, 23, 23),
        std::tuple<int, int, int>(24, 24, 24),
        std::tuple<int, int, int>(25, 25, 25),
        std::tuple<int, int, int>(26, 26, 26),
        std::tuple<int, int, int>(27, 27, 27),
        std::tuple<int, int, int>(28, 28, 28),
        std::tuple<int, int, int>(29, 29, 29),
        std::tuple<int, int, int>(30, 30, 30),
        std::tuple<int, int, int>(31, 31, 31),
        std::tuple<int, int, int>(32, 32, 32),
        std::tuple<int, int, int>(33, 33, 33),
        std::tuple<int, int, int>(34, 34, 34),
        std::tuple<int, int, int>(35, 35, 35),
        std::tuple<int, int, int>(36, 36, 36)
};


#endif