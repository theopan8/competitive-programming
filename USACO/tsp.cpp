#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <cstdio>
#include <utility> 
#include <queue>
#include <math.h>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
using namespace std;
#define maxn 21
#define maxb 1 << 20
#define pii pair<int,int>
vector<pii> graph[maxn];
int dp[maxn][maxb];
int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int v1, v2, d; cin >> v1 >> v2 >> d;
        graph[v1].push_back(pii(v2, d));
        graph[v2].push_back(pii(v1, d));
    }
    //__builtin_popcount
    for(int i = 0; i < 1 << (n); i++) {
        for(int j = 1; j <= n; j++) {
            if (((i & (1 << (j-1))) == 0) || (__builtin_popcount(i) == 1)) {
                continue;
            }
            int min = -1;
            for(pii v: graph[j]) {
                if ((i & (1 << (v.first - 1))) == 0) {
                    continue;
                }
                if (dp[v.first][i & ~(1 << (j-1))] == 0 && (i & ~(1 << (j-1))) != 0 && __builtin_popcount((i & ~(1 << (j-1)))) != 1) {
                    continue;
                }
                if (min == -1) {
                    min = dp[v.first][i & ~(1 << (j-1))] + v.second;
                }
                else if (min > dp[v.first][i & ~(1 << (j-1))] + v.second) {
                    min = dp[v.first][i & ~(1 << (j-1))] + v.second;
                }
            }
            if (min == -1) {
                continue;
            }
            else {
                dp[j][i] = min;
            }
        }
    }
    int min = -1;
    for(int i = 1; i <= n; i++) {
        //cout << dp[i][(1<<n) - 1] << endl;
        if (dp[i][(1 << n)-1] == 0) {
            continue;
        }
        if (min == -1) {
            min = dp[i][(1 << n)-1];
        }
        else if (min > dp[i][(1 << n)-1]) {
            min = dp[i][(1 << n)-1];
        }
    }
    if (min == -1) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << min << endl;
    }
}