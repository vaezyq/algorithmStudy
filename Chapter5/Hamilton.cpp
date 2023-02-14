//
// Created by 王明龙 on 2023/2/14.
//

#include <bits/stdc++.h>

using namespace std;

const double MAX = 0x77FFFFFF;

class Hamilton {
public:

    double get_distance(const unsigned &a, const unsigned &b) {
        return sqrt(pow(cor[a][0] - cor[b][0], 2) + pow(cor[a][1] - cor[b][1], 2));
    }

    Hamilton(const vector <vector<double>> &cor, int n) : cor(cor), N(n) {
        dp.assign(1 << n, vector<double>(n, MAX));

        dist.assign(N, vector<double>(N, 0));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i != j) {
                    dist[i][j] = get_distance(i, j);
                }
            }
        }

    }


    void solve() {

        for (int i = 0; i < N; ++i) {
            dp[1 << (i)][i] = dist[0][i];
        }

        for (int s = 1; s < dp.size(); ++s) {
            for (int u = 0; u < N; ++u) {
                if ((s >> u) & 1) {
                    for (int v = 0; v < N; ++v) {
                        if ((s ^ (1 << u)) >> v & 1) {
                            dp[s][u] = min(dp[s][u], dp[s ^ (1 << u)][v] + dist[u][v]);
                            continue;
                        }
                    }
                }
            }
        }
    }

    double get_result() {
        solve();

        return *min_element(dp[(1 << N) - 1].begin(), dp[(1 << N) - 1].end());
    }


private:
    vector <vector<double>> dp;
    vector <vector<double>> cor;
    vector <vector<double>> dist;
    int N;

};


int main() {
    int N{0};
    cin >> N;
    vector<vector<double>> cor(N + 1, vector<double>(2, 0));
    cor[0] = {0, 0};
    for (int i = 1; i < N + 1; ++i) {
        cin >> cor[i][0] >> cor[i][1];
    }
    Hamilton hamilton(cor, N + 1);

    cout << fixed << setprecision(2) << hamilton.get_result();
}