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
#define maxn 10005
#define maxk 15
#define ll long long
#define pii pair<int,int>
vector<pii> adj[maxn];
int subsize[maxn];
int chainhead[maxn];
int dep[maxn];
int preorder[maxn];
int parents[maxn];
ll st[maxn << 2];
map<pii, int> edgeorder;
int ordertovert[maxn];
int ancestors[maxk][maxn];
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
    return max(p1,p2);
}
void update (int p, int L, int R, int i, int val) {
    if (L > i || R < i) {
        return;
    }
    if (i == L && i == R) {
        st[p] = val;
        return;
    }
    update(left(p), L, (L+R)/2, i, val);
    update(right(p), (L+R)/2 + 1, R, i, val);
    st[p] = max(st[left(p)], st[right(p)]);
}
void predfs(int u, int p) {
    dep[u] = p == -1 ? 1 : dep[p]+1;
    parents[u] = p == -1 ? 1 : p;
    subsize[u] = 1;
    for (pii v : adj[u]) {
        if (v.first == p) continue;
        predfs(v.first, u);
        subsize[u] += subsize[v.first];
    }
}
int numseen = 0;
void dfs(int u, int p, bool conn) {
    preorder[u] = ++numseen;
    if (conn) {
        chainhead[u] = chainhead[p];
    }
    else {
        chainhead[u] = u;
    }
   for (pii v : adj[u]) {
        if (v.first == p) continue;
        if (subsize[v.first] > subsize[u]/2) {
            dfs(v.first, u, true);
        }
    }
    for (pii v : adj[u]) {
        if (v.first == p) continue;
        if (subsize[v.first] <= subsize[u]/2) {
            dfs(v.first, u, false);
        }
    }
    /*int largest = -1;
    int vertex = -1;
    for(pii v : adj[u]) {
        if (v.first == p) continue;
        if (subsize[v.first] > largest) {
            vertex = v.first;
            largest = subsize[v.first];
            break;
        }
    }
    if (vertex == -1) {
        return;
    }
    dfs(vertex, u, true);
    for(pii v : adj[u]) {
        if (v.first == p || v.first == vertex) continue;
        dfs(v.first, u, false);
    }*/
}
void dfs2(int u, int p) {
    for (pii v : adj[u]) {
        if (v.first == p) continue;
        int order = edgeorder[pii(u,v.first)];
        ordertovert[order] = preorder[v.first];
        dfs2(v.first, u);
    }
}
int LCA (int a, int b) {
    if (dep[a] > dep[b]) {
        swap(a,b);
    }
    for(int j = maxk -1; j >= 0; j--) {
        if ((1 << j) & (dep[b] - dep[a])) {
            b = ancestors[j][b];
        }
    }
    if (a == b) {
        return a;
    }
    for(int j = maxk-1; j >= 0; j--) {
        if (ancestors[j][a] == ancestors[j][b]) {
            continue;
        }
        a = ancestors[j][a];
        b = ancestors[j][b];
    }
    return parents[a];
}
int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    for(int i = 0; i < t; i++) {
        int n; cin >> n;
        for(int j = 0; j < n-1; j++) {
            int a, b, c; cin >> a >> b >> c;
            adj[a].push_back(pii(b,c));
            adj[b].push_back(pii(a,c));
            edgeorder[pii(a,b)] = j+1;
            edgeorder[pii(b,a)] = j+1;
        }
        predfs(1, -1);
        dfs(1, -1, false);
        dfs2(1, -1);
        for(int j = 2; j <= n; j++) {
            for(pii v : adj[j]) {
                if (v.first == parents[j]) {
                    update(1, 1, n, preorder[j], v.second);
                    break;
                }
            }
        }
        for(int k = 0; k < maxk; k++) {
            for(int j = 1; j <= n; j++) {
                if (k == 0) {
                    ancestors[k][j] = parents[j];
                    continue;
                }
                ancestors[k][j] = ancestors[k-1][ancestors[k-1][j]];
            }
        }
        while (true) {
            string s; cin >> s;
            if (s == "DONE") {
                break;
            }
            if (s == "QUERY") {
                int x, y; cin >> x >> y;
                int ancestor = LCA(x,y);
                int ans = 0;
                while (true) {
                    if (x == ancestor) {
                        break;
                    }
                    if (dep[chainhead[x]] <= dep[ancestor]) {
                        int max = rmq(1, 1, n, preorder[ancestor], preorder[x]);
                        if (max > ans) {
                            ans = max;
                        }
                        break;
                    }
                    if (chainhead[x] == x) {
                        int max = rmq(1, 1, n, preorder[x], preorder[x]);
                        if (max > ans) {
                            ans = max;
                        }
                    }
                    else {
                        int max = rmq(1, 1, n, preorder[chainhead[x]], preorder[x]);
                        if (max > ans) {
                            ans = max;
                        }
                    }
                    x = parents[chainhead[x]];
                }
                while (true) {
                    if (y == ancestor) {
                        break;
                    }
                    if (dep[chainhead[y]] <= dep[ancestor]) {
                        int max = rmq(1, 1, n, preorder[ancestor], preorder[y]);
                        if (max > ans) {
                            ans = max;
                        }
                        break;
                    }
                    if (chainhead[y] == y) {
                        int max = rmq(1, 1, n, preorder[y], preorder[y]);
                        if (max > ans) {
                            ans = max;
                        }
                    }
                    else {
                        int max = rmq(1, 1, n, preorder[chainhead[y]], preorder[y]);
                        if (max > ans) {
                            ans = max;
                        }
                    }
                    y = parents[chainhead[y]];
                }
                cout << ans << endl;
            }
            else {
                int x, y; cin >> x >> y;
                update(1, 1, n, ordertovert[x], y);
            }
        }
        memset(adj, 0, sizeof(adj));
        memset(subsize, 0, sizeof(subsize));
        memset(chainhead, 0, sizeof(chainhead));
        memset(dep, 0, sizeof(dep));
        memset(preorder, 0, sizeof(preorder));
        memset(parents, 0, sizeof(parents));
        memset(st, 0, sizeof(st));
        edgeorder.clear();
        memset(ordertovert, 0, sizeof(ordertovert));
        memset(ancestors, 0, sizeof(ancestors));
        numseen = 0;
    }
}