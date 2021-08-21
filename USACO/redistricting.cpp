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
const int maxn = 300010;
int prefixSum[maxn];
int dp[maxn];
multiset<int> currPrefixValues[maxn];
multiset<int> currDPValues;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    freopen("redistricting.in", "r", stdin);
    freopen("redistricting.out", "w", stdout);
    int n, k; cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        char x; cin >> x;
        if (x == 'H') prefixSum[i] = prefixSum[i - 1] + 1;
        else prefixSum[i] = prefixSum[i - 1] - 1;
    }
    currDPValues.insert(0);
    currPrefixValues[0].insert(0);
    for(int i = 1; i <= n; i++) {
        int minDP = *(currDPValues.begin());
        int minPrefix = *(currPrefixValues[minDP].begin());
        if (minPrefix < prefixSum[i]) {
            dp[i] = minDP;
        }
        else {
            dp[i] = minDP + 1;
        }
        if (i >= k) {
            currDPValues.erase(currDPValues.find(dp[i - k]));
            currPrefixValues[dp[i - k]].erase(currPrefixValues[dp[i - k]].find(prefixSum[i - k]));
        }
        currDPValues.insert(dp[i]);
        currPrefixValues[dp[i]].insert(prefixSum[i]);
    }
    cout << dp[n] << endl;
}