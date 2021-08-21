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
#define maxn 2010
#define pii pair<int,long double>
#define inf numeric_limits<long double>::max()
long double dp[maxn];
vector<pii> graph[maxn];
long double rolling_max[maxn];
int main() {
    ios_base::sync_with_stdio(0);
    int n, m, a, b; long double v; cin >> n >> m >> v >> a >> b;
    for(int i = 0; i < m; i++) {
        int x, y; long double e; cin >> x >> y >> e;
        graph[y].push_back(pii(x,e));
    }
    for(int i = 1; i <= n; i++) {
        dp[i] = inf;
    }
    dp[a] = v;
    for(int i = 0; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 0; k < graph[j].size(); k++) {
                dp[j] = min(dp[j], dp[graph[j][k].first]*graph[j][k].second);
            }
        }
    }
    bool bad = false;
    for(int j = 1; j <= n; j++) {
        for(int k = 0; k < graph[j].size(); k++) {
            if (dp[j] > dp[graph[j][k].first]*graph[j][k].second) {
                bad = true;
            }
        }
    }
    if (bad) {
        cout << 0 << endl;
    }
    else {
        cout << (long long)(floor(dp[b])) << endl;
    }
}