#ifndef __MJENUM_LOADER__
#define __MJENUM_LOADER__
#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <set>
#include <tuple>
#include <array>
#include <algorithm>
#include "common.h"

namespace mjenum{
    EXPORT using pure_hand_t = std::array<int, 9>;
    enum pure_num_t{
        _111, _222, _333, _444, _555, _666, _777, _888, _999,
        _123, _234, _345, _456, _567, _678, _789,
        _11, _22, _33, _44, _55, _66, _77, _88, _99
    };
    enum pure_wind_t{
        _EEE, _SSS, _WWW, _NNN, _WhiteWW, _GreenGG, _RedRR,
        _EE, _SS, _WW, _NN, _WhiteW, _GreenG, _RedR
    };
    template <typename pure_type> bool add(pure_hand_t& h);
    uint32_t hand_encoder(const pure_hand_t& h);
    pure_hand_t hand_decoder(uint32_t code);
    std::ostream& operator<<(std::ostream& os, const std::set<std::tuple<std::multiset<pure_num_t>, bool>>& x);
    std::ostream& operator<<(std::ostream& os, const std::set<std::tuple<std::multiset<pure_wind_t>, bool>>& x);
    std::ostream& operator<<(std::ostream& os, const pure_hand_t& h);
    std::vector<std::string> split(const std::string &s, const std::string& );
    int sum_of_hand(const pure_hand_t& h);
    bool judge_sum_legal(int sum);
    std::optional<std::set<std::tuple<std::multiset<pure_num_t>, bool>>> dfs_num(pure_hand_t& h);
    std::optional<std::set<std::tuple<std::multiset<pure_wind_t>, bool>>> dfs_wind(pure_hand_t& h);
    std::vector<std::tuple<int,int>> dfs_syanten(pure_hand_t& h);
    bool compare_syanten(const std::tuple<int,int>&, const std::tuple<int, int> &);
    bool compare_syanten_value_equal(const std::tuple<int,int>&, const std::tuple<int, int> &);
    template <typename pure_type>
    pure_hand_t hand_parser(const std::string& line);

    template <typename pure_type>
    std::tuple<pure_hand_t, std::set<std::tuple<std::multiset<pure_type>, bool>>> line_parser(const std::string& line);

    template <typename pure_type>
    std::set<std::tuple<std::multiset<pure_type>, bool>> set_parser(const std::string& line);

    template <typename pure_type>
    std::tuple<std::multiset<pure_type>, bool> list_parser(const std::string& line);

    // generate "mj.dat" in current directory
    bool gen_num_dat_file();
    bool gen_wind_dat_file();
    // TODO: fix the bug in generate syanten data
//    bool gen_syanten_dat_file(); // many bugs
    bool gen_dat_file();

    // load "mj.dat" to memory
    EXPORT std::map<uint32_t, std::set<std::tuple<std::multiset<pure_num_t>, bool>>> load_num_map();
    EXPORT std::map<uint32_t, std::set<std::tuple<std::multiset<pure_wind_t>, bool>>> load_wind_map();
    EXPORT std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> hand_to_index(const hand_t& h);
    EXPORT std::multiset<seq_t> pure_num_to_seq(const std::multiset<pure_num_t>& pure_seq, int base);
    EXPORT std::multiset<seq_t> pure_wind_to_seq(const std::multiset<pure_wind_t>& pure_character);
}

#endif