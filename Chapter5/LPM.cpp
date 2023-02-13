//
// Created by 王明龙 on 2023/2/13.
//

#include <bits/stdc++.h>

using namespace std;


class LongestPathMatrix {

public:

    int solve(const int &row, const int &col) {
        if (row == 0 || col == 0) { return 0; }

        for(int i=0;i<direct.size();++i){
         if(matrix[])


        }
    }

private:
    vector<vector<int>> matrix;

    vector<vector<int>> direct{{-1, 0},
                               {1,  0},
                               {0,  1},
                               {0,  -1}};

};