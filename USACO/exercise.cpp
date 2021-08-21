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
#define MAXN 200010
#define MAXK 20
vector<int> graph[MAXN];
vector<int> back[MAXN];
int parents[MAXN];
int depth[MAXN];
int ancestors[MAXK][MAXN];
void dfs(int u, int p) {
    parents[u] = p;
    depth[u] = depth[p] + 1;
    for(int v : graph[u])
        if(v != p) dfs(v, u);
}
int LCA(int a, int b) {
    if(depth[a] > depth[b]) swap(a,b);
    for(int j = MAXK - 1; j >= 0; j--)
        if((1 << j) & (depth[b] - depth[a]))
            b = ancestors[j][b];
    if(a == b) return a;
    for(int j = MAXK - 1; j >= 0; j--) {
        if(ancestors[j][a] == ancestors[j][b]) continue;
        a = ancestors[j][a];
        b = ancestors[j][b];
    }
    return parents[a];
}
int main() {
    //freopen("exercise.in", "r", stdin);
    //freopen("exercise.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(1, 0);
    for(int i = n - 1; i < m; i++) {
        int x, y; cin >> x >> y;
        if(depth[x] > depth[y]) back[x].push_back(y);
        else back[y].push_back(x);
    }
    for(int i = 0; i < MAXK; i++) {
        for(int j = 1; j <= n; j++) {
            if(i == 0) ancestors[i][j] = parents[j];
            else ancestors[i][j] = ancestors[i - 1][ancestors[i - 1][j]];
        }
    }
}