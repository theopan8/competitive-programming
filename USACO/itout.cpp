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
#include <cstring>
using namespace std;
#define ll long long
const int maxn = 100010;
vector<int> cows;
ll lis[maxn];
ll dp[maxn];
vector<ll> idxLIS[maxn]; //indexes of cows ordered according to lis[i] (decreasing order)
vector<ll> cowsLIS[maxn]; //array for storing lis cows
vector<int> tempNormalization[maxn];
vector<int> normalizationLIS[maxn]; //normalized lis cows
vector<int> indexOfCow;
ll st[maxn << 2];
vector<ll> st2[maxn];
int currLIS = 1;
bool comp (int i, int j) {
    return cowsLIS[currLIS][i] < cowsLIS[currLIS][j];
}
ll left (ll p) {
    return (p << 1);
}
ll right (ll p) {
    return (p << 1) + 1;
}
void update (int p, int L, int R, int i, ll val) {
    if (L > i || R < i) {
        return;
    }
    if (L == i && R == i) {
        st[p] = val;
        return;
    }
    st[p] = max(st[p], val);
    update(left(p), L, (L+R)/2, i, val);
    update(right(p), (L+R)/2 + 1, R, i, val);
}
ll query (int p, int L, int R, int i, int j) {
    if (i > R || j < L) {
        return -1;
    }
    if (L >= i && R <= j) {
        return st[p];
    }
    ll p1 = query(left(p), L, (L+R)/2, i , j);
    ll p2 = query(right(p), (L+R)/2 + 1, R, i, j);
    if (p1 == -1) {
        return p2;
    }
    if (p2 == -1) {
        return p1;
    }
    return max(p1, p2);
}
void update2 (int idx, int p, int L, int R, int i, ll val) {
    if (L > i || R < i) {
        return;
    }
    if (L == i && R == i) {
        st2[idx][p] += val;
        return;
    }
    st2[idx][p] += val;
    update2(idx, left(p), L, (L+R)/2, i, val);
    update2(idx, right(p), (L+R)/2 + 1, R, i, val);
}
ll query2 (int idx, int p, int L, int R, int i, int j) {
    if (i > R || j < L) {
        return -1;
    }
    if (L >= i && R <= j) {
        return st2[idx][p];
    }
    ll p1 = query2(idx, left(p), L, (L+R)/2, i , j);
    ll p2 = query2(idx, right(p), (L+R)/2 + 1, R, i, j);
    if (p1 == -1) {
        return p2;
    }
    if (p2 == -1) {
        return p1;
    }
    return max(p1, p2);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    //freopen("itout.in", "r", stdin);
    //freopen("itout.out", "w", stdout);
    ll n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        cows.push_back(x);
    }
    for(int i = n - 1; i >= 0; i--) {
        lis[i + 1] = query(1, 1, n, cows[i], n) + 1;
        update(1, 1, n, cows[i], lis[i + 1]);
    }
    ll len = 0;
    for(int i = 1; i <= n; i++) {
        len = max(len, lis[i]);
    }
    for(int i = n - 1; i >= 0; i--) {
        idxLIS[lis[i + 1]].push_back(i);
        cowsLIS[lis[i + 1]].push_back(cows[i]);
        indexOfCow[i] = cowsLIS[lis[i + 1]].size() - 1;
        tempNormalization[lis[i + 1]].push_back(cowsLIS[lis[i + 1]].size() - 1);
    }
    for(int i = 1; i <= len; i++) {
        currLIS = i;
        sort(tempNormalization[i].begin(), tempNormalization[i].end(), comp);
        for(int j = 0; j < tempNormalization[i].size(); j++) {
            normalizationLIS[i].push_back(0);
        }
    }
    for(int i = 1; i <= len; i++) {
        for(int j = 0; j < tempNormalization[i].size(); j++) {
            normalizationLIS[i][tempNormalization[i][j]] = j + 1;
        }
    }
    for(int i = 1; i <= len; i++) {
        for(int j = 0; j < normalizationLIS[i].size(); j++) {
            st2[i].push_back(0);
            st2[i].push_back(0);
            st2[i].push_back(0);
            st2[i].push_back(0);
        }
    }
    for(int i = n - 1; i >= 0; i--) {
        if (lis[i] == 1) {
            dp[i] = 1;
            update2(1, 1, 1, cowsLIS[i].size(), normalization[1][indexOfCow[i]], 1);
        }
        else {
            int asdf = lower_bound();
            dp[i] = query2(lis[i] - 1, 1, 1, cowsLIS[lis[i] - 1].size(), ..., ...);

        }
    }
}