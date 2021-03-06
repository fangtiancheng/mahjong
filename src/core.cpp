#include "core.h"
#define DEBUG printf("\"%s:%d\"\n", __FILE__, __LINE__);
bool MJCore::judge_yaku_pair(seq_t x) const {
    // 是否为役牌
    if(is_straight(x)) return false;
    tile_t t = seq_to_tile(x)[0];
    switch (t) {
        case White: case Green: case Red:
            return true;
        default:
            if(t == jikazi || t == bakazi)
                return true;
            else
                return false;
    }
}

int MJCore::judge_kokusi() const {
    // 国士无双 13orphans
    // 检查是否胡牌(非常规胡法)，但是不检查手牌数量是否合法
    if(fuuro.fuuro_num()!=0) return false;
    bool gt1 = false;// great than 1
    bool is13 = false;
    for(tile_t i: orphans){
        if(hand[i] < 1) return false;
        if(hand[i] > 1){
            gt1 = true;
            if(rong_which==i)
                is13 = true;
        }
    }
    if(gt1)
        return is13 ? 2:1;
    else return 0;
}
int MJCore::judge_tuuiisou() const {
    // 字一色 all honor tiles
    // 不检查是否胡牌，不检查手牌数量是否合法
    for(int i=0; i<East; i++){
        if(hand[i] > 0)
            return false;
    }
    return true;
}
int MJCore::judge_daisangen() const {
    // 大三元
    // 不检查是否胡牌，不检查手牌数量是否合法
    return (hand[tile_t::White]>=3) &&
    (hand[tile_t::Green]>=3) &&
    (hand[tile_t::Red]>=3);
}
int MJCore::judge_tyuuren() const {
    // 九莲宝灯
    // 不检查是否胡牌，不检查手牌数量是否合法
    // 虽然 [S: 1112345678999 P: 2]也返回true
    // 但是这种方法一定过不了胡牌，所以没事
    if(fuuro.fuuro_num() != 0) return false;
    bool gt1 = false, is9 = false;
    int base = 0;
    bool find_base = false;
    for(; base<30; base+=10){
        if(hand[base+1] != 0){
            find_base = true;
            break;
        }
    }
    if(!find_base) return false;
    int j = base+1;
    if(hand[j]<3) return false;
    if(hand[j]>3){
        gt1 = true;
        if(rong_which == j)
            is9 = true;
    }
    for(j++;j < base+9;j++){
        if(hand[j] < 1)
            return false;
        if(hand[j] > 1){
            gt1 = true;
            if(rong_which == j)
                is9 = true;
        }
    }
    if(hand[j]<3) return false;
    if(hand[j]>3){
        gt1 = true;
        if(rong_which == j)
            is9 = true;
    }
    if(gt1) return is9? 2:1;
    else return 0;
}
int MJCore::judge_ryuuiisou() const{
    // 绿一色 all green
    for(int i=0; i<=Red; i++){
        if(hand[i]>0 && // 不是0而且不绿
        std::find(greens.cbegin(), greens.cend(), i)==greens.cend()){
            return false;
        }
    }
    return true;
}
int MJCore::judge_tinroutou() const {
    // 清老头
    // 不检查是否胡牌，不检查手牌数量是否合法
    for(int i=0; i<=Red; i++){
        if(hand[i]>0 && // 不是0而且不老头
            std::find(terminals.cbegin(), terminals.cend(), i)==terminals.cend()){
            return false;
        }
    }
    return true;
}
int MJCore::judge_daisuusii() const {
    // 大四喜
    // 不检查是否胡牌，不检查手牌数量是否合法
    return (hand[East]>=3 && hand[South]>=3 &&
    hand[West] >= 3 && hand[North] >= 3) ? 2:0;
}
int MJCore::judge_syousuusii() const {
    // 小四喜
    // 不检查是否胡牌，不检查手牌数量是否合法
    // 如果是大四喜，return false
    int num_pair=0;
    if(hand[East]<2||hand[South]<2||
        hand[West]<2||hand[North]<2)
        return false;
    return (hand[East] == 2) + (hand[South] == 2)
    + (hand[West] == 2) + (hand[North] == 2) == 1;
}
int MJCore::judge_suuankouu(const std::multiset<seq_t>& raw_hand_seq) const {
    // 四暗刻
    // 不检查是否胡牌，不检查手牌数量是否合法
    // 不检查荣和，但是检查门清
    if(!fuuro.concealed_hand()) return 0;
    bool tanki = false; // 单骑
    for(seq_t x: raw_hand_seq){
        if(is_straight(x)) return 0;
        if(is_pair(x)){
            tanki = seq_to_tile(x)[0] == rong_which;
        }
    }
    for(seq_t x: fuuro.sequences){
        if(is_straight(x)) return 0;
    }
    if(tanki) return 2;
    else return tumo ? 1:0;
}
int MJCore::judge_suukantu() const {
    // 四杠子
    // 不检查是否胡牌，不检查手牌数量是否合法
    return fuuro.minka_seq.size() + fuuro.anka_seq.size() == 4;
}

