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
using namespace std;
#define maxn 505
#define ll long long
#define mod 1000000007
char grid[maxn][maxn];
int dp[2][maxn][maxn];
int main() {
    //freopen("palpath.in", "r", stdin);
    //freopen("palpath.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            char x; cin >> x;
            grid[i][j] = x;
        }
    }
    //base case
    for(int i = 1; i < n; i++) {
        if (i == 1) {
            if (grid[i-1][n-i-1] == grid[i][n-i]) {
                dp[0][i][1] = 2;
            }
            if (grid[i][n-i-2] == grid[i][n-i]) {
                dp[0][i][2] = 1;
            }
            continue;
        }
        if (i == n-1) {
            if (grid[i-2][n-i] == grid[i][n-i]) {
                dp[0][i][i-1] = 1;
            }
            if (grid[i-1][n-i-1] == grid[i][n-i]) {
                dp[0][i][i] = 2;
            }
            continue;
        }
        if (grid[i-2][n-i] == grid[i][n-i]) {
            dp[0][i][i-1] = 1;
        }
        if (grid[i-1][n-i-1] == grid[i][n-i]) {
            dp[0][i][i] = 2;
        }
        if (grid[i][n-i-2] == grid[i][n-i]) {
            dp[0][i][i+1] = 1;
        }
    }
    /*cout << "first" << endl;
    for(int i = 1; i < n; i++) {
        cout << i << " " << n-i << endl;
        for(int j = 1; j < n; j++) {
            cout << j << " " << dp[0][i][j] << endl;
        }
        cout << endl;
    }*/
    for(int i = n+1; i <= 2*(n-1); i++) {
        //i is the sum of the coord
        //j is the x-coord
        for(int j = i-(n-1); j < n; j++) {
            //k is the x-coord of corresponding diagonal
            for(int k = 0; k <= 2*(n-1) - i; k++) {
                if (grid[j][i-j] == grid[k][2*(n-1) - i - k]) {
                    int total = 0;
                    if (dp[0][j-(i-(n-1))+1][k+2] != 0) {
                        total = (dp[0][j-(i-(n-1))+1][k+2] + total) % mod;
                    }
                    if (dp[0][j-(i-(n-1))+1][k+1] != 0) {
                        total = (dp[0][j-(i-(n-1))+1][k+1] + total) % mod;
                    }
                    if (dp[0][j-(i-(n-1))+2][k+2] != 0) {
                        total = (dp[0][j-(i-(n-1))+2][k+2] + total) % mod;
                    }
                    if (dp[0][j-(i-(n-1))+2][k+1] != 0) {
                        total = (dp[0][j-(i-(n-1))+2][k+1] + total) % mod;
                    }
                    dp[1][j-(i-(n-1))+1][k+1] = total;
                    //cout << i << " " << j-(i-(n-1))+1 << " " << k+1 << " " << total << endl;
                }
            }
        }
        for(int phat = 0; phat <= n; phat++) {
            for(int phet = 0; phet <= n; phet++) {
                dp[0][phat][phet] = dp[1][phat][phet];
                dp[1][phat][phet] = 0;
            }
        }
    }
    /*cout << "second" << endl;
    for(int i = 2; i < n; i++) {
        cout << i << " " << n+1-i << endl;
        for(int j = 1; j < n-1; j++) {
            cout << j << " " << dp[i][n+1-i][j] << endl;
        }
        cout << endl;
    }*/
    cout << dp[0][1][1] << endl;
}