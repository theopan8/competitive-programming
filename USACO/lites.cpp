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
#define ll long long
ll st[maxn << 2];
ll lazy[maxn << 2];
int left (int p) {
    return (p << 1);
}
int right (int p) {
    return (p << 1) + 1;
}
void push (int p, int L, int R) {
    if ((lazy[p]%2) != 0) {
        st[p] = (R-L+1) - st[p];
    }
    //st[p] = st[p] + (lazy[p])*(R - L + 1);
    if (L != R) {
        lazy[left(p)] += lazy[p];
        lazy[right(p)] += lazy[p];
    }
    lazy[p] = 0;
}
void update (int p, int L, int R, int i, int j, int val) {
    push(p, L, R);
    if (i > R || j < L) {
        return;
    }
    if (L >= i && R <= j) {
        lazy[p] = val;
        push(p, L, R);
        return;
    }
    update(left(p), L, (L+R)/2, i, j, val);
    update(right(p), (L+R)/2 + 1, R, i, j, val);
    st[p] = st[left(p)] + st[right(p)];
}
ll query (int p, int L, int R, int i, int j) {
    push(p, L, R);
    if (i > R || j < L) {
        return 0;
    }
    if (L >= i && R <= j) {
        return st[p];
    }
    return query(left(p), L, (L+R)/2, i, j) + query(right(p), (L+R)/2 + 1, R, i, j);
}
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        if (x == 0) {
            int s, e; cin >> s >> e;
            update(1, 0, n-1, s-1, e-1, 1);
        }
        else {
            int s, e; cin >> s >> e;
            cout << query(1, 0, n-1, s-1, e-1) << endl;
        }
    }
}
