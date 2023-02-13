//
// Created by 王明龙 on 2023/2/13.
//

#include <bits/stdc++.h>

using namespace std;

class MinimumPartition {
public:
    explicit MinimumPartition(const vector<int> &seq) : seq(seq) {
        volume = (std::accumulate(seq.begin(), seq.end(), 0) >> 1);
        dp.assign(seq.size() + 1, vector<int>(volume + 1, 0));
    }

    void solve_by_recursion() {
        for (int i = 1; i < dp.size(); ++i) {
            for (int j = 0; j <= volume; ++j) {
                if (seq[i - 1] > j) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - seq[i - 1]] + seq[i - 1]);
                }
            }
        }
    }

    int get_result() {

        solve_by_recursion();
        return std::abs((dp[dp.size() - 1][dp[0].size() - 1] << 1) -
                        std::accumulate(seq.begin(), seq.end(), 0));
    }


private:
    vector<vector<int>> dp;
    vector<int> seq;
    int volume;
};


int main() {
    vector<int> seq{1, 6, 11, 5};
    MinimumPartition minimumPartition(seq);
    cout << minimumPartition.get_result();
    return 0;
}









