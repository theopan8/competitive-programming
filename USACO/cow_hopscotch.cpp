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
#define ll long long
const int maxn = 760;
const int maxk = 562510;
const long long mod = 1000000007;
ll dp[maxn][maxn];
ll bit[maxn][maxn];
int cows[maxn][maxn];
ll query(int idx, int idy){
    ll sum = 0;
    while (idx > 0) {
        while (idy > 0) {
            sum = (sum + bit[idx][idy]) % mod;
            idy -= (idy & -idy);
        }
        idx -= (idx & -idx);
    }
    return sum;
}
void update(int idx, int idy, ll val){
    while (idx <= maxn) {
        while (idy <= maxn) {
            bit[idx][idy] = (bit[idx][idy] + val) % mod;
            idy += (idy & -idy);
        }
        idx += (idx & -idx);
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    //freopen("hopscotch.in", "r", stdin);
    //freopen("hopscotch.out", "w", stdout);
    int r, c, k; cin >> r >> c >> k;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            cin >> cows[i][j];
        }
    }
    
}