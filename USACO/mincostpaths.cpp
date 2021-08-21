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
#include <deque>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXM = 200010;
ll col[MAXM];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    for(int i = 1; i <= m; i++)
        cin >> col[i];
    if(max(n, m) <= 2000) {
        vector<vector<ll>> dp(n + 1, vector<ll>(m + 1));
        for(ll i = 1; i <= n; i++) {
            for(ll j = 1; j <= m; j++) {
                if(i == 1 && j == 1) continue;
                if(i == 1) dp[i][j] = dp[i][j - 1] + i * i;
                else if(j == 1) dp[i][j] = dp[i - 1][j] + col[j];
                else dp[i][j] = min(dp[i - 1][j] + col[j], dp[i][j - 1] + i * i);
            }
        }
        int q; cin >> q;
        while(q--) {
            int x, y; cin >> x >> y;
            cout << dp[x][y] << '\n';
        }
    }
    else {
        int q; cin >> q;
        while(q--) {
            int x, y; cin >> x >> y;
            int l = 0;
            int r = x - 1;
            while(l != r) {
                int mid1 = (2 * l + r) / 3;
                int mid2 = (l + 2 * r) / 3;
                double large = 1e18 + 1;
                
            }
        }

    }
}