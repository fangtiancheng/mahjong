#ifndef __CORE__
#define __CORE__
#include "common.h"
class MJCore{
private:
    hand_t hand = {}; // 手牌，包括副露，含red dora
    hand_t dora = {}; // 宝牌，非宝牌指示牌，不含red dora
    tile_t jikazi; // 自风
    tile_t bakazi; // 场风

    // 副露数量 = 暗杠数量+明杠数量+吃数量+碰数量
    fuuro_t fuuro = {}; // 副露


//    int tiles_in_hands() const;
    inline bool judge_concealed_hand() const {
        // 检查是否处于门清状态
        return fuuro.concealed_hand();
    }
    bool judge_kokusi13() const ; // 国士无双 13orphans
    bool judge_tuuiisou() const ; // 字一色
    bool judge_daisangen() const ; // 大三元
    bool judge_tyuuren9() const ; // 九莲宝灯
    bool judge_ryuuiisou() const ; // 绿一色
    bool judge_tinroutou() const ; // 清老头
    bool judge_daisuusii() const ; // 大四喜
    bool judge_syousuusii() const ; // 小四喜
    bool judge_suuankouu() const ; // 四暗刻
    bool judge_suukantu() const ; // 四杠子

    bool judge_pinfu() const ; // 平胡
    std::tuple<bool, bool> judge_tiitoitu() const ; // 七对子 & 两杯口
    hand_t get_raw_hand() const; // 比如手牌是1112345678999,副露是111 999,那么返回2345678
    int count_dora() const ; // 计算宝牌
    static int dfs(hand_t raw_hand, int current_depth){
        for(){
            //检查胡没胡
        }
    }
public:
    MJCore();
    std::optional<int> calc_point() const ;
    void set_jikazi(tile_t);
    void set_bakazi(tile_t);
    std::array<std::array< hand_t , 7>, 4> search() const;
};

#endif