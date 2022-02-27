#include "dfs.h"
void MJSearch::dfs(int depth) {
    if(depth > MAX_DEPTH){
        return;
    }
    for(int i=1; i<38;i++){
        if(i%10 == 0) continue;
        if(Tehai[i]==0 && Tehai[i-1]==0 && Tehai[i+1]==0)
            continue;
        Tehai[i]++;
        for(int j=0; j<38; j++){
            if(j%10 == 0) continue;
            if(i==j) continue;
            Tehai[j]--;
            if(depth==0) Current_Discard=j;
            Set_Agarihai(i);
            Run();
            Search_Result[Current_Discard][depth] = max(
                    Search_Result[Current_Discard][depth], Get_Fan());
            dfs(depth+1);
        }
    }
}

MJSearch::MJSearch():MJScore() {

}
array<array<int, MJSearch::MAX_DEPTH>, 41> MJSearch::Get_Search() {
    // init
    Search_Result = {{0}};
    // record
    int Current_Tehai[50], Current_Agarihai;
    Current_Agarihai = Agarihai;
    memcpy(Current_Tehai, Tehai, sizeof(Tehai));
    dfs(0);
    memcpy(Tehai, Current_Tehai, sizeof(Tehai));
    Agarihai = Current_Agarihai;
    return Search_Result;
}