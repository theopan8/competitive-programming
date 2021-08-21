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
#define pip pair<int, pair<int,int> >
#define pii pair<int,int>
#define maxn 22
vector<pip> cows;
int dp[2][(1 << maxn)];
int main() {
    ios_base::sync_with_stdio(0);
    int n, h; cin >> n >> h;
    for(int i = 0; i < n; i++) {
        int height, weight, strength; cin >> height >> weight >> strength;
        cows.push_back(pip(height, pii(weight, strength)));
    }
    int ans = -1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < (1 << n); j++) {
            if (__builtin_popcount(j) != i) {
                continue;
            }
            if (i == 1) {
                int largest = -1;
                for(int k = 0; k < n; k++) {
                    if ((j & (1 << k)) != 0) {
                        largest = max(largest, cows[k].second.second);
                        break;
                    }
                }
                dp[1][j] = largest;
                //cout << i << " " << j << " " << dp[1][j] << endl;
                continue;
            }
            int largest = -1;
            for(int k = 0; k < n; k++) {
                if ((j & (1 << k)) != 0) {
                    if (dp[0][(j & (~(1 << k)))] - cows[k].second.first >= 0) {
                        largest = max(largest, min(cows[k].second.second, dp[0][(j & (~(1 << k)))] - cows[k].second.first));
                    }
                }
            }
            dp[1][j] = largest;
            //cout << i << " " << j << " " << dp[1][j] << endl;
        }
        for(int j = 0; j < (1 << n); j++) {
            dp[0][j] = dp[1][j];
            dp[1][j] = 0;
        }
        bool bad = true;
        int max_safety = -1;
        for(int j = 0; j < (1 << n); j++) {
            if (__builtin_popcount(j) != i) {
                continue;
            }
            if (dp[0][j] == -1) {
                continue;
            }
            int height = 0;
            bad = false;
            for(int k = 0; k < n; k++) {
                if ((j & (1 << k)) != 0) {
                    height += cows[k].first;
                }
            }
            if (height >= h) {
                if (max_safety < dp[0][j]) {
                    max_safety = dp[0][j];
                }
            }
        }
        if (bad && ans == -1) {
            cout << "Mark is too tall" << endl;
            return 0;
        }
        if (max_safety > ans) {
            ans = max_safety;
        }
    }
    if (ans == -1) {
        cout << "Mark is too tall" << endl;
    }
    else {
        cout << ans << endl;
    }
}