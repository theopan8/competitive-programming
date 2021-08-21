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
#define pii pair<int, int>
const int maxn = 100010;
int a[maxn];
int b[maxn];
vector<int> friends[maxn];
ll st[maxn << 2];
ll lazy[maxn << 2];
int left (int p) {
    return (p << 1);
}
int right (int p) {
    return (p << 1) + 1;
}
void push (int p, int L, int R) {
    st[p] = max(st[p], lazy[p]);
    if (L != R) {
        lazy[left(p)] = max(lazy[left(p)], lazy[p]);
        lazy[right(p)] = max(lazy[right(p)], lazy[p]);
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
    st[p] = max(st[left(p)], st[right(p)]);
}
ll query (int p, int L, int R, int i, int j) {
    push(p, L, R);
    if (i > R || j < L) {
        return 0;
    }
    if (L >= i && R <= j) {
        return st[p];
    }
    return max(query(left(p), L, (L+R)/2, i, j), query(right(p), (L+R)/2 + 1, R, i, j));
}
int main() {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
		a[x] = i;
    }
    for(int i = 1; i <= n; i++) {
    	int x; cin >> x;
    	b[x] = i;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = max(i - 4, 0); j <= min(i + 4, n); j++) {
            friends[a[i]].push_back(b[j]);
        }
    }
    for(int i = 1; i <= n; i++) {
        sort(friends[i].begin(), friends[i].end());
        for(int j = friends[i].size() - 1; j >= 0; j--) {
            update(1, 1, n, friends[i][j], n, query(1, 1, n, friends[i][j] - 1, friends[i][j] - 1) + 1);
        }
    }
    cout << query(1, 1, n, n, n) << endl;
}