#include "common.h"
std::ostream & operator<<(std::ostream& os, const hand_t& h){
    for(int i=M1; i<=S9;i++){
        if(i%10==0){
            os << '\n';
            continue;
        }
        os << h[i];
    }
    os << '\n';
    for(int i=East;i<=Red;i++){
        os << h[i];
    }
    return os;
}

std::string seq_to_string(seq_t seq){
    switch (seq) {
        case M111: return "M111";
        case M222: return "M222";
        case M333: return "M333";
        case M444: return "M444";
        case M555: return "M555";
        case M666: return "M666";
        case M777: return "M777";
        case M888: return "M888";
        case M999: return "M999";
        case M123: return "M123";
        case M234: return "M234";
        case M345: return "M345";
        case M456: return "M456";
        case M567: return "M567";
        case M678: return "M678";
        case M789: return "M789";
        case M11: return "M11";
        case M22: return "M22";
        case M33: return "M33";
        case M44: return "M44";
        case M55: return "M55";
        case M66: return "M66";
        case M77: return "M77";
        case M88: return "M88";
        case M99: return "M99";
        case M1111: return "M1111";
        case M2222: return "M2222";
        case M3333: return "M3333";
        case M4444: return "M4444";
        case M5555: return "M5555";
        case M6666: return "M6666";
        case M7777: return "M7777";
        case M8888: return "M8888";
        case M9999: return "M9999";
        case P111: return "P111";
        case P222: return "P222";
        case P333: return "P333";
        case P444: return "P444";
        case P555: return "P555";
        case P666: return "P666";
        case P777: return "P777";
        case P888: return "P888";
        case P999: return "P999";
        case P123: return "P123";
        case P234: return "P234";
        case P345: return "P345";
        case P456: return "P456";
        case P567: return "P567";
        case P678: return "P678";
        case P789: return "P789";
        case P11: return "P11";
        case P22: return "P22";
        case P33: return "P33";
        case P44: return "P44";
        case P55: return "P55";
        case P66: return "P66";
        case P77: return "P77";
        case P88: return "P88";
        case P99: return "P99";
        case P1111: return "P1111";
        case P2222: return "P2222";
        case P3333: return "P3333";
        case P4444: return "P4444";
        case P5555: return "P5555";
        case P6666: return "P6666";
        case P7777: return "P7777";
        case P8888: return "P8888";
        case P9999: return "P9999";
        case S111: return "S111";
        case S222: return "S222";
        case S333: return "S333";
        case S444: return "S444";
        case S555: return "S555";
        case S666: return "S666";
        case S777: return "S777";
        case S888: return "S888";
        case S999: return "S999";
        case S11: return "S11";
        case S22: return "S22";
        case S33: return "S33";
        case S44: return "S44";
        case S55: return "S55";
        case S66: return "S66";
        case S77: return "S77";
        case S88: return "S88";
        case S99: return "S99";
        case S123: return "S123";
        case S234: return "S234";
        case S345: return "S345";
        case S456: return "S456";
        case S567: return "S567";
        case S678: return "S678";
        case S789: return "S789";
        case S1111: return "S1111";
        case S2222: return "S2222";
        case S3333: return "S3333";
        case S4444: return "S4444";
        case S5555: return "S5555";
        case S6666: return "S6666";
        case S7777: return "S7777";
        case S8888: return "S8888";
        case S9999: return "S9999";
        case EEE: return "EEE";
        case SSS: return "SSS";
        case WWW: return "WWW";
        case NNN: return "NNN";
        case WhiteWW: return "WhiteWW";
        case GreenGG: return "GreenGG";
        case RedRR: return "RedRR";
        case EE: return "EE";
        case SS: return "SS";
        case WW: return "WW";
        case NN: return "NN";
        case WhiteW: return "WhiteW";
        case GreenG: return "GreenG";
        case RedR: return "RedR";
        case EEEE: return "EEEE";
        case SSSS: return "SSSS";
        case WWWW: return "WWWW";
        case NNNN: return "NNNN";
        case WhiteWWW: return "WhiteWWW";
        case GreenGGG: return "GreenGGG";
        case RedRRR: return "RedRRR";
        default: return "ERROR";
    }
}
bool is_jyuntyanta(seq_t x){
    // 检查是否纯带幺九
    switch (x) {
        case M111: case M999: case M123: case M789: case M11: case M99: case M1111: case M9999:
            case P111: case P999: case P123: case P789: case P11: case P99: case P1111: case P9999:
                case S111: case S999: case S123: case S789: case S11: case S99: case S1111: case S9999:
                    return true;
                    default:
                        return false;
    }
}
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
void fuuro_t::clear() noexcept {
    sequences.clear();
    anka_seq.clear();
    minka_seq.clear();
}
bool fuuro_t::concealed_hand() const {
    return sequences.size() == anka_seq.size();
}
int fuuro_t::tile_num() const {
    return 3*sequences.size() + anka_seq.size() + minka_seq.size();
}
seq_t tile_to_triplet(tile_t x){
    /*
s = """
seq_t tile_to_triplet(tile_t x){
    switch(x){
%s
    }
}
"""
add_s = []
for color in ["M", "P", "S"]:
    for i in range(1, 10):
        add_s.append("        case %s%d: return %s%d%d%d;\n"%(color,i,color,i,i,i));

for c, append_c, tile in zip(["E", "S", "W", "N", "W", "G", "R"], ["E", "S", "W", "N", "White", "Green", "Red"], ["East","South","West","North","White","Green","Red"]):
    add_s.append("        case %s: return %s%s%s;\n"%(tile, append_c, c, c))

add_s = "".join(add_s) + "        default: exit(1);"
print(s%add_s)
     */
    switch(x){
        case M1: return M111;
        case M2: return M222;
        case M3: return M333;
        case M4: return M444;
        case RED_M5:
            case M5: return M555;
            case M6: return M666;
            case M7: return M777;
            case M8: return M888;
            case M9: return M999;
            case P1: return P111;
            case P2: return P222;
            case P3: return P333;
            case P4: return P444;
            case RED_P5:
                case P5: return P555;
                case P6: return P666;
                case P7: return P777;
                case P8: return P888;
                case P9: return P999;
                case S1: return S111;
                case S2: return S222;
                case S3: return S333;
                case S4: return S444;
                case RED_S5:
                    case S5: return S555;
                    case S6: return S666;
                    case S7: return S777;
                    case S8: return S888;
                    case S9: return S999;
                    case East: return EEE;
                    case South: return SSS;
                    case West: return WWW;
                    case North: return NNN;
                    case White: return WhiteWW;
                    case Green: return GreenGG;
                    case Red: return RedRR;
                    default:
                        exit(1);
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
score_level_t score_to_level(int fan){
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
bool test_file_exist(const std::string& file_name){
    std::ifstream f(file_name, std::ios::in);
    return f.good();
}