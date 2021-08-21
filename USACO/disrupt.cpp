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
#define MAXK 19
#define MAXN 50010
typedef long long ll;
typedef pair<int, int> pii;
map<pii, int> edges;
vector<int> graph[MAXN];
vector<int> toAdd[MAXN];
vector<int> toRem[MAXN];
int parents[MAXN];
int depth[MAXN];
int ancestors[MAXK][MAXN];
multiset<int> weights[MAXN];
int ans[MAXN];
void predfs(int u, int p) {
	parents[u] = p;
	depth[u] = depth[p] + 1;
	for(int v : graph[u]) {
		if (v != p) predfs(v, u);
	}
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
void dfs(int u) {
	if (graph[u].size() != 1 || u == 1) {
		int maxChild = -1;
		for(int v : graph[u]) {
			if (v != parents[u]) {
				dfs(v); 
				if (maxChild == -1 || weights[v].size() > weights[maxChild].size()) {
					maxChild = v;
				}
			}
		}
		weights[u] = weights[maxChild];
		for(int v : graph[u]) {
			if (v != parents[u] && v != maxChild) {
				for(int w : weights[v]) {
					weights[u].insert(w);
				}
				weights[v].clear();
			}
		}
	}
	for(int w : toAdd[u]) {
		weights[u].insert(w);
	}
	for(int w : toRem[u]) {
		weights[u].erase(weights[u].find(w));
	}
	if (u != 1) {
		ans[edges[pii(u, parents[u])]] = *weights[u].begin();
	}
}
int main () {
	//freopen("disrupt.in", "r", stdin);
    //freopen("disrupt.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < n - 1; i++) {
    	int x, y; cin >> x >> y;
    	graph[x].push_back(y);
    	graph[y].push_back(x);
    	edges[pii(x, y)] = i;
    	edges[pii(y, x)] = i;
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
    for(int i = 0; i < m; i++) {
    	int x, y, r; cin >> x >> y >> r;
    	toAdd[x].push_back(r);
    	toAdd[y].push_back(r);
    	toRem[LCA(x, y)].push_back(r);
    	toRem[LCA(x, y)].push_back(r);
    }
    dfs(1);
    for(int i = 0; i < n - 1; i++) {
    	if (ans[i] == 0) cout << -1 << endl;
    	else cout << ans[i] << endl;
    }
}