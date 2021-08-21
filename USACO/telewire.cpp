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
#define maxn 100010
#define maxh 110
#define ll long long
#define pii pair<int,int>
ll dp[2][maxh];
vector<ll> height;
int main() {
    ios_base::sync_with_stdio(0);
    int n, c; cin >> n >> c;
    int max_height = 0;
    for(int i = 0; i < n; i++) {
        int h; cin >> h;
        height.push_back(h);
        max_height = max(max_height, h);
    }
    for(int i = height[0]; i <= max_height; i++) {
        dp[0][i] = (i-height[0])*(i-height[0]);
    }
    for(int i = 1; i < n; i++) {
        for(int j = height[i]; j <= max_height; j++) {
            int mini = -1;
            for(int k = height[i-1]; k <= max_height; k++) {
                if (mini == -1 || dp[0][k] + (j-height[i])*(j-height[i]) + c*abs(k-j) < mini) {
                    mini = dp[0][k] + (j-height[i])*(j-height[i]) + c*abs(k-j);
                }
            }
            dp[1][j] = mini;
        }
        for(int j = 0; j <= max_height; j++) {
            dp[0][j] = dp[1][j];
            dp[1][j] = 0;
        }
    }
    int ans = -1;
    for(int i = height[n-1]; i <= max_height; i++) {
        if (ans == -1 || ans > dp[0][i]) {
            ans = dp[0][i];
        }
    }
    cout << ans << endl;
}