//
// Created by 王明龙 on 2023/2/14.
//
#include <bits/stdc++.h>

using namespace std;

const int MAX = 0x7FFFFFFF;

class StoneMerge {
public:
    StoneMerge(const vector<int> &stone) {
        dp.assign(stone.size(), vector<int>(stone.size(), 0));
        stone_nums.assign(stone.size(), vector<int>(stone.size(), 0));

        for (int i = 0; i < stone.size(); ++i) {
            int sum = 0;
            for (int j = i; j < stone.size(); ++j) {
                sum += stone[j];
                stone_nums[i][j] = sum;

            }
        }
    }

    void solve() {
        for (int i = 0; i < stone_nums.size() - 1; ++i) {
            for (int j = i + 1; j < stone_nums.size(); ++j) {
                int res = MAX;
                for (int k = i; k < j; ++k) {
                    res = min(res, dp[i][k] + dp[k + 1][j] + stone_nums[i][j]);
                }
                dp[i][j] = res;
            }
        }
    }

    int get_result() {
        solve();
        return dp[dp.size() - 1][dp[0].size() - 1];
    }


private:
    vector<vector<int>> dp;
    vector<vector<int>> stone_nums;

};


int main() {
    StoneMerge stoneMerge({2, 4, 5});
    cout << stoneMerge.get_result();
    return 0;
}