#include "mjenum.h"
namespace mjenum{
    template <typename pure_type>
    bool add(pure_hand_t &h) {
        static_assert(std::is_same_v<pure_type, pure_num_t> || std::is_same_v<pure_type, pure_wind_t>, "type error in function line_parser");
        // 对于数牌, index_size = 9
        // 对于字牌, index_size = 7
        int idx = 0;
        while(++h[idx] > 4){
            h[idx] = 0;
            idx++;
            if constexpr(std::is_same_v<pure_type, pure_num_t>){
                if(idx >= 9){
                    return false;
                }
            }
            else{
                if(idx >= 7){
                    return false;
                }
            }
        }
        return true;
    }

    uint32_t hand_encoder(const pure_hand_t& h){
        // 手牌编码器
        uint32_t ans = 0;
        for(int i=0; i<9;i++){
            ans <<= 3;
            ans |= (h[i] & 0b111);
        }
        return ans;
    }

    pure_hand_t hand_decoder(uint32_t code){
        pure_hand_t result;
        for(int i=8;i>=0; i--){
            result[i] = code & 0b111;
            code >>= 3;
        }
        return result;
    }

    std::ostream& operator<<(std::ostream& os, const std::set<std::tuple<std::multiset<pure_num_t>, bool>>& x){
        os << '{';
        for(auto item=x.cbegin(); item!=x.cend();item++){
            os << "[";
            auto [it, have_pair] = *item;
            for(auto ptr=it.cbegin();ptr!=it.cend();ptr++){
                //            os << '(' << seq_to_string[(int)*ptr] << ')' << ", ";
                os << (int)*ptr << ", ";
            }
            os << "], ";
        }
        os << '}';
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const std::set<std::tuple<std::multiset<pure_wind_t>, bool>>& x){
        os << '{';
        for(auto item=x.cbegin(); item!=x.cend();item++){
            os << "[";
            auto [it, have_pair] = *item;
            for(auto ptr=it.cbegin();ptr!=it.cend();ptr++){
                os << (int)*ptr << ", ";
            }
            os << "], ";
        }
        os << '}';
        return os;
    }

    std::ostream& operator << (std::ostream& os, const pure_hand_t& h){
        for(int i=0; i< 9;i++){
            os<< h[i];
        }
        return os;
    }

    std::vector<std::string> split(const std::string &s, const std::string& seperator){
        std::vector<std::string> result;
        typedef std::string::size_type string_size;
        string_size i = 0;

        while(i != s.size()){
            bool flag = false;
            while(i != s.size() && !flag){
                flag = 1;
                for(string_size x = 0; x < seperator.size(); ++x)
                    if(s[i] == seperator[x]){
                        ++i;flag = false;
                        break;
                    }
            }
            flag = false;
            string_size j = i;
            while(j != s.size() && !flag){
                for(string_size x = 0; x < seperator.size(); ++x){
                    if(s[j] == seperator[x]){
                        flag = true;
                        break;
                    }
                }
                if(!flag)++j;
            }
            if(i != j){
                result.push_back(move(s.substr(i, j-i)));
                i = j;
            }
        }
        return result;
    }

