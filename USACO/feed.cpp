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
#define maxn 510
#define maxk 10010
#define ll long long
vector<pip> stores;
ll dp[maxn][maxk];
int main() {
    ios_base::sync_with_stdio(0);
    int k, e, n; cin >> k >> e >> n;
    for(int i = 0; i < n; i++) {
        int x, f, c; cin >> x >> f >> c;
        stores.push_back(pip(x, pii(f,c)));
    }
    sort(stores.begin(), stores.end());
    priority_queue<pii> q;
    for(int i = 0; i <= k; i++) {
        if (i <= stores[0].second.first) {
            dp[0][i] = stores[0].second.second*i;
            q.push(pii(-(dp[0][i] + (stores[1].first - stores[0].first)*i*i - stores[1].second.second*i), i));
            cout << i << " " << (dp[0][i] + (stores[1].first - stores[0].first)*i*i - stores[1].second.second*i) << endl;
        }
    }
    priority_queue<pii> dup;
    for(int i = 1; i < n; i++) {
        for(int j = k; j >= 0; j--) {
            while (q.top().second > j) {
                q.pop();
            }
            if (j - q.top().second > stores[i].second.first) {
                continue;
            }
            if (i == n-1) {
                dp[i][j] = -(q.top().first) + stores[i].second.second*j;
                continue;
            }
            dp[i][j] = -(q.top().first) + stores[i].second.second*j;
            dup.push(pii(-(dp[i][j] + (stores[i+1].first - stores[i].first)*j*j - stores[i+1].second.second*j), j));
        }
        q = dup;
        while (!dup.empty()) {
            dup.pop();
        }
    }
    for(int i = 0; i < n; i++) {
        cout << i << endl;
        for(int j = 0; j <= k; j++) {
            cout << j << " " << dp[i][j] << endl;
        }
        cout << endl;
    }
    cout << dp[n-1][k] + (e-stores[n-1].first)*k*k << endl;
}