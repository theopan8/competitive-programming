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
#define maxn 250010
#define pii pair<int,int>
vector<ll> values;
ll dp[maxn];
vector<ll> prefix;
ll sum = 0;
int par[maxn];
void replace (int n) {
    if (par[n] == -1) {
        return;
    }
    for(int i = par[n]+1; i < n; i++) {
        values[i] = (1 << 50);
    }
    replace(par[n]);
}
ll go (int n, int k) {
    ll curr = 0;
    prefix.push_back(curr);
    for(int i = 0; i < n; i++) {
        curr += values[i];
        sum += values[i];
        prefix.push_back(curr);
    }
    priority_queue<pii> q;
    q.push(pii(0, -1));
    for(int i = 0; i <= n; i++) {
        while (q.top().second < i-k-1) {
            q.pop();
        }
        dp[i] = q.top().first + prefix[i];
        par[i] = q.top().second;
        q.push(pii(dp[i] - prefix[i+1], i));
    }
    prefix.clear();
    ll ans = sum - dp[n];
    replace(n);
    curr = 0;
    sum = 0;
    for(int i = 0; i < n; i++) {
        curr += values[i];
        sum += values[i];
        prefix[i+1] = curr;
    }
    while (!q.empty()) {
        q.pop();
    }
    q.push(pii(0, -1));
    for(int i = 0; i <= n; i++) {
        while (q.top().second < i-k-1) {
            q.pop();
        }
        dp[i] = q.top().first + prefix[i];
        par[i] = q.top().second;
        q.push(pii(dp[i] - prefix[i+1], i));
    }
    return (ans + sum - dp[n]);
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    int total = 0;
    bool neg = false;
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        if (x < 0) {
            neg = true;
            values.push_back(abs(x));
        }
        else {
            total += x;
            if (neg) {
                int val = go(values.size(), k-1);
                prefix.clear();
                values.clear();
                neg = false;
                total -= (val);
                sum = 0;
            }
        }
    }
    cout << total << endl;
}