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
#define maxl 55
#define maxt 8
int l, t;
ll switches = 0;
ll fork = 0;
int dp[maxl][(1 << maxt)][maxl];
int main() {
    ios_base::sync_with_stdio(0);
    cin >> l >> t;
    for(int i = 0; i < l; i++) {
        char x; cin >> x;
        if (x == '1') {
            switches += (1 << i);
        }
    }
    bool zero = true;
    int sub_fact = 0;
    for(int i = 0; i < t; i++) {
        char x; cin >> x;
        if (zero && x == '0') {
            sub_fact += 1;
            continue;
        }
        zero = false;
        if (x == '1') {
            fork += (1 << i);
        }
    }
    //removes empty tongs from the front and end of the fork
    fork = (fork >> sub_fact);
    t = trunc(log2(fork))+1;
    for(int i = 0; i <= l-t; i++) {
        for(int j = 0; j < (1 << t); j++) {
            for(int k = 0; k <= i+1; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    cout << "fork: " << fork << endl;
    cout << "len_fork: " << t << endl;
    cout << "switches: " << switches << endl;
    cout << "len_switch " << l << endl;
    for(int i = 0; i <= l-t; i++) {
        for(int j = 0; j < (1 << t); j++) {
            for(int k = 0; k <= i+1; k++) {
                if (((j & (1 << (t-1))) >> (t-1)) != ((switches & (1 << (i+t-1))) >> (i+t-1))) {
                    //cout << "hi10" << endl;
                    continue;
                }
                if (i == 0) {
                    if (k == 0) {
                        dp[i][switches & ((1 << t)-1)][k] = 1 - ((switches & ((1 << t)-1)) & 1);
                        cout << i << " " << (switches & ((1 << t)-1)) << " " << k << " " << dp[i][switches & ((1 << t)-1)][k] << endl;
                        continue;
                    }
                    dp[i][(switches & ((1 << t)-1)) ^ fork][k] = 1 - (((switches & ((1 << t)-1)) ^ fork) & 1);
                    cout << i << " " << ((switches & ((1 << t)-1)) ^ fork) << " " << k << " " << dp[i][(switches & ((1 << t)-1)) ^ fork][k] << endl;
                    continue;
                }
                //also have to check that t'th character is equal to the switches character
                //done with above
                if (k == 0) {
                    ll new_lights = ((j & ((1 << (t-1)) - 1)) << 1) + 1;
                    ll new_lights2 = ((j & ((1 << (t-1)) - 1)) << 1);
                    if (dp[i-1][new_lights][k] != -1) {
                        dp[i][j][k] = dp[i-1][new_lights][k] + 1 - (j & 1);
                    }
                    if (dp[i-1][new_lights2][k] != -1) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i-1][new_lights2][k] + 1 - (j & 1));
                    }
                    cout << i << " " << j << " " << k << " " << dp[i][j][k] << endl;
                    if (dp[i][j][k] == -1) {
                        continue;
                    }
                    if (i == l-t) {
                        dp[i][j][k] += t - __builtin_popcount(j) - 1 + (j & 1);
                    }
                    continue;
                }
                ll prev_lights = ((j & ((1 << (t-1)) - 1)) << 1) + 1;
                ll prev_lights2 = ((j & ((1 << (t-1)) - 1)) << 1);
                ll new_j = j ^ fork;
                ll new_lights = ((new_j & ((1 << (t-1)) - 1)) << 1) + 1;
                ll new_lights2 = ((new_j & ((1 << (t-1)) - 1)) << 1);
                if (dp[i-1][prev_lights][k] != -1) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][prev_lights][k] + 1 - (j & 1));
                }
                if (dp[i-1][prev_lights2][k] != -1) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][prev_lights2][k] + 1 - (j & 1));
                }
                if (dp[i-1][new_lights][k-1] != -1) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][new_lights][k-1] + 1 - (j & 1));
                }
                if (dp[i-1][new_lights2][k-1] != -1) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][new_lights2][k-1] + 1 - (j & 1));
                }
                cout << i << " " << j << " " << k << " " << dp[i][j][k] << endl;
                if (dp[i][j][k] == -1) {
                    continue;
                }
                if (i == l-t) {
                    dp[i][j][k] += t - __builtin_popcount(j) - 1 + (j & 1);
                }
            }
        }
    }
    int max_lights = 0;
    int num_forks = 0;
    for(int i = 0; i < (1 << t); i++) {
        for(int j = 0; j <= l-t+1; j++) {
            cout << i << " " << j << " " << dp[1][i][j] << endl;
            if (dp[l-t][i][j] == -1) {
                continue;
            }
            if (max_lights < dp[l-t][i][j]) {
                max_lights = dp[l-t][i][j];
                num_forks = j;
            }
            else if (max_lights == dp[l-t][i][j]) {
                if (num_forks > j) {
                    num_forks = j;
                }
            }
        }
    }
    cout << num_forks << endl;
}