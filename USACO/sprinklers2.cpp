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
using namespace std;
typedef long long ll;
#define MAXN 2010
#define MOD 1000000007
char grid[MAXN][MAXN];
int num[MAXN][MAXN];
ll dp[MAXN][MAXN];
ll actual[MAXN][MAXN];
ll sum[MAXN][MAXN];
ll powers[MAXN * MAXN];
int main() {
    freopen("sprinklers2.in", "r", stdin);
    freopen("sprinklers2.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> grid[i][j];
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if (grid[i][j] == '.') num[i][j] = num[i][j - 1] + 1;
            else num[i][j] = num[i][j - 1];
        }
    }
    powers[0] = 1;
    for(int i = 1; i <= n * n; i++)
        powers[i] = (powers[i-1] * (ll)2) % MOD;
    for(int i = 0; i <= n; i++) {
        if (i == 0) {
            dp[1][0] = powers[num[1][n]];
            if (grid[1][1] == '.') actual[1][0] = powers[num[1][n] - 1];
            continue;
        }
        if (i == n && grid[1][n] == '.') {
            dp[1][n] = powers[num[1][n - 1]];
            actual[1][n] = dp[1][n];
            continue;
        }
        if (i != 0 && i != n && grid[1][i] == '.') {
            int left = num[1][i - 1];
            int right = num[1][n] - num[1][i + 1];
            dp[1][i] = powers[num[1][n] - 1];
            if(grid[1][i + 1] == '.') actual[1][i] = powers[left + right];
        }
    }
    sum[1][0] = actual[1][0];
    for(int i = 1; i <= n; i++)
        sum[1][i] = (sum[1][i - 1] + actual[1][i]) % MOD;
    for(int i = 2; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            if (j == 0) {
                ll total = 0;
                for(int k = 1; k <= i; k++)
                    total += num[k][n];
                dp[i][j] = powers[total];
                if (grid[i][1] == '.') actual[i][j] = powers[total - 1];
                continue;
            }
            if (j == n) {
                dp[i][j] = (dp[i - 1][j] * powers[num[i][n]]) % MOD;
                if (grid[i][n] == '.') dp[i][j] = (dp[i][j] + (sum[i - 1][j - 1] * powers[num[i][j - 1]]) % MOD) % MOD;
                actual[i][j] = dp[i][j];
                continue;
            }
            dp[i][j] = (dp[i - 1][j] * powers[num[i][n]]) % MOD;
            if (grid[i][j] == '.') {
                dp[i][j] = (dp[i][j] + (sum[i - 1][j - 1] * powers[num[i][n] - 1]) % MOD) % MOD;
                if (grid[i][j + 1] == '.') actual[i][j] = (((dp[i - 1][j] * powers[num[i][n] - 1]) % MOD) + ((sum[i-1][j-1] * powers[num[i][n] - 2]) % MOD)) % MOD;
            }
            else if (grid[i][j + 1] == '.') actual[i][j] = (dp[i - 1][j] * powers[num[i][n] - 1]) % MOD;
        }
        sum[i][0] = actual[i][0];
        for(int j = 1; j <= n; j++) 
            sum[i][j] = (sum[i][j - 1] + actual[i][j]) % MOD;
    }
    cout << sum[n][n] << endl;
}