//
// Created by 王明龙 on 2023/2/12.
//

#include <bits/stdc++.h>

using namespace std;


class Knapsack01 {

public:

    Knapsack01(const vector<int> &boneVolume, const vector<int> &boneValue, int totalVolume) : bone_volume(boneVolume),
                                                                                               bone_value(boneValue),
                                                                                               total_volume(
                                                                                                       totalVolume) {
        dp.assign(bone_volume.size(), vector<int>(total_volume + 1, 0));
    }


    int solve_by_recursion(const int &index, const int &volume) {

        if (dp[index][volume]) {
            return dp[index][volume];
        }
        if (!index) { return 0; }

        int res = 0;


        if (bone_volume[index] > volume) {
            res = solve_by_recursion(index - 1, volume);
        } else {
            res = max(solve_by_recursion(index - 1, volume),
                      solve_by_recursion(index - 1, volume - bone_volume[index]) + bone_value[index]);
        }
        return dp[index][volume] = res;
    }


    void solve_by_iterate() {
        for (int i = 1; i < dp.size(); ++i) {
            for (int volume = 0; volume <= total_volume; ++volume) {
                if (volume < bone_volume[i]) {
                    dp[i][volume] = dp[i - 1][volume];
                } else {
                    dp[i][volume] = max(dp[i - 1][volume], dp[i - 1][volume - bone_volume[i]] + bone_value[i]);
                }
            }
        }
    }

    //通过滚动数组解决
    int solve_by_iterate_scrolling_array() {
        vector<vector<int>> dp_scroll(2, vector<int>(total_volume + 1, 0));
        auto now{0}, old{1};

        cout << total_volume << endl;
        for (int i = 1; i < bone_volume.size(); ++i) {
            swap(old, now);
            for (int volume = 0; volume <= total_volume; ++volume) {
                if (volume < bone_volume[i]) {
                    dp_scroll[now][volume] = dp_scroll[old][volume];
                } else {
                    dp_scroll[now][volume] = max(dp_scroll[old][volume],
                                                 dp_scroll[old][volume - bone_volume[i]] + bone_value[i]);
                }
            }
        }
        return dp_scroll[now][total_volume];
    }


    int solve_by_iterate_self_scrolling_array() {
        vector<int> dp_scroll(total_volume + 1, 0);
        for (int i = 1; i < bone_volume.size(); ++i) {
            for (int volume = total_volume; volume >= bone_volume[i]; --volume) {
                dp_scroll[volume] = max(dp_scroll[volume], dp_scroll[volume - bone_volume[i]] + bone_value[i]);
            }
        }
        return dp_scroll[total_volume];
    }


    int get_result() {
//        return solve_by_recursion(bone_volume.size() - 1, total_volume);

//        solve_by_iterate();
//        return dp[bone_volume.size() - 1][total_volume];

//        return solve_by_iterate_scrolling_array();

        return solve_by_iterate_self_scrolling_array();
    }


    /*!
     * 得到最终的背包方案
     * @return
     */
    std::shared_ptr<vector<int>> get_scheme() {
        std::shared_ptr<vector<int>> scheme = std::make_shared<vector<int>>(bone_volume.size(), 0);
        auto volume{total_volume};
        for (auto i = bone_volume.size() - 1; i != 0; --i) {
            if (dp[i][volume] != dp[i - 1][volume]) {
                scheme->at(i) = 1;
                volume -= bone_value[i];
            }
        }
        return scheme;
    }


private:
    vector<vector<int>> dp;

    vector<int> bone_volume;

    vector<int> bone_value;

    int total_volume;
};


int main() {
    vector<int> bone_volume{0, 2, 3, 6, 5};
    vector<int> bone_value{0, 6, 3, 5, 4};
    int total_volume{9};

    Knapsack01 knapsack01(bone_volume, bone_value, total_volume);

    cout << knapsack01.get_result() << endl;
    auto scheme = knapsack01.get_scheme();
    for_each(scheme->begin(), scheme->end(), [](int i) {
        cout << i << " ";
    });
    cout << endl;
    return 0;
}







