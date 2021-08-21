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
#define maxn 200005
#define ll long long
struct interval {
	int x, y;
};
vector<interval> intervals;
ll st[maxn << 2];
int left (int p) {
    return (p << 1);
}
int right (int p) {
    return (p << 1) + 1;
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
    return p1 + p2;
}
void update (int p, int L, int R, int i, int val) {
    if (L > i || R < i) {
        return;
    }
    if (L == i && R == i) {
        st[p] += val;
        return;
    }
    st[p] += val;
    update(left(p), L, (L+R)/2, i, val);
    update(right(p), (L+R)/2 + 1, R, i, val);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    //freopen("photo.in", "r", stdin);
    //freopen("photo.out", "w", stdout);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
    	int x, y; cin >> x >> y;
    	intervals.push_back(interval{x, y});
    }
}