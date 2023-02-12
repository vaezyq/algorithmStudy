//
// Created by 王明龙 on 2023/2/10.
//
#include <bits/stdc++.h>

using namespace std;


//rank记录排名，rank[i]: 第i位的后缀在字符串所有后缀中的排名
//suffix记录排名位置,suffix[i]: 在字符串所有后缀中排名第i位的后缀在子串中的位置
bool suffix_sa(int i, int j) {

}


bool calc_suffix_array(const string &s, vector<int> &suffix, vector<int> &rank) {
    for (int i = 0; i < s.size(); ++i) {
        rank[i] = static_cast<int>(s[i]);
        suffix[i] = i;
    }


    for (int k = 1; k < s.size(); k <<= 1) {
        sort(suffix.begin(), suffix.end(), [&](int i, int j) {
            if (rank[i] != rank[j]) {
                return rank[i] < rank[j];
            } else {
                auto ri = i + k < s.size() ? rank[i + k] : -1;
                auto rj = j + k < s.size() ? rank[j + k] : -1;
                return ri < rj;
            }
        });



    }


}
