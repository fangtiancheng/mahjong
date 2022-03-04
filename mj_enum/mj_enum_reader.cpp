#include <iostream>
#include <string>
#include <set>
#include <array>
#include <map>
#include <bitset>
#include <vector>
#include "common.h"
using namespace std;

hand_t hand_parser(const string& line){
    int idx=0;
    while(line[idx] == ' ') idx++;
    hand_t h;
    for(int i=0; i<9; i++){
        h[i] = line[idx+i] - '0';
    }
    return h;
}

tuple<multiset<seq_t>, bool> list_parser(const string& line){
    multiset<seq_t> result = {};
    bool have_pair = false;
    vector<string> nums = split(line, ", []");
    for(const auto& num: nums){
        seq_t seq = static_cast<seq_t>(stoi(num));
        if(seq >= _11 && seq <= _99)
            have_pair = true;
        result.insert(seq);
    }
    return make_tuple(move(result), have_pair);
}
set<tuple<multiset<seq_t>, bool>> set_parser(const string& line){
    // parse {x1, x2, ...} which xi = tuple<multiset<seq_t>, bool>
    set<tuple<multiset<seq_t>, bool>> result = {};
    int idx = 0;
    while(line[idx]!='{') idx++;
    for(int num_left_sq_br=0, l=0;line[idx+l]!='}'; l++){
        switch (line[idx+l]) {
            case '[': num_left_sq_br++;
                idx = idx+l+1; l=0;
            break;
            case ']': num_left_sq_br--;
                if(num_left_sq_br==0){
                    auto list = list_parser(line.substr( idx,l-1));
                    result.insert(move(list));
                }
            break;
        }
    }
    return result;
}

tuple<hand_t, set<tuple<multiset<seq_t>, bool>>> line_parser(const string& line){
    int idx = 0;
    while (line[idx] == ' ') idx++;
    int l = 0;
    while (line[idx+l] != ' ') l++;
    string hand_str = line.substr(idx, l);
    hand_t hand = hand_parser(hand_str);
    idx += l; l = line.size() - idx;
    set<tuple<multiset<seq_t>, bool>> seq = set_parser(line.substr(idx, l));
    return make_tuple(hand, seq);
}
int test(){
    hand_t h = {};
    do{
        if(h!= hand_decoder(hand_encoder(h))){
            cout << "h = " << h << "\ttmp = " <<  bitset<32>( hand_encoder(h) ) << "\tout = " << hand_decoder(hand_encoder(h)) << endl;
            cout << "encoder or decoder error!" << endl;
            return 1;
        }

    } while (add(h));
    return 0;
}

int main(){
    ofstream out_f("mj-read.dat", ios::out);
    map<uint32_t, set<tuple<multiset<seq_t>, bool>> > mj_map;
    string file_name = "mj.dat";
    ifstream f(file_name, ios::in);
    if(!f.good()){
        cout << "open file error!" << endl;
        return 1;
    }
    string line;
    while(getline(f, line)){
        auto[hand, seq] = line_parser(line);
        uint32_t index = hand_encoder(hand);
        // TODO: test
        mj_map[index] = seq;
    }
    for(auto it=mj_map.cbegin();it!=mj_map.cend();it++){
        out_f << hand_decoder(it->first) << ' ' << it->second << endl;
    }
    f.close();
    out_f.close();
    return 0;
}