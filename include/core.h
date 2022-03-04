#ifndef __CORE__
#define __CORE__
#include "common.h"
#include "mjenum_loader.h"
#include <algorithm>
#include <map>
class MJCore{
    // [1 1 1 2 3 4 5 5 6 7 8 9 9 9] => uint32_t => (1 1 1) (2 3 4) (6 7 8) (9 9 9) (5 5)
    static std::map<uint32_t, std::set<std::tuple<std::multiset<mjenum::pure_num_t>, bool>>> number_map;

    // [e e e s s s w w w n n n W W] => uint32_t => (e e e) (s s s) (w w w) (n n n) (W W)
    static std::map<uint32_t, std::set<std::tuple<std::multiset<mjenum::pure_wind_t>, bool>>> character_map;
private:
    hand_t hand = {}; // 手牌，包括副露，含red dora
    hand_t raw_hand = {}; // 手牌，不包括副露，含red dora
    hand_t dora = {}; // 宝牌，非宝牌指示牌，不含red dora
    tile_t jikazi; // 自风
    tile_t bakazi; // 场风
    bool riichi_state = false; // 是否已经进入立直状态
    // 副露数量 = 暗杠数量+明杠数量+吃数量+碰数量
    fuuro_t fuuro = {}; // 副露

    bool judge_yaku_pair(seq_t x) const; // 判断雀头是否为役牌
    bool judge_kokusi13() const ; // 国士无双 13orphans
    bool judge_tuuiisou() const ; // 字一色
    bool judge_daisangen() const ; // 大三元
    bool judge_tyuuren9() const ; // 九莲宝灯
    bool judge_ryuuiisou() const ; // 绿一色
    bool judge_tinroutou() const ; // 清老头
    bool judge_daisuusii() const ; // 大四喜
    bool judge_syousuusii() const ; // 小四喜
    bool judge_suuankouu(const std::multiset<seq_t>&) const ; // 四暗刻
    bool judge_suukantu() const ; // 四杠子

    bool judge_pinfu(const std::multiset<seq_t>&) const ; // 平胡
    bool judge_iipeikou(const std::multiset<seq_t>&) const; // 一杯口
    bool judge_ittuu(const std::multiset<seq_t>&) const; // 一气通贯
    bool judge_sansyokudonjyun(const std::multiset<seq_t>&) const; // 三色同顺
    bool judge_tyanta(const std::multiset<seq_t>&) const; // 混全带幺九
    bool judge_jyuntyanta(const std::multiset<seq_t>&) const; // 纯全带幺九
    bool judge_toitoi(const std::multiset<seq_t>&) const; // 对对
    bool judge_sansyokudoukou(const std::multiset<seq_t>& )const; // 三色同刻
    bool judge_ryanpeikou(const std::multiset<seq_t>&) const; // 两杯口
    bool judge_sanankou(const std::multiset<seq_t>&) const; // 三暗刻
    bool judge_tiitoitu() const ; // 七对子
//    hand_t get_raw_hand() const; // 比如手牌是1112345678999,副露是111 999,那么返回2345678
    int count_dora() const ; // 计算宝牌
    static int dfs(hand_t raw_hand, int current_depth){
        return 0;
    }
    std::optional<std::vector<std::multiset<seq_t>>> parse_raw_hand() const;
public:
    MJCore();
    std::optional<int> calc_point() const ;
    void set_jikazi(tile_t);
    void set_bakazi(tile_t);
    std::array<std::array< hand_t , 7>, 4> search() const;

    //
    bool can_chi(tile_t t) const;
    bool can_pong(tile_t t) const;
    bool can_min_kang(tile_t t) const;
    bool can_an_kang(tile_t t) const;
    bool can_add_kang(tile_t t) const;
    bool can_riichi(tile_t t) const;
    // action
    bool chi(tile_t t);
    bool pong(tile_t t);
    bool min_kang(tile_t t);
    bool an_kang(tile_t t);
    bool add_kang(tile_t t);
    bool discard(tile_t t);
    bool riichi(tile_t t);


};

#endif