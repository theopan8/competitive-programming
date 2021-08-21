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
#define MAXN 262154
#define MAXK 65
int vals[MAXN];
int dp[MAXK][MAXN];
int main() {
    freopen("262144.in", "r", stdin);
    freopen("262144.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> vals[i];
    }
    for(int i = 1; i <= n; i++) {
        dp[vals[i]][i] = i;
        for(int j = vals[i] + 1; j < MAXK; j++) {
            if (dp[j - 1][i] != 0 && dp[j - 1][dp[j - 1][i] - 1] != 0) {
                dp[j][i] = dp[j - 1][dp[j - 1][i] - 1];
            }
            else break;
        }
    }
    int ans = 0;
    for(int i = 0; i < MAXK; i++) {
        for(int j = 1; j <= n; j++) {
            if (dp[i][j] != 0) ans = max(ans, i);
        }
    }
    cout << ans << endl;
}