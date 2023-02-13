//
// Created by 王明龙 on 2023/2/13.
//
#include <bits/stdc++.h>

using namespace std;

const int MAX = 0x7FFFFFFF;

class ConvertStrings {
public:

    ConvertStrings(const string &str, const string &str2) : str(str), str2(str2) {
        dp.assign(str.size() + 1, vector<int>(str2.size() + 1, MAX));
    }

    int solve_by_recursion(const int &index, const int &index2) {

        if (!index) { return index2; }
        if (!index2) { return index; }
        if (dp[index][index2] != MAX) { return dp[index][index2]; }

        int res = 0;
        if (str[index - 1] == str2[index2 - 1]) {
            res = solve_by_recursion(index - 1, index2 - 1);
        } else {
            res = solve_by_recursion(index, index2 - 1) + 1;
            res = min(res, solve_by_recursion(index - 1, index2) + 1);
            res = min(res, solve_by_recursion(index - 1, index2 - 1) + 1);
        }
        return dp[index][index2] = res;
    }


private:
    vector<vector<int>> dp;
    string str;
    string str2;
};

int main() {
    string str, str2;
    cin >> str >> str2;
    ConvertStrings convertStrings(str, str2);
    cout << convertStrings.solve_by_recursion(str.size(), str2.size());
    return 0;
}