int MJCore::judge_haku() const {
    return (hand[White] >= 3) ? 1:0;
}
int MJCore::judge_hatu() const {
    return (hand[Green] >= 3) ? 1:0;
}
int MJCore::judge_tyun() const {
    return (hand[Red] >= 3) ? 1:0;
}
int MJCore::judge_pinfu(const std::multiset<seq_t>& raw_hand_seq) const {
    // 平胡
    // 不检查是否胡牌，不检查手牌数量是否合法
    // 不检查荣和，检查役牌
    if(!fuuro.concealed_hand()) return 0; // 门清限定
    int mid_tile = 0; // 坎张
    for(seq_t x:raw_hand_seq){
        if(is_triplet(x)) return 0; // 刻子
        else if(is_pair(x)){ // 对子
            if(judge_yaku_pair(x))
                return 0;
            if(seq_to_tile(x)[0] == rong_which)
                return 0; // 单骑
        }
        else{
            // 顺子
            auto seq = seq_to_tile(x);
            if(seq[1] == rong_which)
                mid_tile++; // 坎张
        }
    }
    if(mid_tile < raw_hand[rong_which])
        return 1;
    else
        return 0;
}
int MJCore::judge_iipeikou(const std::multiset<seq_t> & raw_hand_seq) const {
    if(!fuuro.concealed_hand()) return 0;// 门清限定
    std::vector<seq_t> seq_pool = {};
    bool exist_same = false;
    for(seq_t x: raw_hand_seq){
        // 顺子
        if(std::find(seq_pool.cbegin(), seq_pool.cend(), x)!=seq_pool.cend())
            exist_same = true;
        else
            seq_pool.push_back(x);
    }
    if(!exist_same) return 0;
    return judge_ryanpeikou(raw_hand_seq) ? 0 : 1;
}
int MJCore::judge_ittuu(const std::multiset<seq_t> & raw_hand_seq) const {
    // 一气通贯 123 456 789
    bool ittuu = false;
    std::vector<seq_t> seq_pool = {};
    for(seq_t x: raw_hand_seq){
        if(is_straight(x)){
            seq_pool.push_back(x);
        }
    }
    for(seq_t x: fuuro.sequences){
        if(is_straight(x)){
            seq_pool.push_back(x);
        }
    }
    std::sort(seq_pool.begin(), seq_pool.end());
    if(seq_pool.size()==3){
        ittuu = (seq_pool[1]-seq_pool[0]==M456-M123) &&
                (seq_pool[2]-seq_pool[1]==M456-M123);
    } else if(seq_pool.size()==4){
        ittuu = (seq_pool[1]-seq_pool[0]==M456-M123) &&
                (seq_pool[2]-seq_pool[1]==M456-M123);
        ittuu = ittuu || ((seq_pool[2]-seq_pool[1]==M456-M123) &&
                (seq_pool[3]-seq_pool[2]==M456-M123));
    }
    if(ittuu) return fuuro.concealed_hand() ? 2:1;
    else return 0;
}
int MJCore::judge_sansyokudonjyun(const std::multiset<seq_t> & raw_hand_seq) const {
    // 三色同顺
    bool sansyokudonjyun = false;
    std::vector<seq_t> seq_pool = {};
    for(seq_t x: raw_hand_seq){
        if(is_straight(x)){
            seq_pool.push_back(x);
        }
    }
    for(seq_t x: fuuro.sequences){
        if(is_straight(x)){
            seq_pool.push_back(x);
        }
    }
    std::sort(seq_pool.begin(), seq_pool.end());
    if(seq_pool.size()==3){
        sansyokudonjyun = (seq_pool[1]-seq_pool[0]==P123-M123) &&
                (seq_pool[2]-seq_pool[1]==P123-M123);
    } else if(seq_pool.size()==4){
        sansyokudonjyun = (seq_pool[1]-seq_pool[0]==P123-M123) &&
                (seq_pool[2]-seq_pool[1]==P123-M123);
        sansyokudonjyun = sansyokudonjyun || ((seq_pool[2]-seq_pool[1]==P123-M123) &&
                (seq_pool[3]-seq_pool[2]==P123-M123));
    }
    if(sansyokudonjyun) return fuuro.concealed_hand() ? 2:1;
    else return 0;
}
int MJCore::judge_tyanta(const std::multiset<seq_t> & raw_hand_seq) const {
    // 全带幺
    bool have_wind = false;
    for(seq_t x: raw_hand_seq){
        if(is_jyuntyanta(x)) continue;
        else if(x>=EEE && x<=RedRRR) have_wind = true;
        else return 0;
    }
    for(seq_t x: fuuro.sequences){
        if(is_jyuntyanta(x)) continue;
        else if(x>=EEE && x<=RedRRR) have_wind = true;
        else return 0;
    }
    if(have_wind){
        // 混全
        return fuuro.concealed_hand() ? 2:1;
    }
    else{
        // 纯全
        return fuuro.concealed_hand() ? 3:2;
    }
}
int MJCore::judge_toitoi(const std::multiset<seq_t> & raw_hand_seq) const {
    for(seq_t x: raw_hand_seq){
        if(is_straight(x)) return 0;
    }
    for(seq_t x: fuuro.sequences){
        if(is_straight(x)) return 0;
    }
    return 2;
}
int MJCore::judge_sansyokudoukou(const std::multiset<seq_t> & raw_hand_seq) const {
    // 三色同刻
    bool sansyokudoukou = false;
    std::vector<seq_t> seq_pool = {};
    for(seq_t x: raw_hand_seq){
        if(x<EEE && is_triplet(x)){
            if(x%(P111-M111) >= M1111){
                x = static_cast<seq_t>(x - static_cast<seq_t>(M1111-M111));
            }// convert 杠子
            seq_pool.push_back(x);
        }
    }
    for(seq_t x: fuuro.sequences){
        if(x<EEE && is_triplet(x)){
            if(x%(P111-M111) >= M1111){
                x = static_cast<seq_t>(x - static_cast<seq_t>(M1111-M111));
            }// convert 杠子
            seq_pool.push_back(x);
        }
    }
    std::sort(seq_pool.begin(), seq_pool.end());
    if(seq_pool.size()==3){
        sansyokudoukou = (seq_pool[1]-seq_pool[0]==P111-M111) &&
                (seq_pool[2]-seq_pool[1]==P111-M111);
    } else if(seq_pool.size()==4){
        sansyokudoukou = (seq_pool[1]-seq_pool[0]==P111-M111) &&
                (seq_pool[2]-seq_pool[1]==P111-M111);
        sansyokudoukou = sansyokudoukou || ((seq_pool[2]-seq_pool[1]==P111-M111) &&
                (seq_pool[3]-seq_pool[2]==P111-M111));
    }
    if(sansyokudoukou) return fuuro.concealed_hand() ? 2:1;
    else return 0;
}
int MJCore::judge_ryanpeikou(const std::multiset<seq_t> & raw_hand_seq) const {
    // 两杯口
    if(!fuuro.concealed_hand()) return 0;
    std::vector<seq_t> seq_pool = {};
    for(seq_t x: raw_hand_seq){
        if(is_straight(x)){
            seq_pool.push_back(x);
        }
        else if(is_triplet(x)){
            return 0;
        }
    }
    std::sort(seq_pool.begin(), seq_pool.end());
#ifdef DEBUG
    if(seq_pool.size()!=4){
        DEBUG;
    }
#endif
    // 由于前面七对子已经有2番了，因此这里两杯口只算1番
    return seq_pool[0] == seq_pool[1] && seq_pool[2] == seq_pool[3];
}
int MJCore::judge_sanankou(const std::multiset<seq_t> & raw_hand_seq) const {
    int ankou = 0;
    for(seq_t x: raw_hand_seq){
        if(is_triplet(x)) ankou++;
    }
    ankou += fuuro.anka_seq.size();
    return ankou == 3? 2: 0;
}
int MJCore::judge_tiitoitu() const {
    // 七对子
    // 由于是特殊胡牌方式，因此检查是否胡牌
    // 注意，龙七对是不算七对子的
    // 如果是两杯口，那么也返回true（即使两杯口不算七对子）
    if(fuuro.fuuro_num() > 0)
        return 0;
    int pair_num = 0;
    for(int i=1; i<37; i++){
        if(i%10==0) i++;
        switch (hand[i]) {
            case 0:
                continue;
                break;
            case 2:
                pair_num++;
                break;
            default:
                return 0;
        }
    }
    return pair_num == 7 ? 2 : 0;
}


