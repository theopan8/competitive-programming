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
const int MAXN = 70;
const ll MOD = 1000000007;
int grid[MAXN][MAXN];
ll countt[MAXN << 1][MAXN << 1][MAXN];
ll countt10[MAXN << 1][MAXN][MAXN];
ll countt01[MAXN][MAXN << 1][MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, k, q; cin >> n >> k >> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            char c; cin >> c;
            grid[i][j] = c - '0';
        }
    }
    for(int i = 1; i <= n; i++)
        countt[i][i][1] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int h = 1; h <= n; h++) {
                countt10[i][j][2] = (countt10[i][j][2] + count[i][h][1] * grid[h][j]) % MOD;
                countt01[i][j][2] = (countt01[i][j][2] + grid[i][h] * count[h][j][1]) % MOD;
            }
        }
    }
    for(int h = 2; h <= k; h++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                
            }
        }
    }
    while(q--) {
        int bs, s, bt, t;
    }

}