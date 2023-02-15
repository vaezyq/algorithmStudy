//
// Created by 王明龙 on 2023/2/15.
//

#include <bits/stdc++.h>

using namespace std;

class OceanFall {
public:

    bool is_center(const int &i, const int &j) {


    }

    void dfs(const int &x, const int &y, bool &flag) {

        visit[x][y] = true;


        if (is_center(x, y)) {
            flag = 1;
        }
        for (auto &i: direct) {
            auto nx = x + i[0];
            auto ny = y + i[1];
            if (visit[nx][ny] == 0 && map[nx][ny] == '#') {
                dfs(nx, ny, flag);
            }
        }
    }

    int get_result() {

        auto res{0};
        for (int i = 1; i < map.size() - 1; ++i) {
            for (int j = 1; j < map.size() - 1; ++j) {
                if (!visit[i][j] && map[i][j] == '#') {
                    bool flag = false;
                    dfs(i, j, flag);
                    if (flag) {
                        res++;
                    }
                }
            }
        }
        return res;
    }


private:
    vector<vector<int>> direct{{-1, 0},
                               {1,  0},
                               {0,  -1},
                               {0,  1}};

    vector<vector<char>> map;

    vector<vector<bool>> visit;

};

int main() {

}