//
// Created by 王明龙 on 2023/2/10.
//

#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;

class StringHash {

public:
    explicit StringHash(const string &str, const int p = 131) : str(str), P(p) {}


    /*!
     * 用于生成指定字符串的哈希值
     * @return 返回字符串的哈希值
     */
    ull get_str_hash() {
        ull has_res{0};
        for (auto &c: str) {
            has_res = has_res * P + c - 'a' + 1;       //把a映射到1，注意不要映射到0，因为会无法区分ab和b
        }
        return has_res;
    }


    /*!
     * 得到字符串的前缀哈希数组
     * @return
     */
    std::shared_ptr<vector<int>> get_prefix_str_hash() {
        std::shared_ptr<vector<int>> prefix_hash = make_shared<vector<int>>(str.size(), 0);
        if (!str.empty()) {      //0坐标单独处理
            prefix_hash->at(0) = str[0] - 'a' + 1;
        }
        for (int i = 1; i < str.size(); i++) {    //递推处理 p[i] = p[i-1]*P + s[i] - 'a' + 1
            prefix_hash->at(i) = prefix_hash->at(i - 1) * P + str[i] - 'a' + 1;
        }
        return prefix_hash;
    }


    /*!
     * 得到[left,right]字串的哈希值
     * @param left 左边界
     * @param right 右边界
     * @param prefix_hash  前缀哈希数组
     * @param power 快速幂值
     * @return   返回区间[left,right]字串的哈希值
     */
    ull get_str_interval_hash(const int &left, const int &right, std::shared_ptr<vector<int>> &prefix_hash,
                              std::shared_ptr<vector<int>> &power) {
        if (!left) {
            return prefix_hash->at(right);
        } else {
            return prefix_hash->at(right) - prefix_hash->at(left - 1) * power->at(right - left + 1);
        }
    }


private:
    string str;    //字符串
    const int P; //进制
};


int main() {
    string s;
    int n{0};
    cin >> n;
    vector<unsigned long long> str_hash;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        str_hash.emplace_back(StringHash(s).get_str_hash());
    }

    sort(str_hash.begin(), str_hash.end());
    auto ptr = unique(str_hash.begin(), str_hash.end());
    cout << distance(str_hash.begin(), ptr);
    return 0;
}