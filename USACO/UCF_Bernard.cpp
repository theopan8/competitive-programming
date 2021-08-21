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
#include <cstring>
using namespace std;
#define ll long long
#define maxn 100010
vector<ll> fishes;
ll dp[maxn];
int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        fishes.push_back(x);
    }
    ll curr_max = 0;
    for(int i = 0; i <= min(n-1,k); i++) {
        if (curr_max < fishes[i]) {
            curr_max = fishes[i];
        }
        dp[i] = curr_max;
    }
    for(int i = k+1; i < n; i++) {
        dp[i] = max(dp[i-1], dp[i-k-1] + fishes[i]);
    }
    cout << dp[n-1] << endl;
}