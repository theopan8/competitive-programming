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
#include <iterator>
using namespace std;
const int maxn = 10010;
int dp[maxn];
int cows[maxn];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> cows[i];
    }
    int max_val = 0;
    for(int i = 0; i <= k - 1; i++) {
        max_val = max(max_val, cows[i]);
        dp[i] = (i + 1) * max_val;
    }
    for(int i = k; i < n; i++) {
        int maxi = 0;
        int maxVal = 0;
        for(int j = i; j >= i - k + 1; j--) {
            maxVal = max(maxVal, cows[j]);
            int val = dp[j - 1] + (i - j + 1) * maxVal;
            maxi = max(val, maxi);
        }
        dp[i] = maxi;
    }
    cout << dp[n - 1] << endl;
}