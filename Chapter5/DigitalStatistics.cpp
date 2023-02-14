//
// Created by 王明龙 on 2023/2/14.
//
#include <bits/stdc++.h>

using namespace std;

const int N = 16;

typedef long long ll;

class DigitalStatistics {

public:
    explicit DigitalStatistics(ll num) : num(num) {
        new_dp.assign(N, vector<ll>(N, -1));

        nums.assign(1, 0);

        auto temp(num);
        while (temp) {         //分别计算每一位
            nums.emplace_back(temp % 10);
            temp /= 10;
        }
    }


    ll solve_by_dfs(const int &index, const int &sum, bool lead, bool limit, const int &now) {


        ll ans = 0;
        if (!index) { return sum; }
        if (!lead && !limit && new_dp[index][sum] != -1) {

//            cout << "index: " << index << ",sum: " << sum << ",lead: " << lead << ",limit: " << limit << ",now: " << now
//                 << endl;
            return new_dp[index][sum];
        }
        ll up = (limit ? nums[index] : 9);   //这一位的最大值(标明是否有数位限制)
        for (int i = 0; i <= up; ++i) {
            if (i == 0 && lead) {       //当前位是0并且有前导0
                ans += solve_by_dfs(index - 1, sum, true, i == up && limit, now);
            } else if (i == now) {
                ans += solve_by_dfs(index - 1, sum + 1, false, limit && i == up, now);
            } else if (i != now) {
                ans += solve_by_dfs(index - 1, sum, false, limit && i == up, now);
            }
        }
        if (!lead && !limit) {
            new_dp[index][sum] = ans;
        }

//        cout << "index: " << index << ",sum: " << sum << ",lead: " << lead << ",limit: " << limit << ",now: " << now
//             << endl;
        return ans;
    }


    std::shared_ptr<vector<ll>> get_result() {
        std::shared_ptr<vector<ll>> num_count = make_shared<vector<ll>>();

//        solve_by_dfs(nums.size() - 1, 0, true, true, 9);
        for (int i = 0; i < 10; ++i) {
            ll temp = solve_by_dfs(nums.size() - 1, 0, true, true, i);
//            cout << temp << endl;
            num_count->emplace_back(temp);
        }
        return num_count;
    }

private:
    vector<vector<ll>> new_dp;

    vector<ll> nums;

    ll num;
};

int main() {
//    ll left{0}, right{0};
//    cin >> left >> right;
//    DigitalStatistics digitalStatistics(left - 1);
//    DigitalStatistics digitalStatistics2(right);
//    auto num_count = digitalStatistics.get_result();
//    auto num_count2 = digitalStatistics2.get_result();
//    for (int i = 0; i < num_count->size(); ++i) {
//        cout << num_count2->at(i) - num_count->at(i) << " ";
//    }

    DigitalStatistics digitalStatistics2(324);
    digitalStatistics2.get_result();

    return 0;
}










