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
vector<pip> bonuses;
int skills[maxn][maxn];
int dp[2][1 << maxn];
int main() {
    ios_base::sync_with_stdio(0);
    int n, b; cin >> n >> b;
    for(int i = 0; i < b; i++) {
        int k, p, a; cin >> k >> p >> a;
        bonuses.push_back(pip(k, pii(p,a)));
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int x; cin >> x;
            skills[i][j] = x;
        }
    }
    sort(bonuses.begin(), bonuses.end());
    int curr_bonus = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < (1 << n); j++) {
            if (__builtin_popcount(j) != i+1) {
                continue;
            }
            if (i == 0) {
                if (curr_bonus < b && bonuses[curr_bonus].first == i+1) {
                    int largest = 0;
                    for(int k = 0; k < n; k++) {
                        if ((j & (1 << k)) != 0) {
                            largest = max(largest, skills[k][i]);
                        }
                    }
                    if (largest >= bonuses[curr_bonus].second.first) {
                        largest += bonuses[curr_bonus].second.second;
                    }
                    int incr = 1;
                    while (curr_bonus + incr < b && bonuses[curr_bonus+incr].first == i+1) {
                        if (largest >= bonuses[curr_bonus+incr].second.first) {
                            largest += bonuses[curr_bonus+incr].second.second;
                            incr += 1;
                        }
                        else {
                            break;
                        }
                    }
                    dp[0][j] = largest;
                    continue;
                }
                int largest = 0;
                for(int k = 0; k < n; k++) {
                    if ((j & (1 << k)) != 0) {
                        largest = max(largest, skills[k][i]);
                    }
                }
                dp[0][j] = largest;
                continue;
            }
            if (curr_bonus < b && bonuses[curr_bonus].first == i+1) {
                int largest = 0;
                for(int k = 0; k < n; k++) {
                    if ((j & (1 << k)) != 0) {
                        largest = max(largest, dp[0][(j & (~(1 << k)))] + skills[k][i]);
                    }
                }
                if (largest >= bonuses[curr_bonus].second.first) {
                    largest += bonuses[curr_bonus].second.second;
                }
                int incr = 1;
                while (curr_bonus + incr < b && bonuses[curr_bonus+incr].first == i+1) {
                    if (largest >= bonuses[curr_bonus+incr].second.first) {
                        largest += bonuses[curr_bonus+incr].second.second;
                        incr += 1;
                    }
                    else {
                        break;
                    }
                }
                dp[1][j] = largest;
                continue;
            }
            int largest = 0;
            for(int k = 0; k < n; k++) {
                if ((j & (1 << k)) != 0) {
                    largest = max(largest, dp[0][(j & (~(1 << k)))] + skills[k][i]);
                }
            }
            dp[1][j] = largest;
            
        }
        if (curr_bonus < b && bonuses[curr_bonus].first == i+1) {
            curr_bonus += 1;
        }
        while (curr_bonus < b && bonuses[curr_bonus].first == i+1) {
            curr_bonus += 1;
        }
        if (i == 0) {
            continue;
        }
        for(int j = 0; j < (1 << n); j++) {
            dp[0][j] = dp[1][j];
            dp[1][j] = 0;
        }
    }
    cout << dp[0][(1 << n) - 1] << endl;
}