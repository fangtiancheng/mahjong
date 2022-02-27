//#include <torch/torch.h>
//#include "model.hpp"
#include "mjscore.h"
#include "dfs.h"
#include <iostream>
const int typeCount = 38;
const int typeCount2 = 41;
const int doraCount = 10;
int hand[typeCount];
int hand2[typeCount2];
int fuuro[20];
int dora[doraCount + 1];
MJSearch mjscore;
void initMjscore() {
    mjscore.Avail_Akahai(true);
    mjscore.Avail_Kuitan(true);
    mjscore.Avail_ManganKiriage(true);
    mjscore.Avail_Ba1500(false);
    mjscore.Avail_DoubleKokushi13(true);
    mjscore.Avail_DoubleTyuuren9(true);
    mjscore.Avail_DoubleDaisuusii(true);
    mjscore.Avail_DoubleSuttan(true);

    mjscore.Is_Riichi(false);
    mjscore.Is_Tenhou(false);
    mjscore.Is_Tiihou(false);
    mjscore.Is_DoubleRiichi(false);
    mjscore.Is_Ippatu(false);
    mjscore.Is_Tyankan(false);
    mjscore.Is_Rinsyan(false);
    mjscore.Is_NagashiMangan(false);
    mjscore.Is_Haitei(false);
}
int parseFuuroType(const string& fuuroType) {
    if (fuuroType == "chii") {
        return MJScore::CHII;
    }
    else if (fuuroType == "pon") {
        return MJScore::PON;
    }
    else if (fuuroType == "minkan") {
        return MJScore::MINKAN;
    }
    else if (fuuroType == "ankan") {
        return MJScore::ANKAN;
    }
    else if (fuuroType == "kakan") {
        return MJScore::KAKAN;
    }
    else if (fuuroType == "aka_chii") {
        return MJScore::AKA_CHII;
    }
    else if (fuuroType == "aka_pon1") {
        return MJScore::AKA_PON1;
    }
    throw std::runtime_error("unknown fuuro type!");
}
void handleMjscore() {
    mjscore.Clear_WithoutRule();
    memset(hand2, 0, sizeof(hand2));
    memset(fuuro, 0, sizeof(fuuro));
    memset(dora, 0, sizeof(dora));

    for (int i = 0; i < typeCount2; i++) {
        cin >> hand2[i];
        cout << "read " << hand2[i] << endl;
    }
    mjscore.Set_Tehai(hand2);

    int lastTile;
    cin >> lastTile;
    cout << "lastTile = " << lastTile << endl;
    mjscore.Set_Agarihai(lastTile);

    int direction;
    cin >> direction;
    mjscore.Set_Bakaze(direction);
    cin >> direction;
    mjscore.Set_Jikaze(direction);

    int fuuroCount;
    cin >> fuuroCount;
    cout << "fuuroCount = " << fuuroCount << endl;
    for (int i = 0; i < fuuroCount; i++) {
        string fuuroType;
        cin >> fuuroType;
        fuuro[i * 4] = parseFuuroType(fuuroType);
        cin >> fuuro[i * 4 + 1];
    }
    mjscore.Set_Fuuro(fuuro);

    for (int i = 1; i <= doraCount; i++) {
        cin >> dora[i];
    }
    mjscore.Set_Dora(dora);

    int isRiichi;
    cin >> isRiichi;
    mjscore.Is_Riichi(isRiichi);

    int tsumoAgari;
    cin >> tsumoAgari;
    mjscore.Set_Tumoagari(tsumoAgari);

    int isLastTile;
    cin >> isLastTile;
    mjscore.Is_Haitei(isLastTile);
    auto x = mjscore.Get_Search();
    for(int i=1; i < 38;i++){
        if(i%10==0) continue;
        for(int d = 0; d<x[i].size(); d++){
            if(x[i][d] != 0){
                cout << "depth = " << d << ", fan = "<< x[i][d] << endl;
            }
        }
    }
//    mjscore.Run();
//    cout <<
//    (mjscore.Get_ErrorCode() != 0 ? 0 :
//    direction == 31 && tsumoAgari ? mjscore.Get_OyaTumo() * 3 :
//    direction == 31 ? mjscore.Get_OyaRon() :
//    tsumoAgari ? mjscore.Get_KoTumoKo() * 2 + mjscore.Get_KoTumoOya() :
//    mjscore.Get_KoRon()) <<
//    endl;
//    cout << mjscore.Get_Fan() << endl;
}
int main() {
    initMjscore();
    handleMjscore();
    return 0;
}