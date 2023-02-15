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

    int solve_by_recursion(const int &index, const int &index2) {
        if (dp[index][index2]) { return dp[index][index2]; }

        int res = MAX;
        if (index == index2) { return 0; }

        for (auto k = index; k < index2; ++k) {
            res = min(res,
                      solve_by_recursion(index, k) + solve_by_recursion(k + 1, index2) + stone_nums[index][index2]);
        }
        return dp[index][index2] = res;
    }


    void solve() {

        for (int i = stone_nums.size() - 1; i >= 0; --i) {

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
//        solve_by_recursion(0, stone_nums.size() - 1);
        solve();
        return dp[0][dp[0].size() - 1];
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