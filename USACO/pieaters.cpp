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
#include <stack>
#include <cstring>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, pair<int, int> > pip;
#define MAXN 310
vector<pip> intervs;
ll dp[MAXN][MAXN];
ll precomp[MAXN][MAXN][MAXN];
int main() {
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        ll w; cin >> w;
        int x, y; cin >> x >> y;
        intervs.push_back(pip(w, pii(x, y)));
    }
    for(pip i : intervs) {
        for(int j = i.second.first; j <= i.second.second; j++) {
            precomp[i.second.first][i.second.second][j] = max(precomp[i.second.first][i.second.second][j], i.first);
        }
    }
    for(int i = 1; i < n; i++) {
        for(int l = 1; l + i <= n; l++) {
            int r = l + i;
            for(int k = l; k <= r; k++) {
                precomp[l][r][k] = max(precomp[l][r][k], max(precomp[l+1][r][k], precomp[l][r-1][k]));
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int l = 1; l + i <= n; l++) {
            int r = l + i;
            for(int k = l; k <= r; k++) {
                dp[l][r] = max(dp[l][r], dp[l][k-1] + dp[k+1][r] + precomp[l][r][k]);
            }
        }
    }
    cout << dp[1][n] << endl;
}