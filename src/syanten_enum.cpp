#include "syanten_enum.h"
namespace syanten{
    using namespace mjenum;

    //コンストラクタ
    std::map<uint32_t, std::tuple<int, int, int, int>> load_syanten_map(){
        //シャンテンファイル読み込み
        std::map<uint32_t, std::tuple<int, int, int, int>> result = {};
        std::ifstream ifs("mj_syanten.dat", std::ios::in);
        std::string str;
        if(ifs.fail()) {
            std::cerr << "open mj_syanten.dat error" << std::endl;
            exit(0);
        }

        while(getline(ifs, str)) {
            int pattern1_m, pattern1_t, pattern2_m, pattern2_t;
            auto splited_str = split(str, " \r\n");
            if(splited_str.size()==0) continue;
            if(splited_str.size()!=5){
                std::cerr<<"mj_syanten.dat format error" << std::endl;
                exit(1);
            }
            uint32_t key = hand_encoder(hand_parser<pure_num_t>(splited_str[0]));
            auto value = std::make_tuple(
                    std::stoi(splited_str[1]), std::stoi(splited_str[2]),
                    std::stoi(splited_str[3]), std::stoi(splited_str[4]));
            result[key] = value;
        }
        return std::move(result);
    }

    //国士シャンテン
    int KokusiSyanten(hand_t& raw_hand)
    {
        int kokusi_toitu=0, syanten_kokusi=13;
        //老頭牌
        for(int i=1;i<30;i++){
            if(i%10==1||i%10==9||i%20==1||i%20==9){
                if(raw_hand[i])
                    syanten_kokusi--;
                if(raw_hand[i] >=2 && kokusi_toitu==0)
                    kokusi_toitu=1;
            }
        }
        //字牌
        for(int i=East;i<=Red;i++){
            if(raw_hand[i]){
                syanten_kokusi--;
                if(raw_hand[i] >=2 && kokusi_toitu==0)
                    kokusi_toitu=1;
            }
        }
        //頭
        syanten_kokusi-= kokusi_toitu;
        return syanten_kokusi;
    }

    //チートイシャンテン
    int TiitoituSyanten(hand_t& raw_hand){
        int toitu=0,syurui=0,syanten_tiitoi;
        //トイツ数を数える
        for(int i=M1;i<=Red;i++){
            if(i%10==0) continue;
            while(i<=Red && raw_hand[i]==0)
                i++;
            if(i>Red) break;
            syurui++;
            if(raw_hand[i] >=2)
                toitu++;
        }
        syanten_tiitoi=6-toitu;
        //４枚持ちを考慮
        if(syurui<7)
            syanten_tiitoi+= 7-syurui;
        return syanten_tiitoi;
    }

    //通常手シャンテン
    int NormalSyanten(hand_t& raw_hand, int fuuro_num){
        int result=14;
        int tmpresult=0;
        for(int i=M1;i<=Red;i++) {
            //頭抜き出し
            if(i%10==0) continue;
            if(2 <= raw_hand[i])
            {
                raw_hand[i] -= 2;
                tmpresult = _checkNormalSyanten(raw_hand, fuuro_num)-1;
                if(tmpresult < result){
                    result=tmpresult;
                }
                raw_hand[i] += 2;
            }
        }

        tmpresult = _checkNormalSyanten(raw_hand, fuuro_num);   //頭無しと仮定して計算
        if(tmpresult < result){
            result=tmpresult;
        }

        return result;
    }

    //Checkシャンテン
    int _checkNormalSyanten(hand_t& raw_hand, int fuuro_num){
        int ptm=0,ptt=0;
        uint32_t key[4];
        std::tie(key[0],key[1],key[2],key[3]) = mjenum::hand_to_index(raw_hand);
        for(int j=0;j<3;j++){
            auto [pt1m, pt1t, pt2m, pt2t]=syanten_map[key[j]];

            if(pt1m*2+pt1t>=pt2m*2+pt2t){
                ptm+=pt1m;
                ptt+=pt1t;
            }
            else{
                ptm+=pt2m;
                ptt+=pt2t;
            }
        }

        for(int i=East;i<=Red;i++){
            if(raw_hand[i]>=3){
                ptm++; // 面子
            }
            else if(raw_hand[i]>=2){
                ptt++; // 雀头
            }
        }

        while (ptm + ptt > 4 - fuuro_num && ptt > 0) ptt--;
        while (ptm + ptt > 4 - fuuro_num) ptm--;
        return 8-ptm*2-ptt - fuuro_num * 2;
    }

    int get_syanten(hand_t& raw_hand, int fuuro_num){
        // -1 => 可以胡牌
        // 0  => 已经听牌
        // x  => x向听
        int syanten_num = NormalSyanten(raw_hand, fuuro_num);
        if(fuuro_num==0){
            syanten_num = std::min(syanten_num, TiitoituSyanten(raw_hand));
            syanten_num = std::min(syanten_num, KokusiSyanten(raw_hand));
        }
        return syanten_num;
    }
    std::map<uint32_t, std::tuple<int, int, int, int>> syanten_map = load_syanten_map();
}