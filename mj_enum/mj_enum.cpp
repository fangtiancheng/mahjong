#include <iostream>
#include <tuple>
#include <fstream>
#include <array>
#include <set>
#include "common.h"
using namespace std;

int sum_of_hand(const hand_t& h){
    int sum=0;
    for(int i=0;i<9;i++){
        sum += h[i];
    }
    return sum;
}
bool judge_sum_legal(int sum){
    switch (sum) {
        case 0: case 2: case 3: case 5: case 6: case 8:
            case 9: case 11: case 12: case 14:
            return true;
        default:
            return false;
    }
}

optional<tuple<set<tuple<multiset<seq_t>, bool>>, bool>> dfs(hand_t& h){
    /*
     * @param1: 手牌
     * return optional(是否合法){({({手牌序列}, 该手牌序列是否含有对子)}, 手牌是否是空的)}
     */
    set<tuple<multiset<seq_t>, bool>> ans = {};
    if(sum_of_hand(h)==0){
        return make_tuple(ans, true);
    }
    bool action = false;
    for(int i=0;i < 9;i++){
        if(h[i] >= 3){
            h[i]-=3;
            auto _x = dfs(h);
            h[i]+=3;
            if(_x.has_value()){
                action = true;
                auto [x, is_empty] = _x.value();
                if(is_empty){
                    ans.insert({make_tuple(multiset<seq_t>{static_cast<seq_t>(i)}, false)});
                }
                else{
                    set<tuple<multiset<seq_t>, bool>> y = {};
                    for(tuple<multiset<seq_t>, bool> item: x){
                        auto [it, have_pair] = move(item);
                        it.insert(static_cast<seq_t>(i));
                        y.insert(make_tuple(move(it), have_pair));
                    }
                    ans.merge(move(y));
                }
            }
        }
        if(h[i]>=2){
            h[i]-=2;
            auto _x = dfs(h);
            h[i]+=2;
            if(_x.has_value()){
                auto [x, is_empty]= _x.value();
                // set<tuple<multiset<seq_t>, bool>> x
                if(is_empty){
                    action = true;
                    ans.insert({make_tuple(multiset<seq_t>{static_cast<seq_t>(i+16)}, true)});
                }
                else{
                    set<tuple<multiset<seq_t>, bool>> y = {};
                    for(tuple<multiset<seq_t>, bool> item : x){
                        auto [it, have_pair] = move(item);
                        // 不能有多个对子
                        if(have_pair) continue;
                        action = true;
                        it.insert(static_cast<seq_t>(i+16));
                        y.insert(make_tuple(move(it), true));
                    }
                    ans.merge(move(y));
                }

            }
        }
    }
    for(int i=0;i+2<9; i++){
        if(h[i]>0 && h[i+1]>0 && h[i+2]>0){
            h[i]--; h[i+1]--; h[i+2]--;
            auto _x = dfs(h);
            h[i]++; h[i+1]++; h[i+2]++;
            if(_x.has_value()){
                action = true;
                auto [x, is_empty] = _x.value();
                if(is_empty){
                    ans.insert(make_tuple(multiset<seq_t>{static_cast<seq_t>(i+9)}, false));
                }
                else{
                    set<tuple<multiset<seq_t>, bool>> y = {};
                    for(tuple<multiset<seq_t>, bool> item :x){
                        auto[it, have_pair] = move(item);
                        it.insert(static_cast<seq_t>(i+9));
                        y.insert(make_tuple(move(it), have_pair));
                    }
                    ans.merge(move(y));
                }
            }
        }
    }
    if(!action){
        return {};
    }
    else{
        return  make_tuple(ans, false);
    }
}

int main(){
    hand_t hand = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    ofstream f("mj.dat", ios::out);
    DEBUG
    if(!f.good()){
        cout << "open file error!" << endl;
        return 1;
    }
    do{
        int sum = sum_of_hand(hand);
        if(judge_sum_legal(sum)){
            auto x = dfs(hand);
            if(x.has_value()){
                auto [ans_tuple, is_empty] = x.value();
                if(!is_empty){
                    f << hand << ' ' << ans_tuple << endl;
                }
            }
        }
    } while (add(hand));
    f.close();
    return 0;
}