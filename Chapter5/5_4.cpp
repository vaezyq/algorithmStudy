//
// Created by 王明龙 on 2023/2/13.
//
#include <bits/stdc++.h>

using namespace std;

const int N = 16;

typedef unsigned long long ull;

class DigitalStatistics {

public:
    DigitalStatistics(const ull &left, const ull &right) : left(left), right(right) {
        dp.assign(N, 0);
        ten_power.assign(N, 0);
        ten_power.at(0) = 1;

        for (int i = 1; i < N; ++i) {
            dp[i] = i * ten_power[i - 1];
            ten_power[i] = ten_power[i - 1] * 10;
        }
    }


    void solve(ull const &x, vector<ull> &num_cnt) {
        vector<int> num(1, 0);
        auto temp{x};
        while (temp) {         //分别计算每一位
            num.emplace_back(temp % 10);
            temp /= 10;
        }
        for (int i = num.size() - 1; i >= 1; --i) {
            for (int j = 0; j < 10; ++j) {
                num_cnt[j] += dp[i - 1] * num[i];
            }

            for (int j = 0; j < num[i]; ++j) {
                num_cnt[j] += ten_power[i - 1];
            }


            ull num2 = 0;

            for (int j = i - 1; j >= 1; --j) {
                num2 = num2 * 10 + num[j];
            }
            num_cnt[num[i]] += (num2 + 1);
            num_cnt[0] -= ten_power[i - 1];
        }
    }


    ull solve_by_dfs(const int &index, const int &sum, bool lead, bool limit) {
        ull ans = 0;
        if (!index) { return sum; }

    }


    void get_result() {
        vector<ull> num_cnt(10, 0);
        vector<ull> num_cnt2(10, 0);
        solve(left - 1, num_cnt);
        solve(right, num_cnt2);
        for (int i = 0; i < 10; ++i) {
            cout << num_cnt2[i] - num_cnt[i] << " ";
        }
    }


private:
    vector<ull> dp;
    vector<ull> ten_power;
    ull left;
    ull right;
};


int main() {
    ull left, right;
    cin >> left >> right;
    DigitalStatistics digitalStatistics(left, right);
    digitalStatistics.get_result();
}