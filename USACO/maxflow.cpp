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
#define MAXN 50010
#define MAXK 17
vector<int> graph[MAXN];
int parents[MAXN];
int depth[MAXN];
int ancestors[MAXK][MAXN];
int vals[MAXN];
int subtrees[MAXN];
void predfs(int u, int p) {
    depth[u] = depth[p] + 1;
    parents[u] = p;
    for(int v : graph[u]) {
        if (v != p) predfs(v, u);
    }
}
int LCA(int a, int b) {
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
void dfs(int u, int p) {
    int sum = 0;
    for(int v : graph[u]) {
        if (v != p) {
            dfs(v, u);
            sum += subtrees[v];
        }
    }
    subtrees[u] = vals[u] + sum;
}
int main() {
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    predfs(1, 0);
    for(int i = 0; i < MAXK; i++) {
        for(int j = 1; j <= n; j++) {
            if (i == 0) {
                ancestors[i][j] = parents[j];
                continue;
            }
            ancestors[i][j] = ancestors[i-1][ancestors[i-1][j]];
        }
    }
    for(int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        if (LCA(x, y) == x) {
            vals[y]++;
            vals[parents[LCA(x, y)]]--;
        }
        else if (LCA(x, y) == y) {
            vals[x]++;
            vals[parents[LCA(x, y)]]--;
        }
        else {
            vals[x]++;
            vals[y]++;
            vals[LCA(x, y)]--;
            vals[parents[LCA(x, y)]]--;
        }
        
    }
    dfs(1, 0);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, subtrees[i]);
    }
    cout << ans << endl;
}