    int sum_of_hand(const pure_hand_t& h){
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

    std::optional<std::set<std::tuple<std::multiset<pure_num_t>, bool>>> dfs_num(pure_hand_t& h){
        /*
         * @param1: 手牌
         * return optional(是否合法){({({手牌序列}, 该手牌序列是否含有对子)}, 手牌是否是空的)}
         */
        std::set<std::tuple<std::multiset<pure_num_t>, bool>> ans = {};
        if(sum_of_hand(h)==0){
            ans.insert(std::make_tuple(std::multiset<pure_num_t>{}, false));
            return ans;
        }
        bool action = false;
        for(int i=0;i < 9;i++){
            if(h[i] >= 3){
                h[i]-=3;
                auto _x = dfs_num(h);
                h[i]+=3;
                if(_x.has_value()){
                    action = true;
                    auto x = _x.value();
                    if(x.empty()){
                        ans.insert({std::make_tuple(std::multiset<pure_num_t>{static_cast<pure_num_t>(i+_111)}, false)});
                    }
                    else{
                        std::set<std::tuple<std::multiset<pure_num_t>, bool>> y = {};
                        for(std::tuple<std::multiset<pure_num_t>, bool> item: x){
                            auto [it, have_pair] = move(item);
                            it.insert(static_cast<pure_num_t>(i+_111));
                            y.insert(std::make_tuple(move(it), have_pair));
                        }
                        ans.merge(std::move(y));
                    }
                }
            }
            if(h[i]>=2){
                h[i]-=2;
                auto _x = dfs_num(h);
                h[i]+=2;
                if(_x.has_value()){
                    auto x= _x.value();
                    // set<tuple<multiset<pure_num_t>, bool>> x
                    if(x.empty()){
                        action = true;
                        ans.insert({std::make_tuple(std::multiset<pure_num_t>{static_cast<pure_num_t>(i+_11)}, true)});
                    }
                    else{
                        std::set<std::tuple<std::multiset<pure_num_t>, bool>> y = {};
                        for(std::tuple<std::multiset<pure_num_t>, bool> item : x){
                            auto [it, have_pair] = std::move(item);
                            // 不能有多个对子
                            if(have_pair) continue;
                            action = true;
                            it.insert(static_cast<pure_num_t>(i+_11));
                            y.insert(std::make_tuple(std::move(it), true));
                        }
                        ans.merge(std::move(y));
                    }
                }
            }
        }
        for(int i=0;i+2<9; i++){
            if(h[i]>0 && h[i+1]>0 && h[i+2]>0){
                h[i]--; h[i+1]--; h[i+2]--;
                auto _x = dfs_num(h);
                h[i]++; h[i+1]++; h[i+2]++;
                if(_x.has_value()){
                    action = true;
                    auto x = _x.value();
                    if(x.empty()){
                        ans.insert(std::make_tuple(std::multiset<pure_num_t>{static_cast<pure_num_t>(i+_123)}, false));
                    }
                    else{
                        std::set<std::tuple<std::multiset<pure_num_t>, bool>> y = {};
                        for(std::tuple<std::multiset<pure_num_t>, bool> item :x){
                            auto[it, have_pair] = std::move(item);
                            it.insert(static_cast<pure_num_t>(i+_123));
                            y.insert(std::make_tuple(std::move(it), have_pair));
                        }
                        ans.merge(std::move(y));
                    }
                }
            }
        }
        if(!action){
            return {};
        }
        else{
            return  ans;
        }
    }
    std::optional<std::set<std::tuple<std::multiset<pure_wind_t>, bool>>> dfs_wind(pure_hand_t& h){
        /*
         * @param1: 手牌
         * return optional(是否合法){({({手牌序列}, 该手牌序列是否含有对子)}, 手牌是否是空的)}
         */
        std::set<std::tuple<std::multiset<pure_wind_t>, bool>> ans = {};
        if(sum_of_hand(h)==0){
            ans.insert(std::make_tuple(std::multiset<pure_wind_t>{}, false));
            return ans;
        }
        bool action = false;
        for(int i=0;i < 7;i++){
            if(h[i] >= 3){
                h[i]-=3;
                auto _x = dfs_wind(h);
                h[i]+=3;
                if(_x.has_value()){
                    action = true;
                    auto x = _x.value();
                    if(x.empty()){
                        ans.insert({std::make_tuple(std::multiset<pure_wind_t>{static_cast<pure_wind_t>(i+_EEE)}, false)});
                    }
                    else{
                        std::set<std::tuple<std::multiset<pure_wind_t>, bool>> y = {};
                        for(std::tuple<std::multiset<pure_wind_t>, bool> item: x){
                            auto [it, have_pair] = move(item);
                            it.insert(static_cast<pure_wind_t>(i+_EEE));
                            y.insert(std::make_tuple(move(it), have_pair));
                        }
                        ans.merge(std::move(y));
                    }
                }
            }
            if(h[i]>=2){
                h[i]-=2;
                auto _x = dfs_wind(h);
                h[i]+=2;
                if(_x.has_value()){
                    auto x = _x.value();
                    // set<tuple<multiset<pure_character>, bool>> x
                    if(x.empty()){
                        action = true;
                        ans.insert({std::make_tuple(std::multiset<pure_wind_t>{static_cast<pure_wind_t>(i+_EE)}, true)});
                    }
                    else{
                        std::set<std::tuple<std::multiset<pure_wind_t>, bool>> y = {};
                        for(std::tuple<std::multiset<pure_wind_t>, bool> item : x){
                            auto [it, have_pair] = std::move(item);
                            // 不能有多个对子
                            if(have_pair) continue;
                            action = true;
                            it.insert(static_cast<pure_wind_t>(i+_EE));
                            y.insert(std::make_tuple(std::move(it), true));
                        }
                        ans.merge(std::move(y));
                    }
                }
            }
        }

        if(!action){
            return {};
        }
        else{
            return  ans;
        }
    }
    std::vector<std::tuple<int,int>> dfs_syanten(pure_hand_t& h){
        std::vector<std::tuple<int,int>> result={std::make_tuple(0,0)};
        for(int i=0; i<9;i++){
            if(h[i]>=3){
                h[i]-=3;
                auto x = move(dfs_syanten(h));
                h[i]+=3;
                for(auto [a, b]: x){
                    result.push_back(std::make_tuple(a+1, b));
                }
            }
            if(h[i]>=2){
                h[i]-=2;
                auto x = move(dfs_syanten(h));
                h[i]+=2;
                for(auto [a, b]: x){
                    result.push_back(std::make_tuple(a, b+1));
                }
            }
        }
        for(int i=0; i+2<9;i++){
            if(h[i]>0&&h[i+1]>0&&h[i+2]>0){
                h[i]--;h[i+1]--;h[i+2]--;
                auto x = move(dfs_syanten(h));
                h[i]++;h[i+1]++;h[i+2]++;
                for(auto [a, b]:x){
                    result.push_back(std::make_tuple(a+1,b));
                }
            }

            if(h[i]>0 && h[i+2]>0){
                h[i]--; h[i+2]--;
                auto x = std::move(dfs_syanten(h));
                h[i]++; h[i+2]++;
                for(auto [a, b]:x){
                    result.push_back(std::make_tuple(a, b+1));
                }
            }
        }
        for(int i=0;i+1<9;i++){
            if(h[i+1]>0 && h[i]>0){
                h[i]--; h[i+1]--;
                auto x = std::move(dfs_syanten(h));
                h[i]++; h[i+1]++;
                for(auto [a, b]:x){
                    result.push_back(std::make_tuple(a, b+1));
                }
            }
        }
        return std::move(result);
    }
    bool compare_syanten(const std::tuple<int,int>& a, const std::tuple<int, int> & b){
        auto [a1, a2] = a;
        int val_a = 2*a1+a2;
        auto [b1, b2] = b;
        int val_b = 2*b1+b2;
        if(val_a != val_b)
            return 2*a1+a2 > 2*b1+b2;
        else
            return a1 > b1;
    }
    bool compare_syanten_value_equal(const std::tuple<int,int>& a, const std::tuple<int, int> & b){
        auto [a1, a2] = a;
        auto [b1, b2] = b;
        return 2*a1+a2 == 2*b1+b2 && (a1!=a2 || b1!=b2);
    }

    bool gen_num_dat_file(){
        pure_hand_t hand;
        hand.fill(0);
        std::ofstream f;
        // 生成数牌的库
        f.open("mj_num.dat", std::ios::out);
        if(!f.good()){
            std::cerr << "open mj_num.dat error!" << std::endl;
            return false;
        }
        do{
            int sum = sum_of_hand(hand);
            if(judge_sum_legal(sum)){
                auto x = dfs_num(hand);
                if(x.has_value()){
                    auto ans = x.value();
                    f << hand << ' ' << ans << std::endl;
                }
            }
        } while (add<pure_num_t>(hand));
        f.close();
        return true;
    }
    bool gen_wind_dat_file(){
        pure_hand_t hand;
        hand.fill(0);
        std::ofstream f;
        // 生成字牌的库
        f.open("mj_wind.dat", std::ios::out);
        if(!f.good()){
            std::cerr << "open mj_wind.dat error!" << std::endl;
            return false;
        }
        hand.fill(0);
        do{
            int sum = sum_of_hand(hand);
            if(judge_sum_legal(sum)){
                auto x = dfs_wind(hand);
                if(x.has_value()){
                    auto ans= x.value();
                    f << hand << ' ' << ans << std::endl;
                }
            }
        } while (add<pure_wind_t>(hand));
        f.close();
        return true;
    }
//    bool gen_syanten_dat_file(){
//        pure_hand_t hand;
//        hand.fill(0);
//        std::ofstream f;
//        f.open("mj_syanten.dat", std::ios::out);
//        if(!f.good()){
//            std::cerr << "open syanten.dat error" << std::endl;
//            return false;
//        }
//        hand.fill(0);
//        do{
//            int sum = sum_of_hand(hand);
//            if(sum > 14) continue;
//            // TODO:
//            auto x = dfs_syanten(hand);
//            std::sort(x.begin(), x.end(), compare_syanten);
//            auto [a1, a2] = x[0];
//            f << hand << ' ' << a1 << ' ' << a2 << ' ';
//            if(x.size()>1 && compare_syanten_value_equal(x[0],x[1])){
//                auto [b1, b2] = x[1];
//                f << b1 << ' ' << b2 << std::endl;
//            }
//            else{
//                f << a1 << ' ' << a2 << std::endl;
//            }
//        } while (add<pure_num_t>(hand));
//        f.close();
//        return true;
//    }
    bool gen_dat_file(){
        bool a= true, b= true, c= true;
        if(!test_file_exist("mj_num.dat")){
            std::cout << "generate mj_num.dat(about 3min)... " << std::endl;
            a = gen_num_dat_file();
        }
        if(!test_file_exist("mj_wind.dat")){
            std::cout << "generate mj_wind.dat... " << std::endl;
            b = gen_wind_dat_file();
        }
//        if(!test_file_exist("mj_syanten.dat")){
//            std::cout << "generate mj_syanten.dat(about 5min)... " << std::endl;
//            c = gen_syanten_dat_file();
//        }
        return a && b && c;
    }
    template<typename pure_type>
    pure_hand_t hand_parser(const std::string& line){
        static_assert(std::is_same_v<pure_type, pure_num_t> || std::is_same_v<pure_type, pure_wind_t>, "type error in function line_parser");
        int idx=0;
        while(line[idx] == ' ') idx++;
        pure_hand_t h;
        if constexpr(std::is_same_v<pure_type, pure_num_t>){
            for(int i=0; i<9; i++){
                h[i] = line[idx+i] - '0';
            }
        }
        else{
            for(int i=0; i<7; i++){
                h[i] = line[idx+i] - '0';
            }
        }
        return h;
    }
    template <typename pure_type>
    std::tuple<std::multiset<pure_type>, bool> list_parser(const std::string& line){
        static_assert(std::is_same_v<pure_type, pure_num_t> || std::is_same_v<pure_type, pure_wind_t>, "type error in function list_parser");
        std::multiset<pure_type> result = {};
        bool have_pair = false;
        std::vector<std::string> nums = split(line, ", []");
        for(const auto& num: nums){
            auto seq = static_cast<pure_type>(stoi(num));
            if constexpr(std::is_same_v<pure_type, pure_num_t>){
                if(seq >= _11 && seq <= _99)
                    have_pair = true;
            }
            else{
                if(seq >= _EE && seq <= _RedR){
                    have_pair = true;
                }
            }
            result.insert(seq);
        }
        return std::make_tuple(std::move(result), have_pair);
    }
    template <typename pure_type>
    std::set<std::tuple<std::multiset<pure_type>, bool>> set_parser(const std::string& line){
        // parse {x1, x2, ...} which xi = tuple<multiset<pure_num_t>, bool>
        std::set<std::tuple<std::multiset<pure_type>, bool>> result = {};
        int idx = 0;
        while(line[idx]!='{') idx++;
        for(int num_left_sq_br=0, l=0;line[idx+l]!='}'; l++){
            switch (line[idx+l]) {
                case '[': num_left_sq_br++;
                idx = idx+l+1; l=0;
                break;
                case ']': num_left_sq_br--;
                if(num_left_sq_br==0){
                    auto list = list_parser<pure_type>(line.substr( idx,l-1));
                    result.insert(move(list));
                }
                break;
            }
        }
        return std::move(result);
    }
    template <typename pure_type>
    std::tuple<pure_hand_t, std::set<std::tuple<std::multiset<pure_type>, bool>>> line_parser(const std::string& line){
        static_assert(std::is_same_v<pure_type, pure_num_t> || std::is_same_v<pure_type, pure_wind_t>, "type error in function line_parser");
        int idx = 0;
        while (line[idx] == ' ') idx++;
        int l = 0;
        while (line[idx+l] != ' ') l++;
        std::string hand_str = line.substr(idx, l);
        pure_hand_t hand = hand_parser<pure_type>(hand_str);
        idx += l; l = line.size() - idx;
        std::set<std::tuple<std::multiset<pure_type>, bool>> seq = set_parser<pure_type>(line.substr(idx, l));
        return make_tuple(hand, seq);
    }
    std::map<uint32_t, std::set<std::tuple<std::multiset<pure_num_t>, bool>>> load_num_map(){
        std::map<uint32_t, std::set<std::tuple<std::multiset<pure_num_t>, bool>> > mj_map;
        std::string file_name = "mj_num.dat";
        std::ifstream f(file_name, std::ios::in);
        if(!f.good()){
            std::cerr << "open \"" << file_name << "\" file error!" << std::endl;
            std::cout <<  "try to generate mahjong data (about 2min)... " << std::flush;
            gen_num_dat_file();
            f.open(file_name, std::ios::in);
            if(!f.good()){
                std::cerr << "Failed! Please check file system!" << std::endl;
                exit(1);
            }
            std::cout << "OK!" << std::endl;
        }
        std::string line;
        while(std::getline(f, line)){
            auto[hand, seq] = line_parser<pure_num_t>(line);
            uint32_t index = hand_encoder(hand);
            mj_map[index] = seq;
        }
        // a little check
        if(mj_map.size()!=21743){
            std::cerr << "file \"" << file_name << "\" broken, please delete it and rerun the program!";
            exit(1);
        }
        return std::move(mj_map);
    }
    std::map<uint32_t, std::set<std::tuple<std::multiset<pure_wind_t>, bool>>> load_wind_map(){
        std::map<uint32_t, std::set<std::tuple<std::multiset<pure_wind_t>, bool>>> mj_map;
        std::string file_name = "mj_wind.dat";
        std::ifstream f(file_name, std::ios::in);
        if(!f.good()){
            std::cerr << "open \"" << file_name << "\" file error!" << std::endl;
            std::cout <<  "try to generate mahjong data (about 2min)... " << std::flush;
            gen_wind_dat_file();
            f.open(file_name, std::ios::in);
            if(!f.good()){
                std::cerr << "Failed! Please check file system!" << std::endl;
                exit(1);
            }
            std::cout << "OK!" << std::endl;
        }
        std::string line;
        while(std::getline(f, line)){
            auto[hand, seq] = line_parser<pure_wind_t>(line);
            uint32_t index = hand_encoder(hand);
            mj_map[index] = seq;
        }
        // a little check
        if(mj_map.size() != 498){
            std::cerr << "file \"" << file_name << "\" broken, please delete it and rerun the program!";
            exit(1);
        }
        return std::move(mj_map);
    }
    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> hand_to_index(const hand_t& h){
        uint32_t index[4] = {0, 0, 0, 0};
        for(int base = 0; base < 3; base++){
            for(int i=0; i<9;i++){
                index[base] <<= 3;
                index[base] |= (h[base*(P1-M1)+i+1] & 0x111);
            }
        }
        int base = 3;
        for(int i=0; i<7;i++){
            index[base] <<= 3;
            index[base] |= (h[base*(P1-M1)+i+1] & 0x111);
        }
        return std::make_tuple(index[0], index[1], index[2], index[3]);
    }
    std::multiset<seq_t> pure_num_to_seq(const std::multiset<pure_num_t>& pure_seq, int base){
        std::multiset<seq_t> result = {};
        for(const auto& n_seq: pure_seq){
            result.insert(static_cast<seq_t>(n_seq+base*(P111-M111)+M111));
        }
        return std::move(result);
    }
    std::multiset<seq_t> pure_wind_to_seq(const std::multiset<pure_wind_t>& pure_character){
        std::multiset<seq_t> result = {};
        for(const auto& c_seq: pure_character){
            result.insert(static_cast<seq_t>(c_seq+EEE));
        }
        return std::move(result);
    }
}