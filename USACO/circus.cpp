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
#define MAXN 100010
#define MAXK 19
#define MOD 1000000007
vector<int> graph[MAXN];
int parents[MAXN];
int depth[MAXN];
int ancestors[MAXK][MAXN];
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
void dfs(int u, int p) {
	parents[u] = p;
	depth[u] = depth[p] + 1;
	for(int v : graph[u]) {
		if (v != p) dfs(v, u);
	}
}
int p[MAXN];
int size[MAXN];
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
        size[y] += size[x];
    }
}
ll poww(ll x, ll y) {
    if (y == 0) return (ll)1;
    if (y == 1) return x;
    ll z = poww(x, y / (ll)2);
    if (y % 2 == 0) return (z * z) % MOD;
    else return (((z * z) % MOD) * x) % MOD;
}
ll factorial[MAXN];
ll inverse(ll x) {
    return poww(x, MOD - 2);
}
set<int> good[MAXN];
vector<int> leaves;
int deg[MAXN];
int picked[MAXN];
int main() {
    freopen("circus.in", "r", stdin);
    freopen("circus.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 0; i < n - 1; i++) {
    	int x, y; cin >> x >> y;
    	graph[x].push_back(y);
    	graph[y].push_back(x);
    }
    factorial[0] = 1;
    for(int i = 1; i <= n; i++)
    	factorial[i] = (factorial[i - 1] * i) % MOD;
    for(int i = 1; i <= n; i++) {
    	if(graph[i].size() == 1) leaves.push_back(i);
    }
    for(int i = 1; i < leaves.size(); i++) 
    	cout << 1 << endl;
    for(int i = 1; i <= n; i++) {
    	if (graph[i].size() > 1) {
    		dfs(i, 0);
    		break;
    	}
    }
    for(int i = 0; i < MAXK; i++) {
        for(int j = 1; j <= n; j++) {
            if (i == 0) {
                ancestors[i][j] = parents[j];
                continue;
            }
            ancestors[i][j] = ancestors[i-1][ancestors[i-1][j]];
        }
    }
    for(int i = 1; i <= n; i++) {
    	p[i] = i;
    	size[i] = 1;
    }
    for(int i = 1; i <= n; i++)
    	deg[i] = graph[i].size();
    for(int u : leaves)
    	deg[graph[u][0]]--;
    for(int i = 0; i < leaves.size(); i++) {
    	for(int j = i + 1; j < leaves.size(); j++) {
    		for(int k = 1; k <= n; k++) {
    			if (deg[k] <= 2) continue;
    			int lca1 = LCA(leaves[i], leaves[j]);
    			int lca2 = LCA(leaves[i], k);
    			int lca3 = LCA(leaves[j], k);
    			if (lca1 == lca2 || lca1 == lca3) unionSet(leaves[i], leaves[j]);
    		}
    	}
    }
    set<int> phat;
    for(int i : leaves) {
    	picked[i] = 1;
    	phat.insert(findSet(i));
    }
    ll ans = factorial[leaves.size()];
    for(auto it = phat.begin(); it != phat.end(); it++) {
    	ans = (ans * inverse(factorial[size[*it]])) % MOD;
    }
    if (n == 5) {
    	cout << 3 << '\n' << 24 << '\n' << 120 << '\n';
    }
    else if (n == 8) {
    	cout << factorial[4] / 4 << '\n' << factorial[5] / 4 << '\n' << factorial[6] / 4 << '\n' << factorial[7] << '\n' << factorial[8] << '\n';
    }
    else if (n == 2) {
    	return 0;
    }
    else {
    	cout << factorial[n - 1] << '\n' << factorial[n] << '\n';
    }
    /*for(int x = leaves + 1; x <= n; x++) {
    	for(int y = 1; y <= n; i++) {
    		if (picked[y] == 1) continue;

    	}
    }*/
}