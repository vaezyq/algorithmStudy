//
// Created by 王明龙 on 2023/2/12.
//



#include <bits/stdc++.h>

using namespace std;

class GroupBackpacks {
public:

    GroupBackpacks(const vector<vector<int>> &groupVolume, const vector<vector<int>> &groupValue, int totalVolume)
            : group_volume(groupVolume), group_value(groupValue), total_volume(totalVolume) {
        dp.assign(groupValue.size(), vector<int>(totalVolume + 1, 0));
    }

    int solve_by_recursion(const int &index, const int &volume) {

        if (!index) { return 0; }

        if (dp[index][volume]) {
            return dp[index][volume];
        }

        int res{0};
        for (int idx = 1; idx < group_volume[index].size(); ++idx) {

            res = max(res, solve_by_recursion(index - 1, volume));
            if (volume >= group_volume[index][idx]) {
                res = max(res,
                          solve_by_recursion(index - 1, volume - group_volume[index][idx]) + group_value[index][idx]);
            }
        }
        return dp[index][volume] = res;
    }

    void solve_by_iterate() {
        for (int i = 1; i < group_volume.size(); ++i) {
            for (int j = 1; j <= total_volume; ++j) {
                for (int k = 1; k <= total_volume; ++k) {
                    if (group_volume[i][k] > j) {
                        dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                    } else {
                        dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                        dp[i][j] = max(dp[i][j], dp[i - 1][j - group_volume[i][k]] + group_value[i][k]);
                    }
                }
            }
        }
    }


    int get_result() {
//        solve_by_recursion(group_volume.size() - 1, total_volume);
//        return dp[dp.size() - 1][dp[0].size() - 1];

        solve_by_iterate();
        return dp[dp.size() - 1][dp[0].size() - 1];
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
        vector<vector<int>> group_value(n + 1, vector<int>(m + 1, 0));

        vector<vector<int>> group_volume(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> group_value[i][j];
                group_volume[i][j] = j;
            }
        }

        GroupBackpacks groupBackpacks(group_volume, group_value, m);

        cout << groupBackpacks.get_result() << endl;
    }

}
















