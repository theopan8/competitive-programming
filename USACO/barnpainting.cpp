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
#include <bitset>
#include <cstring>
#include <limits>
using namespace std;
#define ll long long
const int maxn = 100010;
const long long mod = 1000000007;
vector<int> graph[maxn];
int colors[maxn];
ll dp[4][maxn];
void dfs (int u, int p) {
    int num = 0;
    ll val[4] = {1, 1, 1, 1};
    for(int v : graph[u]) {
        if (v != p) {
            num++;
            dfs(v, u);
            val[1] = (val[1] * (dp[2][v] + dp[3][v])) % mod;
            val[2] = (val[2] * (dp[1][v] + dp[3][v])) % mod;
            val[3] = (val[3] * (dp[2][v] + dp[1][v])) % mod;
        }
    }
    if (num == 0) {
        if (colors[u] == 0) {
            dp[1][u] = 1;
            dp[2][u] = 1;
            dp[3][u] = 1;
        }
        else {
            dp[colors[u]][u] = 1;
        }
    }
    else {
        if (colors[u] == 0) {
            dp[1][u] = val[1];
            dp[2][u] = val[2];
            dp[3][u] = val[3];
        }
        else {
            dp[colors[u]][u] = val[colors[u]];
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for(int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        colors[x] = y;
    }
    dfs(1, -1);
    cout << (dp[1][1] + dp[2][1] + dp[3][1]) % mod << endl;
}