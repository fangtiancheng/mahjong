#ifndef __CORE__
#define __CORE__
#include "common.h"
#include "mjenum_loader.h"
#include <algorithm>
#include <map>
#include <queue>
std::optional<std::vector<std::multiset<seq_t>>> parse_raw_hand(const hand_t&);
class MJCore{
public:
    // [1 1 1 2 3 4 5 5 6 7 8 9 9 9] => uint32_t => (1 1 1) (2 3 4) (6 7 8) (9 9 9) (5 5)
    static std::map<uint32_t, std::set<std::tuple<std::multiset<mjenum::pure_num_t>, bool>>> number_map;

    // [e e e s s s w w w n n n W W] => uint32_t => (e e e) (s s s) (w w w) (n n n) (W W)
    static std::map<uint32_t, std::set<std::tuple<std::multiset<mjenum::pure_wind_t>, bool>>> character_map;
protected:
    hand_t hand = {}; // 手牌，包括副露，含red dora
    hand_t raw_hand = {}; // 手牌，不包括副露，含red dora
    hand_t dora = {}; // 宝牌，非宝牌指示牌，不含red dora
    tile_t jikazi = East; // 自风
    tile_t bakazi = East; // 场风
    bool riichi_state = false; // 是否已经进入立直状态
    // 副露数量 = 暗杠数量+明杠数量+吃数量+碰数量
    fuuro_t fuuro = {}; // 副露

    // 工具函数
    bool judge_yaku_pair(seq_t x) const; // 判断雀头是否为役牌, for pinfu

    int judge_kokusi() const ; // 国士无双(13面)
    int judge_tuuiisou() const ; // 字一色
    int judge_daisangen() const ; // 大三元
    int judge_tyuuren() const ; // 九莲宝灯(纯正)
    int judge_ryuuiisou() const ; // 绿一色
    int judge_tinroutou() const ; // 清老头
    int judge_daisuusii() const ; // 大四喜
    int judge_syousuusii() const ; // 小四喜
    int judge_suuankouu(const std::multiset<seq_t>&) const ; // 四暗刻(单骑)
    int judge_suukantu() const ; // 四杠子

    int judge_haku() const; // 役牌白
    int judge_hatu() const; // 役牌发
    int judge_tyun() const; // 役牌中
    int judge_pinfu(const std::multiset<seq_t>&) const ; // 平胡
    int judge_iipeikou(const std::multiset<seq_t>&) const; // 一杯口
    int judge_ittuu(const std::multiset<seq_t>&) const; // 一气通贯
    int judge_sansyokudonjyun(const std::multiset<seq_t>&) const; // 三色同顺
    int judge_tyanta(const std::multiset<seq_t>&) const; // 混/纯 全带幺九
    int judge_toitoi(const std::multiset<seq_t>&) const; // 对对
    int judge_sansyokudoukou(const std::multiset<seq_t>& )const; // 三色同刻
    int judge_ryanpeikou(const std::multiset<seq_t>&) const; // 两杯口
    int judge_sanankou(const std::multiset<seq_t>&) const; // 三暗刻
    int judge_tiitoitu() const ; // 七对子
    int count_dora() const ; // 计算宝牌

public:
    MJCore();
    void set_hand(const hand_t&);
    void clear() noexcept ;
    int calc_point(const std::multiset<seq_t>& ) const ;
    void set_jikazi(tile_t);
    void set_bakazi(tile_t);
    std::array<std::array< hand_t , 7>, 4> search() const;

    //
    bool can_chi(tile_t t) const;
    bool can_pong(tile_t t) const;
    bool can_min_kang(tile_t t) const;
    bool can_an_kang(tile_t t) const;
    bool can_add_kang(tile_t t) const;
//    bool can_riichi(tile_t t) const;

    // action
//    bool chi(tile_t t);
//    bool pong(tile_t t);
//    bool min_kang(tile_t t);
//    bool an_kang(tile_t t);
//    bool add_kang(tile_t t);
//    bool discard(tile_t t);
//    bool riichi(tile_t t);

    bool tumo = false;  // 是否为自摸
    tile_t rong_which = static_cast<tile_t>(0); // 最后胡的哪张
};

#endif