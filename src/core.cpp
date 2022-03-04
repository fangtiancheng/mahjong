#include "core.h"
bool MJCore::judge_yaku_pair(seq_t x) const {

}

bool MJCore::judge_kokusi13() const {
    // 国士无双 13orphans
    // 检查是否胡牌(非常规胡法)，但是不检查手牌数量是否合法
    if(fuuro.fuuro_num()!=0) return false;
    bool gt1 = false;// great than 1
    for(int i: orphans){
        if(hand[i] < 1) return false;
        if(hand[i] > 1) gt1 = true;
    }
    return gt1;
}

bool MJCore::judge_tuuiisou() const {
    // 字一色 all honor tiles
    // 不检查是否胡牌，不检查手牌数量是否合法
    for(int i=0; i<East; i++){
        if(hand[i] > 0)
            return false;
    }
    return true;
}

bool MJCore::judge_daisangen() const {
    // 大三元
    // 不检查是否胡牌，不检查手牌数量是否合法
    return (hand[tile_t::White]>=3) &&
    (hand[tile_t::Green]>=3) &&
    (hand[tile_t::Red]>=3);
}
bool MJCore::judge_tyuuren9() const {
    // 九莲宝灯
    // 不检查是否胡牌，不检查手牌数量是否合法
    // 虽然 [S: 1112345678999 P: 2]也返回true
    // 但是这种方法一定过不了胡牌，所以没事
    if(fuuro.fuuro_num() != 0) return false;
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
    for(j++;j < base+9;j++){
        if(hand[j] < 1)
            return false;
    }
    if(hand[j]<3) return false;
    return true;
}
bool MJCore::judge_ryuuiisou() const{
    // 绿一色 all green
    for(int i=0; i<=Red; i++){
        if(hand[i]>0 && // 不是0而且不绿
        std::find(greens.cbegin(), greens.cend(), i)==greens.cend()){
            return false;
        }
    }
    return true;
}

bool MJCore::judge_tinroutou() const {
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

bool MJCore::judge_daisuusii() const {
    // 大四喜
    // 不检查是否胡牌，不检查手牌数量是否合法
    return hand[East]>=3 && hand[South]>=3 &&
    hand[West] >= 3 && hand[North] >= 3;
}

bool MJCore::judge_syousuusii() const {
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

bool MJCore::judge_suuankouu(const std::multiset<seq_t>& raw_hand_seq) const {
    // 四暗刻
    // 不检查是否胡牌，不检查手牌数量是否合法
    // 不检查荣和，但是检查门清
    if(!fuuro.concealed_hand()) return false;
    for(seq_t x: raw_hand_seq){
        if(is_straight(x)) return false;
    }
    for(seq_t x: fuuro.sequences){
        if(is_straight(x)) return false;
    }
    return true;
}

bool MJCore::judge_suukantu() const {
    // 四杠子
    // 不检查是否胡牌，不检查手牌数量是否合法
    return fuuro.minka_seq.size() + fuuro.anka_seq.size() == 4;
}

bool MJCore::judge_pinfu(const std::multiset<seq_t>& raw_hand_seq) const {
    // 平胡
    // 不检查是否胡牌，不检查手牌数量是否合法
    // 不检查荣和，检查役牌
    if(!fuuro.concealed_hand()) return false; // 门清限定
    for(seq_t x:raw_hand_seq){
        if(is_triplet(x)) return false;
    }
    return true;
}

bool MJCore::judge_tiitoitu() const {
    // 七对子
    // 由于是特殊胡牌方式，因此检查是否胡牌
    if(fuuro.fuuro_num() > 0)
        return false;
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
                return false;
        }
    }
    return pair_num == 7;
}

//hand_t MJCore::get_raw_hand() const {
//    if(fuuro.fuuro_num() == 0) return hand;
//    // handle red dora
//    // TODO:
//
//}

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

std::map<uint32_t, std::set<std::tuple<std::multiset<mjenum::pure_num_t>, bool>>> MJCore::number_map = mjenum::load_num_map();
std::map<uint32_t, std::set<std::tuple<std::multiset<mjenum::pure_wind_t>, bool>>> MJCore::character_map = mjenum::load_wind_map();

MJCore::MJCore() {}
std::optional<int> MJCore::calc_point() const{
    // 是否胡牌，如果胡牌则计算番数

    // 去掉副露
    int seq_to_find = 4 - fuuro.fuuro_num();
//    hand_t raw_hand = get_raw_hand();
    // 非常规型，寻找国士无双和七对子
    if(judge_kokusi13())
        return 13;
    bool is_tiitiotu, is_ryanpeikou;
    std::tie(is_tiitiotu, is_ryanpeikou) = judge_tiitoitu();
    if(is_tiitiotu){
        if(judge_tuuiisou()) return 13; // 大七星
        // TODO:
    }
    // 找孤立张
    bool paired = false; // 是否有雀头
    for(int i=tile_t::East; i<=tile_t::Red; i++){
        if(raw_hand[i] > 0){
            // TODO:
        }
    }
    // 先找役满
    {
        if(judge_tyuuren9()) return 13;
        int x = judge_daisangen() + judge_ryuuiisou() + judge_tinroutou() +
                judge_daisuusii() + judge_syousuusii() + judge_suuankouu() +
                judge_suukantu();
        if(x!=0) return 13*x;
    }
    // 再找常规役
}

void MJCore::set_jikazi(tile_t j){
    jikazi = j;
}
void MJCore::set_bakazi(tile_t b){
    bakazi = b;
}

std::array<std::array< hand_t , 7>, 4> MJCore::search() const{

}

std::optional<std::vector<std::multiset<seq_t>>> MJCore::parse_raw_hand() const{
//    hand_t raw_hand = move(get_raw_hand());
    auto[a_idx, b_idx, c_idx, d_idx] = mjenum::hand_to_index(raw_hand);
    auto a_iter = MJCore::number_map.find(a_idx);
    if(a_iter == MJCore::number_map.cend()) return {};
    auto b_iter = MJCore::number_map.find(b_idx);
    if(b_iter == MJCore::number_map.cend()) return {};
    auto c_iter = MJCore::number_map.find(c_idx);
    if(c_iter == MJCore::number_map.cend()) return {};
    auto d_iter = MJCore::character_map.find(d_idx);
    if(d_iter == MJCore::character_map.cend()) return {};
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