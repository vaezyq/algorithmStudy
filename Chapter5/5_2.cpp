//
// Created by 王明龙 on 2023/2/12.
//



#include <bits/stdc++.h>

using namespace std;

class GroupBackpacks {
public:
    int solve_by_recursion(const int &index, const int &volume) {

        if (!index) { return 0; }

        if (dp[index][volume]) {
            return dp[index][volume];
        }

        int res{0};
        for (int idx = 1; idx < group_volume[index].size(); ++idx) {
            if (volume < group_volume[index][idx]) {
                res = max(res, solve_by_recursion(index - 1, volume));
            } else {
                res = max(res, solve_by_recursion(index - 1, volume - group_volume[index][idx])) +
                      group_value[index][idx];
                res = max(res, solve_by_recursion(index - 1, volume));
            }
        }
        return dp[index][volume] = res;
    }

private:

    vector<vector<int>> dp;

    vector<vector<int>> group_volume;

    vector<vector<int>> group_value;

    int total_volume;

};


int main() {
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) { break; }


    }

}
















