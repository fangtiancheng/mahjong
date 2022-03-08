#pragma once
#ifndef __COMMON__
#define __COMMON__
#include <array>
#include <vector>
#include <iostream>
#include <set>
#include <optional>
#include <map>
#include <tuple>
#include <set>
#include <fstream>
#define EXPORT
#define IN
#define OUT
typedef std::array<int, 37> hand_t;
std::ostream & operator<<(std::ostream& , const hand_t&);
enum seq_t{
    M111, M222, M333, M444, M555, M666, M777, M888, M999,
    M123,M234, M345, M456, M567, M678, M789,
    M11, M22, M33, M44, M55, M66, M77, M88, M99,
    M1111, M2222, M3333, M4444, M5555, M6666, M7777, M8888, M9999,

    P111, P222, P333, P444, P555, P666, P777, P888, P999,
    P123,P234, P345, P456, P567, P678, P789,
    P11, P22, P33, P44, P55, P66, P77, P88, P99,
    P1111, P2222, P3333, P4444, P5555, P6666, P7777, P8888, P9999,

    S111,S222, S333, S444, S555, S666, S777, S888, S999,
    S11, S22, S33, S44, S55, S66, S77, S88, S99,
    S123,S234, S345, S456, S567, S678, S789,
    S1111, S2222, S3333, S4444, S5555, S6666, S7777, S8888, S9999,

    EEE, SSS, WWW, NNN, WhiteWW, GreenGG, RedRR,
    EE, SS, WW, NN, WhiteW, GreenG, RedR,
    EEEE, SSSS, WWWW, NNNN, WhiteWWW, GreenGGG, RedRRR
};
std::string seq_to_string(seq_t seq);
bool is_jyuntyanta(seq_t x);
bool is_straight(seq_t s);
bool is_triplet(seq_t s);
bool is_pair(seq_t s);

struct fuuro_t{
    /* example:
     * furro: M1111(an) P2222(min) S123
     * @sequences: M1111 P2222 S123
     * @anka_seq: M1111
     * @minka_seq:P2222
     */
    std::multiset<seq_t> sequences = {};
    std::set<seq_t> anka_seq = {};
    std::set<seq_t> minka_seq = {};
    void clear() noexcept ;
    inline int fuuro_num() const {
        return sequences.size();
    }
    bool concealed_hand() const;
    int tile_num() const ;
//    std::tuple<int, int, int> num_five_in_fuuro()const {
//        // return number of [M5, P5, S5]
//        int num[3] = {0,0,0};
//        for(seq_t s: sequences){
//            switch (s) {
//                case M345: case M456: case M567: num[0]++; break;
//                case M55: num[0]+=2; break;
//                case M555: num[0] += 3;break;
//                case M5555: num[0] += 4; break;
//
//                case P345: case P456: case P567: num[1]++; break;
//                case P55: num[1]+=2; break;
//                case P555: num[1] += 3; break;
//                case P5555: num[1] += 4; break;
//
//                case S345: case S456: case S567: num[2]++; break;
//                case S55: num[2]+=2; break;
//                case S555: num[2] += 3; break;
//                case S5555: num[2] += 4; break;
//
//                default:
//                    break;
//            }
//        }
//        return std::make_tuple(num[0], num[1], num[2]);
//    }
};


enum tile_t{
    RED_M5 = 0, // num of M5 red dora(support red dora > 1)
    M1, M2, M3, M4, M5, M6, M7, M8, M9,
    RED_P5 = 10,
    P1, P2, P3, P4, P5, P6, P7, P8, P9,
    RED_S5 = 20,
    S1, S2, S3, S4, S5, S6, S7, S8, S9,
    East = 30, South, West, North,
    White, Green, Red
};

seq_t tile_to_triplet(tile_t x);

std::vector<tile_t> seq_to_tile(seq_t s);

bool is_red_dora(tile_t tile);
const std::vector<tile_t> orphans = {M1,M9,P1,P9,S1,S9,East,South,West,North,White,Green,Red}; // 幺九
const std::vector<tile_t> greens = {S2, S3, S4, S6, S8, Green}; // 纯绿
const std::vector<tile_t> terminals = {M1, M9, P1, P9, S1, S9}; // 老头

enum score_level_t{
    LEVEL_0, // 0 fan
    LEVEL_1, // 1-3 fan
    LEVEL_2, // 4-5 fan
    LEVEL_3, // 6-7 fan
    LEVEL_4, // 8-10 fan
    LEVEL_5, // 11-12 fan
    LEVEL_6 // 13+ fan
};
score_level_t score_to_level(int fan);
bool test_file_exist(const std::string& );
#endif