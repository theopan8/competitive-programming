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
#define maxn 4010
#define pii pair<int,int>
#define int long long
int dp[maxn][maxn];
vector<pii> memes;
main() {
    ios_base::sync_with_stdio(0);
    int n, r; cin >> n >> r;
    for(int i = 0; i < n; i++) {
        int rec, d; cin >> rec >> d;
        memes.push_back(pii(rec, d));
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= r; j++) {
            if (i == 0) {
                if (memes[i].first <= r) {
                    dp[i][memes[i].first] = memes[i].second;
                }
                break;
            }
            if (j < memes[i].first) {
                dp[i][j] = dp[i-1][j];
                continue;
            }
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-memes[i].first] + memes[i].second);
        }
    }
    int max = 0;
    for(int i = 0; i <= r; i++) {
        if (dp[n-1][i] > max) {
            max = dp[n-1][i];
        }
    }
    cout << max << endl;
}