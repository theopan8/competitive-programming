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
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define MAXN 100010
vector<int> graph[MAXN];
int preorder[MAXN];
int subtrees[MAXN];
int pre = 0;
void dfs(int u, int p) {
    pre++;
    preorder[u] = pre;
    int tot = 1;
    for(int v : graph[u]) {
        if (v != p) {
            dfs(v, u);
            tot += subtrees[preorder[v]];
        }
    }
    subtrees[preorder[u]] = tot;
}
ll st[MAXN << 2];
ll lazy[MAXN << 2];
set<int> colors[MAXN];
int left (int p) {
    return (p << 1);
}
int right (int p) {
    return (p << 1) + 1;
}
void push (int p, int L, int R) {
    st[p] += (lazy[p])*(R-L + 1);
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
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, q; cin >> n >> q;
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(1, 0);
    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int x, c; cin >> x >> c;
            auto idx = colors[c].lower_bound(preorder[x]);
            if (*idx == preorder[x]) continue;
            if (idx != colors[c].begin()) {
                idx--;
                if (preorder[x] <= *idx + subtrees[*idx] - 1) continue;
            }
            auto begin = colors[c].lower_bound(preorder[x]);
            auto end = colors[c].upper_bound(preorder[x] + subtrees[preorder[x]] - 1);
            for(auto j = begin; j != end; j++) {
                update(1, 1, n, *j, *j + subtrees[*j] - 1, -1);
            }
            update(1, 1, n, preorder[x], preorder[x] + subtrees[preorder[x]] - 1, 1);
            colors[c].erase(begin, end);
            colors[c].insert(preorder[x]);
        }
        else {
            int x; cin >> x;
            cout << query(1, 1, n, preorder[x], preorder[x] + subtrees[preorder[x]] - 1) << endl;
        }
    }
}