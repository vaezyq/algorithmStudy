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
            has_res = has_res * P + c - '0' + 1;       //把a映射到1，注意不要映射到0，因为会无法区分ab和b
        }
        return has_res;
    }


    /*!
     * 得到字符串的前缀哈希数组
     * @return
     */
    std::shared_ptr<vector<ull>> get_prefix_str_hash() {
        std::shared_ptr<vector<ull>> prefix_hash = make_shared<vector<ull>>(str.size(), 0);
        if (!str.empty()) {      //0坐标单独处理
            prefix_hash->at(0) = str[0] - '0' + 1;
        }
        for (int i = 1; i < str.size(); i++) {    //递推处理 p[i] = p[i-1]*P + s[i] - 'a' + 1
            prefix_hash->at(i) = prefix_hash->at(i - 1) * P + str[i] - '0' + 1;
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
    ull get_str_interval_hash(const int &left, const int &right, std::shared_ptr<vector<ull>> &prefix_hash,
                              std::shared_ptr<vector<ull>> &power) {
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
    int n{0};
    cin >> n;
    string str;
    cin >> str;
    string str_reverse;
    for (auto &e: str) {
        str_reverse += (e == '0' ? '1' : '0');
    }

    reverse(str_reverse.begin(), str_reverse.end());

    StringHash stringHash(str);
    StringHash stringHashReverse(str_reverse);


    std::shared_ptr<vector<ull>> power = make_shared<vector<ull>>(str.size(), 1);
    for (int i = 1; i < str.size(); ++i) {
        power->at(i) = power->at(i - 1) * 131;
    }

    auto prefix_hash = stringHash.get_prefix_str_hash();
    auto prefix_hash_reverse = stringHashReverse.get_prefix_str_hash();

//    cout << stringHash.get_str_interval_hash(0, 3, prefix_hash, power) << endl;
//    cout << stringHashReverse.get_str_interval_hash(
//            4, 7, prefix_hash_reverse, power) << endl;


    int ans = 0;
    for (int i = 0; i < str.size(); ++i) {

        int left = -1, right = min(i + 1, int(str.size() - i));
        while (left + 1 != right) {
            int mid = (left + right) >> 1;


            if (str.size() - i - 1 + mid < str.size() && i + 1 + mid < str.size() &&
                stringHash.get_str_interval_hash(i - mid, i + 1 + mid, prefix_hash, power) ==
                stringHashReverse.get_str_interval_hash(
                        str.size() - i - 2 - mid, str.size() - i - 1 + mid, prefix_hash_reverse, power)) {
                left = mid;
            } else {
                right = mid;
            }

//                if (i + 1 + mid < str.size() && stringHash.get_str_interval_hash(i - mid, i, prefix_hash, power) ==
//                                                stringHashReverse.get_str_interval_hash(i + 1, i + 1 + mid,
//                                                                                        prefix_hash_reverse, power)) {
//
//                } else {
//
//                }
        }
//        cout << left << endl;
        ans += (left + 1);
    }

    cout << ans << endl;
    return 0;

}