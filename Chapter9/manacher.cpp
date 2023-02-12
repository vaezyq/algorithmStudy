//
// Created by 王明龙 on 2023/2/11.
//
#include <bits/stdc++.h>

using namespace std;


class Manacher {

public:
    explicit Manacher(const string &str) {

        processed_str += "$";

        for (const auto &c: str) {
            processed_str += "#";
            processed_str += c;
        }
        processed_str += "#&";
    }

    std::shared_ptr<vector<int>> get_maximum_palindromic_radius_array() {

        int center = 0, max_right = 0;
        std::shared_ptr<vector<int>> max_radius_array = make_shared<vector<int>>(processed_str.size(), 0);
        for (auto i = 1; i < processed_str.size(); ++i) {
            if (i < max_right) {
                max_radius_array->at(i) = min(max_radius_array->at((center << 1) - i),
                                              center + max_radius_array->at(center) - i);
            } else {
                max_radius_array->at(i) = 1;       //最大回文半径从1开始暴力枚举
            }

            while (processed_str[i + max_radius_array->at(i)] == processed_str[i - max_radius_array->at(i)]) {
                max_radius_array->at(i)++;
            }
            if (max_radius_array->at(i) + i > max_right) {
                max_right = max_radius_array->at(i) + i;
                center = i;
            }
        }
        return max_radius_array;
    }


    int get_maximum_palindromic_length() {
        auto max_radius_array = get_maximum_palindromic_radius_array();
        int ans{1};
        for_each(max_radius_array->begin(), max_radius_array->end(), [&ans](int a) {
//            cout<<a<<endl;
            ans = max(ans, a);
        });
        return ans - 1;
    }


private:
//    string str;
    string processed_str;
};


int main() {
    string str;
    cin >> str;
    Manacher manacher(str);
    cout << manacher.get_maximum_palindromic_length();
    return 0;
}













