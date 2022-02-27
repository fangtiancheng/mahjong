#ifndef __DFS__
#define __DFS__
#include "mjscore.h"
#include <vector>
#include <array>

class MJSearch: public MJScore{
    static const int MAX_DEPTH = 4; // 最多搜到3向听
private:
    void dfs(int depth);
    array<array<int, MJSearch::MAX_DEPTH>, 41> Search_Result;
    int Current_Discard;
    // Search_Result[i][j] => 丢掉i牌在depth=j的情况下胡到的最大番
public:
    enum SCORE_LEVEL{
        SCORE_LV0, // 0 fan
        SCORE_LV1, // 1~3 fan
        SCORE_LV2, // 4~5 fan
        SCORE_LV3, // 6~7 fan
        SCORE_LV4, // 8~10 fan
        SCORE_LV5, // 11~12 fan
        SCORE_LV6, // 13~25 fan
        SCORE_LV7, // 26~inf fan
    };
    MJSearch();
    array<array<int, MAX_DEPTH>, 41> Get_Search();
};
#endif