int MJCore::count_dora() const {
    int doras = 0;
    for(int i=1; i<=Red; i++){
        if(i%10 == 0 && hand[i]!=0){
            doras ++;
        }
        doras += hand[i] * dora[i];
    }
    return doras;
}

const std::map<uint32_t, std::set<std::tuple<std::multiset<mjenum::pure_num_t>, bool>>> number_map = mjenum::load_num_map();
const std::map<uint32_t, std::set<std::tuple<std::multiset<mjenum::pure_wind_t>, bool>>> character_map = mjenum::load_wind_map();

MJCore::MJCore() {}
void MJCore::set_hand(const hand_t &h) {
    hand = h;
    raw_hand = h;
}
void MJCore::clear() noexcept {
    hand.fill(0);
    raw_hand.fill(0);
    dora.fill(0);
    jikazi = East;
    bakazi = East;
    riichi_state = false;
    fuuro.clear();
    tumo = false;
    rong_which = static_cast<tile_t>(0);
}
int MJCore::calc_point(const std::multiset<seq_t>& raw_hand_seq) const {
    // 是否胡牌，如果胡牌则计算番数,否则 return 0
    return 1;
}

void MJCore::set_jikazi(tile_t j){
    jikazi = j;
}
void MJCore::set_bakazi(tile_t b){
    bakazi = b;
}

