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
typedef long long ll;
typedef pair<int, int> pii;
#define MAXN 1010
#define MAXK 10
ll dist[MAXN][MAXN];
ll cows[MAXN];
ll dp[MAXK][MAXN];
int n;
int x;
void solve(int i, int l, int r, int y, int z) {
    if (y > z) return;
	if (l > r) return;
    int curr = (l + r) / 2;
	ll mini = dp[i - 1][curr + 1];
	int idx = curr + 1;
	for(int k = y; k <= z; k++) {
		if (mini >= dp[i - 1][k] + dist[(curr + x) % n][(k - 1 + n + x) % n]) {
			mini = dp[i - 1][k] + dist[(curr + x) % n][(k - 1 + n + x) % n];
			idx = k;
		}
	}
	dp[i][curr] = mini;
	solve(i, l, curr - 1, (l + curr - 1) / 2 + 1, idx);
	solve(i, curr + 1, r, idx, z);
}
int main() {
    //freopen("cbarn.in", "r", stdin);
    //freopen("cbarn.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
    	cin >> cows[i];
    }
    for(int i = 0; i < n; i++) {
    	for(int j = i + 1; j < i + n; j++) {
    		dist[i][j % n] = dist[i][(j - 1 + n) % n] + (j - i) * cows[j % n];
    	}
    }
    ll ans = dist[0][n - 1];
    for(x = 0; x < n; x++) {
    	for(int i = x; i < x + n; i++) {
    		dp[1][i - x] = dist[i % n][(x + n - 1) % n];
    	}
    	for(int a = 2; a <= k; a++) {
    		solve(a, 0, n - 1, (n - 1) / 2 + 1, n - 1);
    	}
    	ans = min(ans, dp[k][0]);
    	/*for(int i = 1; i <= k; i++) {
    		cout << i << ": ";
    		for(int j = 0; j < n; j++) {
    			cout << dp[i][j] << " ";
    		}
    		cout << endl;
    	}*/
    	memset(dp, 0, sizeof(dp));
    }
    cout << ans << endl;
}