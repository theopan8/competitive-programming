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
#define maxn 100005
#define pii pair<long long, long long>
#define pip pair<long long, pair<long long, long long> >
#define ll long long
#define INF 100000000000LL
vector<pip> slingshots;
vector<pii> queries;
ll st[maxn << 2];
bool comp (pip i, pip j) {
    return i.second.first < j.second.first;
}
bool comp1 (pii i, pii j) {
    return i.first < i.second;
}
int left (int p) {
    return (p << 1);
}
int right (int p) {
    return (p << 1) + 1;
}
ll rmq (int p, int L, int R, int i, int j) {
    if (i > R || j < L) {
        return -1;
    }
    if (L >= i && R <= j) {
        return st[p];
    }
    ll p1 = rmq(left(p), L, (L+R)/2, i , j);
    ll p2 = rmq(right(p), (L+R)/2 + 1, R, i, j);
    if (p1 == -1) {
        return p2;
    }
    if (p2 == -1) {
        return p1;
    }
    return min(p1,p2);
}
void update (int p, int L, int R, int i, int val) {
    if (L > i || R < i) {
        return;
    }
    st[p] += val;
    update(left(p), L, (L+R)/2, i, val);
    update(right(p), (L+R)/2 + 1, R, i, val);
}
int main() {
    //freopen("slingshot.in", "r", stdin);
    //freopen("slingshot.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < n; i++) {
        ll x, y, t; cin >> x >> y >> t;
        if (y - x <= t) {
            continue;
        }
        slingshots.push_back(pip(t, pii(x,y)));
    }
    sort(slingshots.begin(), slingshots.end(), comp);
    for(int i = 0; i < m; i++) {
        ll x, y; cin >> x >> y;
        queries.push_back(pii(x,y));
    }
}