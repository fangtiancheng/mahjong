#ifndef __COMMON__
#define __COMMON__
#include <array>
#include <vector>
#include <set>
#include <optional>
#include <map>
#include <tuple>
#include <set>
#define EXPORT
typedef std::array<int, 37> hand_t;
// 1 1 1 2 3 4 5 5 6 7 8 9 9 9s  -5s +1p
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

bool is_straight(seq_t s){
    // 检查是否为顺子
    if(s>=EEE) return false;
    int x = s%(P111-M111);
    return x >= M123 && x <= M789;
}
bool is_triplet(seq_t s){
    // 检查是否为刻子(包括杠子)
    if(s>=EEE && s<=RedRR) return true;
    if(s>=EEEE && s<=RedRRR) return true;
    int x = s%(P111-M111);
    if(x>=M111 && x<=M999) return true;
    if(x>=M1111 && x<=M9999) return true;
    return false;
}
bool is_pair(seq_t s){
    // 检查是否为对子
    if(s>=EE && s<=RedR) return true;
    int x = s%(P111-M111);
    return x>=M11 && x<=M99;
}

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
    int fuuro_num() const {
        return sequences.size();
    }
    bool concealed_hand() const {
        return sequences.size() == anka_seq.size();
    }
    int tile_num() const {
        return 3*sequences.size() + anka_seq.size() + minka_seq.size();
    }
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