void MJCore::dfs(tile_t last_tile, int depth) {
    if(depth >= MAX_DEPTH) return;
    int syanten_num = syanten::get_syanten(raw_hand, fuuro.fuuro_num());
//    std::cout << syanten_num << std::endl;
    if(syanten_num == -1){
        auto seqs_op = parse_raw_hand(raw_hand);
        if(!seqs_op.has_value()){
            std::cerr << "conflict occurs between syanten model and MJCore" << std::endl;
            std::cerr << "hand = \n" << raw_hand << std::endl;
            exit(1);
        }
        auto seqs = seqs_op.value();
        int max_score = -10;
        for(const auto& raw_hand_seq: seqs){
            max_score = std::max(max_score, calc_point(raw_hand_seq));
        }
//        std::cout << "depth = " << depth << ", score = " << max_score << std::endl;
    } else{// 胡了的牌就不参与了
        if(syanten_num+1 +depth < MAX_DEPTH)
        for(int i=M1; i<=Red;i++){
            if(i%10==0||raw_hand[i]==0||i==last_tile) continue;
            raw_hand[i]--; hand[i]--;
            for(int j=M1; j<=Red;j++){
                if(j%10==0||j==i||hand[j]==4) continue;
                raw_hand[j]++; hand[j]++;
                dfs(static_cast<tile_t>(j), depth+1);
                raw_hand[j]--; hand[j]--;
            }
            raw_hand[i]++; hand[i]++;
        }
    }
}


//std::array<std::array< hand_t , 7>, 4> MJCore::search() const{
//    // use bfs
//    std::queue<hand_t> current_queue;
//    std::queue<hand_t> next_queue;
//    current_queue.push(raw_hand);
//    // std::set<hand_t> hand_pool;
//    const int max_depth=4;
//    for(int depth=0;depth<max_depth;depth++){
//        int max_score = -1;
//        while (!current_queue.empty()){
//            hand_t h = std::move(current_queue.front());
//            current_queue.pop();
//            auto op_raw_hand_seq = parse_raw_hand(h);
//            if(op_raw_hand_seq.has_value()) {
//                auto raw_hand_seqs = op_raw_hand_seq.value();
//                for(const auto& raw_hand_seq: raw_hand_seqs){
//                    max_score = std::max(max_score, calc_point(raw_hand_seq));
//                }
//            }
//            for(int i=1; i<=Red;i++){
//                if(i%10==0) continue;
//                if(h[i]<1) continue;
//
//                h[i]--;
//                for(int base=0;base<25; base += 10){
//                    int sum_near = h[base+1]+h[base+2]+h[base+3];
//                    for(int j=base+1; j<=base+9;j++){
//                        if(i!=j){
//                            if(depth == 0 || (depth>0 && sum_near>0)){
//                                h[j]++;
//                                next_queue.push(h);
//                                h[j]--;
//                            }
//                        }
//                        if(j%10>=3) sum_near -= h[j-2];
//                        if(j%10<=6) sum_near += h[j+3];
//                    }
//                }
//                for(int j=East; j<= Red;j++){
//                    if(i!=j){
//                        if(depth<=1 ||(depth>1 && h[j]>0)){
//                            h[j]++;
//                            next_queue.push(h);
//                            h[j]--;
//                        }
//                    }
//                }
//                h[i]++;
//            }
//        }
//        std::cout << "next_queue.size = " << next_queue.size() << std::endl;
//        std::swap(current_queue, next_queue);
//        std::cout << "depth = " << depth << ", max-score = " << max_score << std::endl;
//    }
//    // TODO:
//    return {};
//}

