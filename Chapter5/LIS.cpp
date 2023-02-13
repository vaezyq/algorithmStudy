//
// Created by 王明龙 on 2023/2/13.
//

#include <bits/stdc++.h>

using namespace std;

class LIS {
public:
    explicit LIS(const vector<int> &sequence) : sequence(sequence) {
        dp.assign(sequence.size(), 1);
    }

    int solve_by_recursion(const int &index) {

        if (dp[index] != 1) { return dp[index]; }

        for (int i = index - 1; i >= 0; --i) {
            if (sequence[index] > sequence[i]) {
//                cout << 2 << endl;
                dp[index] = max(dp[index], solve_by_recursion(i) + 1);
            }
        }
        return dp[index];
    }

    int get_result() {
        for (int i = 0; i < sequence.size(); ++i) {
            solve_by_recursion(i);
        }
        return *max_element(dp.begin(), dp.end());
    }


private:
    vector<int> dp;
    vector<int> sequence;
};


int main() {
    vector<int> sequence{5, 6, 7, 4, 2, 8, 3};
    LIS lis(sequence);
    cout << lis.get_result();
    return 0;
}







