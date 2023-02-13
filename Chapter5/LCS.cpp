//
// Created by 王明龙 on 2023/2/13.
//

#include <bits/stdc++.h>

using namespace std;


class LCS {

public:
    LCS(const string &str, const string &str2) : str(str), str2(str2) {
        dp.assign(str.size() + 1, vector<int>(str2.size() + 1, 0));
    }


    int solve_by_recursion(const int &index, const int &index2) {
        if (index == 0 || index2 == 0) { return 0; }

        if (dp[index][index2] != 0) {
            return dp[index][index2];
        }
        if (str[index - 1] == str[index2 - 1]) {
            dp[index][index2] = solve_by_recursion(index - 1, index2 - 1) + 1;
        } else {
            dp[index][index2] = max(solve_by_recursion(index - 1, index2), solve_by_recursion(index, index2 - 1));
        }
        return dp[index][index2];
    }

    int get_result() {
        return solve_by_recursion(str.size(), str2.size());
    }

private:
    vector<vector<int>> dp;
    string str;
    string str2;

};


int main() {
    LCS lcs("abcde", "ace");
    cout << lcs.get_result();
    int a = 1;
    return 0;
}