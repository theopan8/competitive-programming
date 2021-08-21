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
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define MAXN 200010
struct edge {
    int w, u, v;
    bool operator <(const edge &other) const {
        return (this->w < other.w) || (this->w == other.w && this->u < other.u) || (this->w == other.w && this->u == other.u && this->v < other.v);
    }
    bool operator ==(const edge &other) const {
        return (this->w == other.w) && (this->u == other.u) && (this->v == other.v);
    }
};
int p[MAXN];
vector<pii> graph[MAXN];
int types[MAXN];
vector<edge> edges;
ll st[MAXN << 2];
pii parents[MAXN];
map<int, set<pii> > adj[MAXN];
multiset<int> maxes[MAXN];
int findSet(int i) {
    if (p[i] == i) {
        return (i);
    }
    else {
        p[i] = findSet(p[i]);
        return (p[i]);
    }
}
void unionSet(int i, int j) {
    int x = findSet(i); int y = findSet(j);
    if (x != y) {
        p[x] = y;
    }
}
void dfs(int u, int p, int w) {
    parents[u] = pii(w, p);
    for(pii e : graph[u]) {
        if (e.first != p) dfs(e.first, u, e.second);
    }
}
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
    return min(p1, p2);
}
void update (int p, int L, int R, int i, int val) {
    if (L > i || R < i) {
        return;
    }
    if (L == i && R == i) {
        st[p] = val;
        return;
    }
    update(left(p), L, (L+R)/2, i, val);
    update(right(p), (L+R)/2 + 1, R, i, val);
    st[p] = min(st[left(p)], st[right(p)]);
}
int main() {
    //freopen("grass.in", "r", stdin);
    //freopen("grass.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, m, k, q; cin >> n >> m >> k >> q;
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        if (u == v) continue;
        edges.push_back(edge{w, u, v});
    }
    for(int i = 1; i <= n; i++) {
        cin >> types[i];
    }
    sort(edges.begin(), edges.end());
    for(int i = 1; i <= n; i++) {
        p[i] = i;
    }
    for(edge e : edges) {
        if (findSet(e.u) != findSet(e.v)) {
            graph[e.u].push_back(pii(e.v, e.w));
            graph[e.v].push_back(pii(e.u, e.w));
            unionSet(e.u, e.v);
        }
    }
    dfs(1, 0, -1);
    for(int i = 1; i <= n; i++) {
        for(pii e : graph[i]) {
            if (e.first != parents[i].second) {
                adj[i][types[e.first]].insert(pii(e.second, e.first));
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        if (i != 1 && graph[i].size() == 1) {
            update(1, 1, n, i, 1000001);
            continue;
        }
        for(auto idx = adj[i].begin(); idx != adj[i].end(); idx++) {
            if (idx->first == types[i]) continue;
            if ((idx->second).size() == 0) continue;
            maxes[i].insert((*(idx->second).begin()).first);
        }
        if (maxes[i].size() == 0) update(1, 1, n, i, 1000001);
        else update(1, 1, n, i, *maxes[i].begin());
    }
    while (q--) {
        int a, b; cin >> a >> b;
        if (adj[a][b].size() != 0) maxes[a].erase(maxes[a].find((*adj[a][b].begin()).first));
        if (adj[a][types[a]].size() != 0) maxes[a].insert((*adj[a][types[a]].begin()).first);
        if (maxes[a].size() != 0) update(1, 1, n, a, *maxes[a].begin());
        else update(1, 1, n, a, 1000001);
        maxes[parents[a].second].erase(maxes[parents[a].second].find((*adj[parents[a].second][types[a]].begin()).first));
        adj[parents[a].second][types[a]].erase(pii(parents[a].first, a));
        if (adj[parents[a].second][types[a]].size() != 0) maxes[parents[a].second].insert((*adj[parents[a].second][types[a]].begin()).first);
        if (adj[parents[a].second][b].size() != 0) maxes[parents[a].second].erase(maxes[parents[a].second].find((*adj[parents[a].second][b].begin()).first));
        adj[parents[a].second][b].insert(pii(parents[a].first, a));
        maxes[parents[a].second].insert((*adj[parents[a].second][b].begin()).first);
        if (maxes[parents[a].second].size() != 0) update(1, 1, n, parents[a].second, *maxes[parents[a].second].begin());
        else update(1, 1, n, parents[a].second, 1000001);
        cout << query(1, 1, n, 1, n) << endl;
        types[a] = b;
    }
}