std::vector<tile_t> seq_to_tile(seq_t s){
    /*
s = """
std::vector<tile_t> seq_to_tile(seq_t s){
    switch(s){
%s
    }
}
"""
add_s = []
for color in ["M", "P", "S"]:
    for i in range(1, 10):
        add_s.append("        case %s%d%d%d: return {%s%d, %s%d, %s%d};\n"%(color, i,i,i,color,i,color,i,color,i));
    for i in range(1, 8):
        add_s.append("        case %s%d%d%d: return {%s%d, %s%d, %s%d};\n"%(color, i, i+1, i+2, color,i, color,i+1, color,i+2))
    for i in range(1, 10):
        add_s.append("        case %s%d%d: return {%s%d, %s%d};\n"%(color, i, i, color,i, color,i))
    for i in range(1, 10):
        add_s.append("        case %s%d%d%d%d: return {%s%d, %s%d, %s%d, %s%d};\n"%(color,i,i,i,i,color,i,color,i,color,i,color,i))
for c, append_c, tile in zip(["E", "S", "W", "N", "W", "G", "R"], ["E", "S", "W", "N", "White", "Green", "Red"], ["East","South","West","North","White","Green","Red"]):
    add_s.append("        case %s%s%s: return {%s, %s, %s};\n"%(append_c, c, c, tile, tile, tile))
for c, append_c, tile in zip(["E", "S", "W", "N", "W", "G", "R"], ["E", "S", "W", "N", "White", "Green", "Red"], ["East","South","West","North","White","Green","Red"]):
    add_s.append("        case %s%s: return {%s, %s};\n"%(append_c, c, tile, tile))
for c, append_c, tile in zip(["E", "S", "W", "N", "W", "G", "R"], ["E", "S", "W", "N", "White", "Green", "Red"], ["East","South","West","North","White","Green","Red"]):
    add_s.append("        case %s%s%s%s: return {%s, %s, %s, %s};\n"%(append_c, c, c, c, tile, tile, tile, tile))
add_s = "".join(add_s) + "default: return {};"
print(s%add_s)
     */
    switch(s){
        case M111: return {M1, M1, M1};
        case M222: return {M2, M2, M2};
        case M333: return {M3, M3, M3};
        case M444: return {M4, M4, M4};
        case M555: return {M5, M5, M5};
        case M666: return {M6, M6, M6};
        case M777: return {M7, M7, M7};
        case M888: return {M8, M8, M8};
        case M999: return {M9, M9, M9};
        case M123: return {M1, M2, M3};
        case M234: return {M2, M3, M4};
        case M345: return {M3, M4, M5};
        case M456: return {M4, M5, M6};
        case M567: return {M5, M6, M7};
        case M678: return {M6, M7, M8};
        case M789: return {M7, M8, M9};
        case M11: return {M1, M1};
        case M22: return {M2, M2};
        case M33: return {M3, M3};
        case M44: return {M4, M4};
        case M55: return {M5, M5};
        case M66: return {M6, M6};
        case M77: return {M7, M7};
        case M88: return {M8, M8};
        case M99: return {M9, M9};
        case M1111: return {M1, M1, M1, M1};
        case M2222: return {M2, M2, M2, M2};
        case M3333: return {M3, M3, M3, M3};
        case M4444: return {M4, M4, M4, M4};
        case M5555: return {M5, M5, M5, M5};
        case M6666: return {M6, M6, M6, M6};
        case M7777: return {M7, M7, M7, M7};
        case M8888: return {M8, M8, M8, M8};
        case M9999: return {M9, M9, M9, M9};
        case P111: return {P1, P1, P1};
        case P222: return {P2, P2, P2};
        case P333: return {P3, P3, P3};
        case P444: return {P4, P4, P4};
        case P555: return {P5, P5, P5};
        case P666: return {P6, P6, P6};
        case P777: return {P7, P7, P7};
        case P888: return {P8, P8, P8};
        case P999: return {P9, P9, P9};
        case P123: return {P1, P2, P3};
        case P234: return {P2, P3, P4};
        case P345: return {P3, P4, P5};
        case P456: return {P4, P5, P6};
        case P567: return {P5, P6, P7};
        case P678: return {P6, P7, P8};
        case P789: return {P7, P8, P9};
        case P11: return {P1, P1};
        case P22: return {P2, P2};
        case P33: return {P3, P3};
        case P44: return {P4, P4};
        case P55: return {P5, P5};
        case P66: return {P6, P6};
        case P77: return {P7, P7};
        case P88: return {P8, P8};
        case P99: return {P9, P9};
        case P1111: return {P1, P1, P1, P1};
        case P2222: return {P2, P2, P2, P2};
        case P3333: return {P3, P3, P3, P3};
        case P4444: return {P4, P4, P4, P4};
        case P5555: return {P5, P5, P5, P5};
        case P6666: return {P6, P6, P6, P6};
        case P7777: return {P7, P7, P7, P7};
        case P8888: return {P8, P8, P8, P8};
        case P9999: return {P9, P9, P9, P9};
        case S111: return {S1, S1, S1};
        case S222: return {S2, S2, S2};
        case S333: return {S3, S3, S3};
        case S444: return {S4, S4, S4};
        case S555: return {S5, S5, S5};
        case S666: return {S6, S6, S6};
        case S777: return {S7, S7, S7};
        case S888: return {S8, S8, S8};
        case S999: return {S9, S9, S9};
        case S123: return {S1, S2, S3};
        case S234: return {S2, S3, S4};
        case S345: return {S3, S4, S5};
        case S456: return {S4, S5, S6};
        case S567: return {S5, S6, S7};
        case S678: return {S6, S7, S8};
        case S789: return {S7, S8, S9};
        case S11: return {S1, S1};
        case S22: return {S2, S2};
        case S33: return {S3, S3};
        case S44: return {S4, S4};
        case S55: return {S5, S5};
        case S66: return {S6, S6};
        case S77: return {S7, S7};
        case S88: return {S8, S8};
        case S99: return {S9, S9};
        case S1111: return {S1, S1, S1, S1};
        case S2222: return {S2, S2, S2, S2};
        case S3333: return {S3, S3, S3, S3};
        case S4444: return {S4, S4, S4, S4};
        case S5555: return {S5, S5, S5, S5};
        case S6666: return {S6, S6, S6, S6};
        case S7777: return {S7, S7, S7, S7};
        case S8888: return {S8, S8, S8, S8};
        case S9999: return {S9, S9, S9, S9};
        case EEE: return {East, East, East};
        case SSS: return {South, South, South};
        case WWW: return {West, West, West};
        case NNN: return {North, North, North};
        case WhiteWW: return {White, White, White};
        case GreenGG: return {Green, Green, Green};
        case RedRR: return {Red, Red, Red};
        case EE: return {East, East};
        case SS: return {South, South};
        case WW: return {West, West};
        case NN: return {North, North};
        case WhiteW: return {White, White};
        case GreenG: return {Green, Green};
        case RedR: return {Red, Red};
        case EEEE: return {East, East, East, East};
        case SSSS: return {South, South, South, South};
        case WWWW: return {West, West, West, West};
        case NNNN: return {North, North, North, North};
        case WhiteWWW: return {White, White, White, White};
        case GreenGGG: return {Green, Green, Green, Green};
        case RedRRR: return {Red, Red, Red, Red};
        default: return {};
    }
}

bool is_red_dora(tile_t tile){
    switch (tile) {
        case RED_M5: case RED_P5: case RED_S5:
            return true;
        default:
            return false;
    }
}
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
inline score_level_t score_to_level(int fan){
    switch (fan) {
        case 0: return LEVEL_0;
        case 1: case 2: case 3:
            return LEVEL_1;
        case 4: case 5:
            return LEVEL_2;
        case 6: case 7:
            return LEVEL_3;
        case 8: case 9: case 10:
            return  LEVEL_4;
        case 11: case 12:
            return LEVEL_5;
        default:
            if(fan>=13) return LEVEL_6;
            else return LEVEL_0;
    }
}
#endif