#include "core.h"
int MJCore::tiles_in_hands() const {
    int sum = 0;
    for(int i=1; i<37; i++){
        if(i%10 == 0) i++;
        sum += hand[i];
    }
    return sum - fuuro_num*3 - (anka_num + minka_num);
}

bool MJCore::judge_kokusi13() const {
    // 国士无双 13orphans
    // 检查是否胡牌(非常规胡法)，但是不检查手牌数量是否合法
    if(fuuro_num!=0) return false;
    for(int i=0; i < 30; i++){
        int res = i%10;
        if(res == 1|| res == 9)
            continue;
        if(hand[i] != 0)
            return false;
    }
    for(int i: orphans){
        if(hand[i] < 1) return false;
    }
    return true;
}

bool MJCore::judge_tuuiisou() const {
    // 字一色 all honor tiles
    // 不检查是否胡牌，不检查手牌数量是否合法
    for(int i=0; i<30; i++){
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
    if(fuuro_num != 0) return false;
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
    for(int i=0; i<37; i++){
        if(hand[i] != 0 && greens.find(i) != greens.cend()){
            return false;
        }
    }
    return true;
}

bool MJCore::judge_tinroutou() const {
    // 清老头
    // 不检查是否胡牌，不检查手牌数量是否合法
    for(int i=0; i<37; i++){
        if(hand[i]!=0 && terminals.find(i) != terminals.cend()){
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

bool MJCore::judge_suuankouu() const {
    // 四暗刻
    // 不检查是否胡牌，不检查手牌数量是否合法
    // 不检查荣和，但是检查门清
    if(!judge_concealed_hand()) return false;
    int seq_num = 0;
    for(int i=1; i<37; i++){
        if(hand[i] >= 3){
            seq_num++;
        }
    }
    return seq_num == 4;
}

bool MJCore::judge_suukantu() const {
    // 四杠子
    // 不检查是否胡牌，不检查手牌数量是否合法
    return minka_num + anka_num == 4;
}

bool MJCore::judge_pinfu() const {
    // 平胡
    // 不检查是否胡牌，不检查手牌数量是否合法
    // 不检查荣和

}

hand_t MJCore::get_raw_hand() const {
    if(fuuro_num == 0) return hand;
    // handle red dora
    hand_t raw_hand = hand;
    for(int red_dora = RED_M5; red_dora <= RED_S5; red_dora += 10){
        if(fuuro[red_dora] > 0)
            raw_hand[red_dora] = 0;
    }
    int res_fuuro_num = fuuro_num;
    for(int i=1; i<37; i++){
        if(i%10==0) i++; // skip red dora
        if(fuuro[i]>0){
            if(raw_hand[i+21] > 0){
                raw_hand[i] -= 4;
            } else{
                raw_hand[i] -= 3;
            }
            res_fuuro_num--;
            if(res_fuuro_num==0)
                return raw_hand;
        }
    }
    for(int i=37; i<37+21; i++){
        if(fuuro[i] > 0){
            int a, b, c;
            std::tie(a, b, c) = id_to_seq[i];
            raw_hand[a] -= fuuro[i];
            raw_hand[b] -= fuuro[i];
            raw_hand[c] -= fuuro[i];
            res_fuuro_num--;
            if(res_fuuro_num==0)
                return raw_hand;
        }
    }
    return raw_hand;
}

int MJCore::count_dora() const {
    int doras = 0;
    for(int i=1; i<37; i++){
        if(i%10 == 0){
            doras += hand[i];
        }
        if(dora[i])
            doras += hand[i];
    }
    return doras;
}

MJCore::MJCore() {}
std::optional<int> MJCore::calc_point() const{
    // 是否胡牌，如果胡牌则计算番数

    // 去掉副露
    int seq_to_find = 4 - fuuro_num;
    hand_t raw_hand = get_raw_hand();
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