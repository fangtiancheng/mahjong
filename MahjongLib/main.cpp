#include <cstdlib>
#include <iostream>
#include <ctime>
#include "common.h"
#include "syanten.h"
#include "mjscore.h"
using namespace std;

const int typeCount = 38;
const int typeCount2 = 41;
const int doraCount = 10;

Syanten syanten;
MJScore mjscore;
int hand[typeCount];
int hand2[typeCount2];
int fuuro[20];
int dora[doraCount + 1];

void handleSyanten() {
	memset(hand, 0, sizeof(hand));
	syanten.clear();

	for (int i = 0; i < typeCount; i++) {
		cin >> hand[i];
	}
	syanten.set_tehai(hand);

	int fuurosuu=0;
	// cin >> fuurosuu;
	syanten.set_fuurosuu(fuurosuu);

	int resNormal;
	int res = syanten.AnySyanten(OUT resNormal);
	cout << res << " " << resNormal << endl;
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
}
const int max_depth = 4;
int max_score[max_depth] = {-1, -1, -1, -1};
void dfs(int* hand, int lastTile, int depth){
	if(depth >= max_depth) return;
	syanten.set_tehai(hand);
	int resNormal;
	int res = syanten.AnySyanten(OUT resNormal);
	int error_code = 0;
	// syanten.clear();
	if(res == -1){
		mjscore.Set_Tehai(hand);
		mjscore.Set_Agarihai(lastTile);
		mjscore.Run();
		error_code = mjscore.Get_ErrorCode();
		if(error_code != 0 && error_code != 6){
			cout << "ERROR, code = " << error_code << endl;
		}
		else {
			int score = mjscore.Get_OyaTumo();
			max_score[depth] = max(max_score[depth],score);
			// cout << "depth = " << depth << ", score = " << score << endl;
		}
		// mjscore.Clear();
	}
	if((res != -1 || error_code == 6) && res+1 + depth < max_depth){
		// hand[lastTile]++;
		for(int i=1;i<38;i++){
			if(i%10==0 || hand[i]==0||i==lastTile) continue;
			hand[i]--;
			for(int j=1;j<38;j++){
				if(j%10==0||j==i||hand[j]==4) continue;
				hand[j]++;
				dfs(hand, j, depth+1);
				hand[j]--;
			}
			hand[i]++;
		}
	}
	// cout << res << " " << resNormal << endl;

}
void handleMjscore() {
	freopen("input/2.txt", "r", stdin);
	mjscore.Clear_WithoutRule();
	memset(hand2, 0, sizeof(hand2));
	memset(fuuro, 0, sizeof(fuuro));
	memset(dora, 0, sizeof(dora));
	int lastTile = -1;
	for (int i = 0; i < typeCount2; i++) {
		cin >> hand2[i];
		if(lastTile==-1&&hand2[i]>0){
			lastTile = i;
		}
	}

	// int fuuroCount;
	// cin >> fuuroCount;
	// for (int i = 0; i < fuuroCount; i++) {
	// 	string fuuroType;
	// 	cin >> fuuroType;
	// 	fuuro[i * 4] = parseFuuroType(fuuroType);
	// 	cin >> fuuro[i * 4 + 1];
	// }
	// mjscore.Set_Fuuro(fuuro);
	syanten.set_fuurosuu(0);
	for (int i = 1; i <= doraCount; i++) {
		cin >> dora[i];
	}
	// mjscore.Set_Dora(dora);
	// mjscore.Set_Agarihai(lastTile);
	// mjscore.Set_Tehai(hand2);
	// syanten.set_tehai(hand2);



	int direction = 31;
	int tsumoAgari = 1;
	mjscore.Is_Riichi(0);
	mjscore.Set_Tumoagari(0);
	mjscore.Is_Haitei(0);
	mjscore.Set_Bakaze(direction);
	mjscore.Set_Jikaze(direction);
	clock_t start_time = clock();
	dfs(hand2, lastTile, 0);
    clock_t end_time = clock();
    std::cout << "time = " << (end_time - start_time)/(double) CLOCKS_PER_SEC << std::endl;

	// mjscore.Run();

	// cout << 
	// 	(mjscore.Get_ErrorCode() != 0 ? 0 :
	// 		direction == 31 && tsumoAgari ? mjscore.Get_OyaTumo() * 3 :
	// 		direction == 31 ? mjscore.Get_OyaRon() :
	// 		tsumoAgari ? mjscore.Get_KoTumoKo() * 2 + mjscore.Get_KoTumoOya() :
	// 		mjscore.Get_KoRon()) << 
	// 	endl;
}

void initMjscore() {
	//��`������
	mjscore.Avail_Akahai(true);//�����Ф�
	mjscore.Avail_Kuitan(true);//���������Ф�
	mjscore.Avail_ManganKiriage(true);//��؞�Ф��Ϥ��Ф�	
	mjscore.Avail_Ba1500(false);//��ǧ���Ф�
	mjscore.Avail_DoubleKokushi13(false);//��ʿ13��������֥��ۜ��Ф�
	mjscore.Avail_DoubleTyuuren9(false);//���B����9��������֥��ۜ��Ф�
	mjscore.Avail_DoubleDaisuusii(false);//����ϲ���֥��ۜ��Ф�
	mjscore.Avail_DoubleSuttan(false);//�İ��̅g�T���֥��ۜ��Ф�

	//�����۳����ե饰����	
	mjscore.Is_Riichi(false);//��`��
	mjscore.Is_Tenhou(false);//���	
	mjscore.Is_Tiihou(false);//�غ�	
	mjscore.Is_DoubleRiichi(false);//���֥��`��	
	mjscore.Is_Ippatu(false);//һ�k	
	mjscore.Is_Tyankan(false);//����󥫥�	
	mjscore.Is_Rinsyan(false);//��󥷥��	
	mjscore.Is_NagashiMangan(false);//������؞
	mjscore.Is_Haitei(false);//�ϥ��ƥ�
}

int main() {
	// handleSyanten();
	// return 0;
	// ios_base::sync_with_stdio(false);
	initMjscore();
	handleMjscore();
	// handleSyanten();
	return 0;
}