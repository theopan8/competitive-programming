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
#define maxn 510
#define int long long
vector<int> members_prefix;
int dp[maxn][maxn];
vector<int> costs;
main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    members_prefix.push_back(0);
    int curr_prefix = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        curr_prefix += x;
        members_prefix.push_back(curr_prefix);
    }
    for(int i = 0; i < n; i++) {
        int c; cin >> c;
        costs.push_back(c);
    }
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < n-i; j++) {
            if (i == 1) {
                dp[j][j+i] = (members_prefix[j+i+1] - members_prefix[j])*min(costs[j], costs[j+i]);
                continue;
            }
            int mini = -1;
            for(int k = j; k <= j+i-1; k++) {
                if (mini == -1 || mini > dp[j][k] + dp[k+1][j+i] + (members_prefix[j+i+1] - members_prefix[j])*min(costs[k], costs[k+1])) {
                    mini = dp[j][k] + dp[k+1][j+i] + (members_prefix[j+i+1] - members_prefix[j])*min(costs[k], costs[k+1]);
                }
            }
            dp[j][j+i] = mini;
        }
    }
    /*for(int i = 1; i < n; i++) {
        for(int j = 0; j < n-i; j++) {
            cout << j << " " << j+i << " " << dp[j][j+i] << endl;
        }
    }*/
    cout << dp[0][n-1];
}
