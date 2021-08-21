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
using namespace std;
#define maxn 1010
#define maxk 11
#define mod 1000000009
#define int long long
vector<int> fj;
vector<int> fp;
int dp[maxk][maxn][maxn];// dp[num of cows chosen so far][curr_cow][last chosen cow]
int n, m, k;
int prefix_sum[maxk][maxn][maxn];
main() {
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        fj.push_back(x);
    }
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        fp.push_back(x);
    }
    sort(fj.begin(), fj.end());
    sort(fp.begin(), fp.end());
    for(int i = 1; i <= k; i++) {
        for(int j = 0; j < n; j++) {
            for(int h = 0; h < m; h++) {
                if (i == 1) {
                    if (fj[j] > fp[h]) {
                        dp[i][j][h] = 1;
                    }
                    if (j == 0 && h == 0) {
                        prefix_sum[i][j][h] = dp[i][j][h];
                    }
                    else if (j == 0) {
                        prefix_sum[i][j][h] = (prefix_sum[i][j][h-1] + dp[i][j][h]) % mod;
                    }
                    else if (h == 0) {
                        prefix_sum[i][j][h] = (prefix_sum[i][j-1][h] + dp[i][j][h]) % mod;
                    }
                    else {
                        prefix_sum[i][j][h] = (prefix_sum[i][j-1][h] + prefix_sum[i][j][h-1] - prefix_sum[i][j-1][h-1] + dp[i][j][h]) % mod;
                    }
                    //cout << i << " " << j << " " << h << " " << dp[i][j][h] << endl;
                    continue;
                }
                if (min(j, h) + 1 < i) {
                    if (j == 0 && h == 0) {
                        prefix_sum[i][j][h] = dp[i][j][h];
                    }
                    else if (j == 0) {
                        prefix_sum[i][j][h] = (prefix_sum[i][j][h-1] + dp[i][j][h]) % mod;
                    }
                    else if (h == 0) {
                        prefix_sum[i][j][h] = (prefix_sum[i][j-1][h] + dp[i][j][h]) % mod;
                    }
                    else {
                        prefix_sum[i][j][h] = (prefix_sum[i][j-1][h] + prefix_sum[i][j][h-1] - prefix_sum[i][j-1][h-1] + dp[i][j][h]) % mod;
                    }
                    continue;
                }
                if (fj[j] <= fp[h]) {
                    if (j == 0 && h == 0) {
                        prefix_sum[i][j][h] = dp[i][j][h];
                    }
                    else if (j == 0) {
                        prefix_sum[i][j][h] = (prefix_sum[i][j][h-1] + dp[i][j][h]) % mod;
                    }
                    else if (h == 0) {
                        prefix_sum[i][j][h] = (prefix_sum[i][j-1][h] + dp[i][j][h]) % mod;
                    }
                    else {
                        prefix_sum[i][j][h] = (prefix_sum[i][j-1][h] + prefix_sum[i][j][h-1] - prefix_sum[i][j-1][h-1] + dp[i][j][h]) % mod;
                    }
                    continue;
                }
                dp[i][j][h] = prefix_sum[i-1][j-1][h-1];
                //cout << i << " " << j << " " << h << " " << dp[i][j][h] << endl;
                prefix_sum[i][j][h] = (prefix_sum[i][j-1][h] + prefix_sum[i][j][h-1] - prefix_sum[i][j-1][h-1] + dp[i][j][h]) % mod;
            }
        }
    }
    int total = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            total = (total + dp[k][i][j]) % mod;
        }
    }
    if (total >= 0) {
        cout << total << endl;
    }
    else {
        cout << total + mod << endl;
    }
}