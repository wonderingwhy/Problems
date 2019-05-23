#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

using namespace std;
#if 1
ifstream fin("C-large-practice.in");
ofstream fout("C-large-practice.out");
#define cin fin
#define cout fout
#endif
const int MAXN = 105;
int tri[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN];
int search(const vector<string> &data) {
    int max_depth = 0;
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            if (data[i][j] == '#') {
                int depth = -1;
                for (int k = i + 1; k < data.size(); ++k) {
                    for (int l = j - (k - i); l <= j + (k - i); ++l) {
                        if (l < 0 || l >= data[i].size() || data[k][l] != '#') {
                            depth = k - i;
                            break;
                        }
                    }
                    if (depth != -1) {
                        break;
                    }
                }
                if (depth == -1) {
                    depth = data.size() - i;
                }
                tri[i][j] = depth;
                dp[i][j][1] = depth * depth;
                max_depth = max(max_depth, depth);
            }
        }
    }
    return max_depth * max_depth;
}
int N, M, K;
int dfs(int cur_i, int cur_j, int cur_K) {
    if (cur_K == K) {
        return 0;
    }
    if (cur_i >= N || cur_j >= M || K - cur_K > N - cur_i) {
        return -1;
    }
    if (dp[cur_i][cur_j][K - cur_K] != -1) {
        return dp[cur_i][cur_j][K - cur_K];
    }
    int maxi = -1;
    int cur_h = tri[cur_i][cur_j];
    for (int h = 1; h <= cur_h; ++h) {
        for (int j = cur_j - h + 1; j < cur_j + h; ++j) {
            if (tri[cur_i + h][j]) {
                int ret = dfs(cur_i + h, j, cur_K + 1);
                if (ret != -1) {
                    int sum = ret + h * h;
                    maxi = max(maxi, sum);
                }
            }
        }
    }
    if (maxi != -1) {
        dp[cur_i][cur_j][K - cur_K] = maxi;
    }
    return maxi;
}

int main() {
    int T;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        memset(dp, -1, sizeof(dp));
        memset(tri, 0, sizeof(tri));
        cin >> N >> M >> K;
        vector<string> data;
        for (int i = 0; i < N; ++i) {
            string str;
            cin >> str;
            data.emplace_back(str);
        }
        search(data);
        int maxi = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (tri[i][j]) {
                    maxi = max(maxi, dfs(i, j, 0));
                }
            }
        }
        cout << "Case #" << cas << ": " << maxi << endl;
    }
    return 0;
}