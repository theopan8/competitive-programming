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
#include <limits>
using namespace std;
#define maxn 200005
#define ll long long
ll st[maxn << 2];
ll lazy[maxn << 2];
ll minst[maxn << 2];
int left (int p) {
    return (p << 1);
}
int right (int p) {
    return (p << 1) + 1;
}
void push (int p, int L, int R) {
    st[p] += (lazy[p])*(R-L + 1);
    minst[p] += lazy[p];
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
    minst[p] = min(minst[left(p)], minst[right(p)]);
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
ll querymin (int p, int L, int R, int i, int j) {
    push(p, L, R);
    if (i > R || j < L) {
        return numeric_limits<int>::max();
    }
    if (L >= i && R <= j) {
        return minst[p];
    }
    return min(querymin(left(p), L, (L+R)/2, i, j), querymin(right(p), (L+R)/2 + 1, R, i, j));
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++) {
        int haybale; cin >> haybale;
        update(1, 0, n-1, i, i, haybale);
    }
    for(int i = 0; i < q; i++) {
        char x; cin >> x;
        if (x == 'M') {
            int a, b; cin >> a >> b;
            cout << querymin(1, 0, n-1, a-1, b-1) << endl;
        }
        else if (x == 'S') {
            int a, b; cin >> a >> b;
            cout << query(1, 0, n-1, a-1, b-1) << endl;
        }
        else {
            int a, b, c; cin >> a >> b >> c;
            update(1, 0, n-1, a-1, b-1, c);
        }
    }
}
