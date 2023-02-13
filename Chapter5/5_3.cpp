//
// Created by 王明龙 on 2023/2/13.
//

#include <bits/stdc++.h>

using namespace std;


class MultipleBackpacks {

public:

    MultipleBackpacks(const vector<int> &volume, const vector<int> &value, const vector<int> &nums, int maxValue)
            : volume(volume), value(value), nums(nums), max_value(maxValue) {}

    void solve_by_iterate() {
        for (int i = 1; i < volume.size(); ++i) {
            for (int j = 1; i <= max_value; ++j) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                for (int k = 1; k * volume[i] <= j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][j - k * volume[i]]);
                }
            }
        }
    }


    int solve_by_iterate_binary_optimization() {
        vector<int> new_value(1, 0);
        vector<int> new_volume(1, 0);

        for (int i = 1; i < nums.size(); ++i) {

            for (int j = 1; j <= nums[i]; j <<= 1) {
                nums[i] -= j;
                new_value.emplace_back(j * value[i]);
                new_volume.emplace_back(j * volume[i]);
            }
            if (nums[i]) {
                new_value.emplace_back(nums[i] * value[i]);
                new_volume.emplace_back(nums[i] * volume[i]);
            }
        }

        vector<vector<int>> new_dp(new_value.size(), vector<int>(max_value + 1, 0));
        for (int i = 1; i < new_volume.size(); ++i) {
            for (int j = 0; j <= max_value; ++j) {
                if (j < new_volume[i]) {
                    new_dp[i][j] = new_dp[i - 1][j];
                } else {
                    new_dp[i][j] = max(new_dp[i - 1][j], new_dp[i - 1][j - new_volume[i]] + new_value[i]);
                }
            }
        }
        return new_dp[new_dp.size() - 1][max_value];
    }


    int solve_by_iterate_binary_optimization_by_scroll_array() {
        vector<int> new_value(1, 0);
        vector<int> new_volume(1, 0);

        for (int i = 1; i < nums.size(); ++i) {

            for (int j = 1; j <= nums[i]; j <<= 1) {
                nums[i] -= j;
                new_value.emplace_back(j * value[i]);
                new_volume.emplace_back(j * volume[i]);
            }
            if (nums[i]) {
                new_value.emplace_back(nums[i] * value[i]);
                new_volume.emplace_back(nums[i] * volume[i]);
            }
        }

        vector<vector<int>> new_dp(2, vector<int>(max_value + 1, 0));

        int now{0}, old{1};
        for (int i = 1; i < new_volume.size(); ++i) {
            swap(now, old);
            for (int j = 0; j <= max_value; ++j) {
                if (j < new_volume[i]) {
                    new_dp[now][j] = new_dp[old][j];
                } else {
                    new_dp[now][j] = max(new_dp[old][j], new_dp[old][j - new_volume[i]] + new_value[i]);
                }
            }
        }
        return new_dp[now][max_value];
    }


private:
    vector<vector<int>> dp;

    vector<int> volume;

    vector<int> value;

    vector<int> nums;

    int max_value;

};


int main() {


    int n{0}, max_value{0};
    cin >> n >> max_value;
    vector<int> volume(n + 1, 0);
    vector<int> value(n + 1, 0);
    vector<int> nums(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> value[i] >> volume[i] >> nums[i];
    }

    MultipleBackpacks multipleBackpacks(volume, value, nums, max_value);
    cout << multipleBackpacks.solve_by_iterate_binary_optimization_by_scroll_array();
    return 0;
}












