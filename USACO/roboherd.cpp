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
#define maxn 100010
vector<ll> values[maxn];
int KC = 0;
int N = -1;
void numberOfAffordableCows(int i, int j, int C) {
    if (KC > 0) {
        KC--;
        if (j + 1 < values[i].size() && (values[i][j + 1] - values[i][j]) <= C) {
            numberOfAffordableCows(i, j + 1, C - (values[i][j + 1] - values[i][j]));
        }
        i++;
        while (i < N && values[i][1] <= C && KC > 0) {
            numberOfAffordableCows(i, 1, C - values[i][1]);
            i++;
        }
    }
}
int main() {
    //freopen("roboherd.in", "r", stdin);
    //freopen("roboherd.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    int minCost = 0;
    for(int i = 0; i < n; i++) {
        int m; cin >> m;
        if (m == 1) {
            ll x; cin >> x;
            minCost += x;
            continue;
        }
        N++;
        for(int j = 0; j < m; j++) {
            ll x; cin >> x;
            values[i].push_back(x);
        }
        sort(values[i].begin(), values[i].end());
    }
    for(int i = 0; i < n; i++) {
        minCost += values[i][0];
        for(int j = 0; j < values[i].size(); j++) {
            values[i][j] -= values[i][0];
        }
    }
    ll low = 0;
    ll high = (ll)1 << 45;
    while (low < high - 1) {
        ll avg = (low + high) / 2;
        KC = k;
        numberOfAffordableCows(0, 0, avg);
        if (KC <= 0) {
            low = avg;
        }
        else {
            high = avg;
        }
    }
    
}