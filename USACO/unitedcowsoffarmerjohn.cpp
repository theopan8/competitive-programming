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
#include <stack>
#include <cstring>
#include <deque>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 200010;
ll ans = 0;
ll temp[MAXN];
ll prev[MAXN];
struct node {
    int numzero, cnt; ll sum;
};
node st[MAXN << 2];
node lazy[MAXN << 2];
int left(int p) {
    return (p << 1);
}
int right(int p) {
    return (p << 1) + 1;
}
void merge(int p) {
    st[p].numzero = st[left(p)].numzero + st[right(p)].numzero;
    st[p].cnt = st[left(p)].cnt + st[right(p)].cnt;
    st[p].sum = st[left(p)].sum + st[right(p)].sum;
}
void push(int p, int L, int R) {
    st[p].sum += lazy[p] * (R - L + 1 - st[p].numzero);
    if(L != R) {
        lazy[left(p)] += lazy[p];
        lazy[right(p)] += lazy[p];
    }
    lazy[p] = 0;
}
void zeroupdate(int p, int L, int R, int i) {
    push(p, L, R);
    if(L > i || R < i) return;
    if(L == i && R == i) {
        st[p] = node{1, 0, 0};
        return;
    }
    update(left(p), L, (L + R)/2, i, val);
    update(right(p), (L + R)/2 + 1, R, i, val);
    merge(p);
}
void pntupdate(int p, int L, int R, int i, int val) {
    
}
void update(int p, int L, int R, int i, int j, int val) {
    push(p, L, R);
    if(i > R || j < L) return;
    if(L >= i && R <= j) {
        lazy[p] = val;
        push(p, L, R);
        return;
    }
    update(left(p), L, (L + R)/2, i, j, val);
    update(right(p), (L + R)/2 + 1, R, i, j, val);
    st[p] = st[left(p)] + st[right(p)];
}
ll query(int p, int L, int R, int i, int j) {
    push(p, L, R);
    if(i > R || j < L) return 0;
    if(L >= i && R <= j) return st[p];
    return query(left(p), L, (L + R)/2, i, j) + query(right(p), (L + R)/2 + 1, R, i, j);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        prev[i] = temp[x];
        temp[x] = i;
    }

}