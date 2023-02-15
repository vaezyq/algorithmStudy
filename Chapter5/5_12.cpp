//
// Created by 王明龙 on 2023/2/15.
//
#include <bits/stdc++.h>

using namespace std;
const int MAX = 0x7FFFFFFF;

class StringPainter {

public:
    StringPainter(const string &str, const string &str2) : str(str), str2(str2) {
        dp.assign(str.size(), vector<int>(str.size(), 0));
    }


    int solve(const int &index, const int &index2) {
        if (dp[index][index2]) { return dp[index][index2]; }

        if (index == index2) {
//            dp[index][index2] = (str[index] == str2[index2]) ? 0 : 1;
            return dp[index][index2] = 1;
        }

        if (str2[index] == str2[index2]) {
            dp[index][index2] = solve(index, index2 - 1);
        } else {
            int res = MAX;
            for (int k = index; k != index2; ++k) {
                res = min(res, solve(index, k) + solve(k + 1, index2));
            }
            dp[index][index2] = res;
        }


        return dp[index][index2];
    }

    int get_result() {
        solve(0, str2.size() - 1);    //把空字符串刷成str的需要结果

        vector<int> new_dp(str.size(), 0);

        for (int i = 0; i < str.size(); ++i) {

            new_dp[i] = dp[0][i];
            if (str[i] == str2[i]) {
                new_dp[i] = (i == 0 ? 0 : (dp[0][i - 1] == 0 ? solve(0, i - 1) : dp[0][i - 1]));
            } else {
                for (int k = 0; k < i; ++k) {
                    new_dp[i] = min(new_dp[i], new_dp[k] + (dp[k + 1][i] == 0 ? solve(k + 1, i) : dp[k + 1][i]));
                }
            }
        }
        return new_dp[str.size() - 1];
    };

private:
    vector<vector<int>> dp;
    string str;
    string str2;
};

int main() {
    string str;

    string str2;

    while (cin >> str >> str2) {
        if (str.empty()) { break; }
        StringPainter stringPainter(str, str2);
        cout << stringPainter.get_result() << endl;
    }
    return 0;
}