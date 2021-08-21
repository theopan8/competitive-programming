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
typedef pair<pair<int, int>, int> pip;
#define MAXN 100010
#define MAXK 19
vector<int> graph[MAXN];
int types[MAXN];
int parents[MAXN];
int depth[MAXN];
int ancestors[MAXK][MAXN];
vector<pip> queries;
vector<int> node[MAXN];
map<int, int> values[MAXN];
int curr[MAXN];
void dfs(int u, int p) {
    parents[u] = p;
    depth[u] = depth[p] + 1;
    for(int v : graph[u]) {
        if (v != p) dfs(v, u);
    }
}
void dfs1(int u, int p) {
    curr[types[u]]++;
    for(int c : node[u]) {
        values[u][c] = curr[c];
    }
    for(int v : graph[u]) {
        if (v != p) dfs1(v, u);
    }
    curr[types[u]]--;
}
int LCA (int a, int b) {
    if (depth[a] > depth[b]) {
        swap(a,b);
    }
    for(int j = MAXK - 1; j >= 0; j--) {
        if ((1 << j) & (depth[b] - depth[a])) {
            b = ancestors[j][b];
        }
    }
    if (a == b) {
        return a;
    }
    for(int j = MAXK - 1; j >= 0; j--) {
        if (ancestors[j][a] == ancestors[j][b]) {
            continue;
        }
        a = ancestors[j][a];
        b = ancestors[j][b];
    }
    return parents[a];
}
int main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> types[i];
    }
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(1, 0);
    for(int i = 0; i < MAXK; i++) {
        for(int j = 1; j <= n; j++) {
            if (i == 0) {
                ancestors[i][j] = parents[j];
                continue;
            }
            ancestors[i][j] = ancestors[i-1][ancestors[i-1][j]];
        }
    }
    for(int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        queries.push_back(pip(pii(a, b), c));
        node[a].push_back(c);
        node[b].push_back(c);
        node[parents[LCA(a, b)]].push_back(c);
    }
    dfs1(1, 0);
    for(pip q : queries) {
        int ans = values[q.first.first][q.second] + values[q.first.second][q.second] - 2 * values[parents[LCA(q.first.first, q.first.second)]][q.second];
        if (ans > 0) cout << 1;
        else cout << 0;
    }
}