bool MJCore::can_chi(tile_t t) const {
    if(t>=East) return false;
    int x = t%(P1-M1);
    if(x == RED_M5){
        x += (M5-RED_M5);
        t = static_cast<tile_t>(static_cast<int>(t) + static_cast<int>(M5-RED_M5));
    }
    if(x<M8 && raw_hand[t+1]>0&& raw_hand[t+2]>0) return true;
    if(x>M2 && raw_hand[t-1]>0&& raw_hand[t-2]>0) return true;
    if(x>M1 && x<M9 && raw_hand[t-1]>0&& raw_hand[t+1]>0) return true;
    return false;
}
bool MJCore::can_pong(tile_t t) const {
    if(t==RED_M5 || t==RED_P5 || t==RED_S5){
        t = static_cast<tile_t>(static_cast<int>(t) + static_cast<int>(M5-RED_M5));
    }
    return raw_hand[t] >= 2;
}
bool MJCore::can_min_kang(tile_t t) const {
    if(t==RED_M5 || t==RED_P5 || t==RED_S5){
        t = static_cast<tile_t>(static_cast<int>(t) + static_cast<int>(M5-RED_M5));
    }
    return raw_hand[t] >= 3;
}
bool MJCore::can_an_kang(tile_t t) const {
    if(t==RED_M5 || t==RED_P5 || t==RED_S5){
        t = static_cast<tile_t>(static_cast<int>(t) + static_cast<int>(M5-RED_M5));
    }
    return raw_hand[t] >= 3;
}
bool MJCore::can_add_kang(tile_t t) const {
    if(t==RED_M5 || t==RED_P5 || t==RED_S5){
        t = static_cast<tile_t>(static_cast<int>(t) + static_cast<int>(M5-RED_M5));
    }
    seq_t x = tile_to_triplet(t);
    if(fuuro.sequences.find(x) != fuuro.sequences.cend())
        return true;
    else
        return false;
}
std::optional<std::vector<std::multiset<seq_t>>> parse_raw_hand(const hand_t& raw_hand) {
//    std::cout << "=====raw_hand=====\n" << raw_hand <<std::endl;
    auto[a_idx, b_idx, c_idx, d_idx] = mjenum::hand_to_index(raw_hand);
    auto a_iter = number_map.find(a_idx);
    if(a_iter == number_map.cend()) return {};
    auto b_iter = number_map.find(b_idx);
    if(b_iter == number_map.cend()) return {};
    auto c_iter = number_map.find(c_idx);
    if(c_iter == number_map.cend()) return {};
    auto d_iter = character_map.find(d_idx);
    if(d_iter == character_map.cend()) return {};
    const auto& a = a_iter->second;
    const auto& b = b_iter->second;
    const auto& c = c_iter->second;
    const auto& d = d_iter->second;
    std::vector<std::multiset<seq_t>> result;
    for(const auto& a_i: a){
        const auto& [a_pure_seq, a_have_pair] = a_i;
        for(const auto& b_i: b){
            const auto& [b_pure_seq, b_have_pair] = b_i;
            for(const auto& c_i: c){
                const auto& [c_pure_seq, c_have_pair] = c_i;
                for(const auto& d_i: d){
                    const auto& [d_pure_seq, d_have_pair] = d_i;
                    if(a_have_pair+b_have_pair+c_have_pair+d_have_pair!=1)
                        continue;
                    std::multiset<seq_t> new_result;
                    // pure_seq to seq!
                    new_result.merge(move(mjenum::pure_num_to_seq(a_pure_seq, 0)));
                    new_result.merge(move(mjenum::pure_num_to_seq(b_pure_seq, 1)));
                    new_result.merge(move(mjenum::pure_num_to_seq(c_pure_seq, 2)));
                    new_result.merge(move(mjenum::pure_wind_to_seq(d_pure_seq)));
                    result.push_back(move(new_result));
                }
            }
        }
    }
    if(result.empty()) return {};
    else return result;
}
std::ostream& operator<<(std::ostream& os, const std::multiset<seq_t>& seqs){
    os << '[';
    for(const auto& seq: seqs){
        os << seq_to_string(seq) << ", ";
    }
    os << ']';
    return os;
}
