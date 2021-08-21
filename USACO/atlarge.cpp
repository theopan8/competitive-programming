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
#include <limits>
using namespace std;
#define maxn 70010
#define pii pair<int,int>
vector<int> graph[maxn];
int sqrtn = 0;
int tree[266][2*maxn];
int distToLeaf[maxn];
int depth[maxn];
int bfs_visited[maxn];
int lazyCounter[266];
int visited_ans[maxn];
int preorder[maxn];
int curr_preorder = 0;
int anser[maxn];
int subsize[maxn];
int delta[maxn];
int anser_visited[maxn];
void dfs_precomp(int u, int p) {
	curr_preorder++;
	preorder[u] = curr_preorder;
	if (p != 0) {
		depth[u] = depth[p] + 1;
	}
	int curr_size = 1;
	for(int v : graph[u]) {
		if (v != p) {
			dfs_precomp(v, u);
			curr_size += subsize[v];
		}
	}
	subsize[u] = curr_size;
}
void bfs_precomp(int n) {
	queue<pii> q;
	for(int i = 1; i <= n; i++) {
		if (graph[i].size() == 1) {
			q.push(pii(i, 0));
		}
	}
	while (!q.empty()) {
		int v = q.front().first;
		int dist = q.front().second;
		q.pop();
		if (bfs_visited[v]) {
			continue;
		}
		bfs_visited[v] = 1;
		distToLeaf[v] = dist;
		for(int u : graph[v]) {
			if (!bfs_visited[u]) {
				q.push(pii(u, dist+1));
			}
		}
	}
}
int query(int idx, int sqrtPart){
    int sum = 0;
    while (idx > 0){
        sum += tree[sqrtPart][idx];
        idx -= (idx & -idx);
    }
    return sum;
}
void update(int idx, int val, int sqrtPart){
    while (idx < 2*maxn){
        tree[sqrtPart][idx] += val;
        idx += (idx & -idx);
    }
}
void dfs_ans(int v, int n) {
	if (v == 1) {
		for(int i = 1; i <= n; i++) {
			delta[preorder[i]] = n + depth[i] - distToLeaf[i];
			update(n + depth[i] - distToLeaf[i], 2 - graph[i].size(), preorder[i]/sqrtn);
		}
	}
	else {
		int low = preorder[v]/sqrtn + 1;
		int high = (preorder[v] + subsize[v] - 1)/sqrtn - 1;
		for(int i = 0; i <= sqrtn; i++) {
			lazyCounter[i]++;
		}
		for(int i = low; i <= high; i++) {
			lazyCounter[i] -= 2;
		}
		lazyCounter[low -1]++;
		lazyCounter[high+1]++;
		int curr = preorder[v]+1;
		update(delta[preorder[v]], -2 + graph[preorder[v]].size(), preorder[v]/sqrtn);
		update(delta[preorder[v]] - 1, 2 - graph[preorder[v]].size(), preorder[v]/sqrtn);
		delta[preorder[v]]--;
		while (curr % sqrtn != 0 && curr <= n) {
			update(delta[curr], -2 + graph[curr].size(), curr/sqrtn);
			update(delta[curr] - 1, 2 - graph[curr].size(), curr/sqrtn);
			delta[curr]--;
			curr++;
		}
		curr = preorder[v] + subsize[v] - 1;
		//cout << curr << endl;
		while (curr % sqrtn != 0) {
			update(delta[curr], -2 + graph[curr].size(), curr/sqrtn);
			update(delta[curr] - 1, 2 - graph[curr].size(), curr/sqrtn);
			delta[curr]--;
			curr--;
		}
		//cout << curr << endl;
		if (curr != 0) {
			update(delta[curr], -2 + graph[curr].size(), curr/sqrtn);
			update(delta[curr] - 1, 2 - graph[curr].size(), curr/sqrtn);
		}
	}
	for(int i = 0; i <= sqrtn; i++) {
		anser[v] += query(2*n, i) - query(n-1 - lazyCounter[i], i);
	}
	anser_visited[v] = 1;
	for(int u : graph[v]) {
		if (!anser_visited[u]) {
			dfs_ans(u, n);
		}
	}
	int low = preorder[v]/sqrtn + 1;
	int high = (preorder[v] + subsize[v] - 1)/sqrtn - 1;
	for(int i = 0; i <= sqrtn; i++) {
		lazyCounter[i]--;
	}
	for(int i = low; i <= high; i++) {
		lazyCounter[i] += 2;
	}
	lazyCounter[low -1]--;
	lazyCounter[high+1]--;
	int curr = preorder[v]+1;
	update(delta[preorder[v]], 2 - graph[preorder[v]].size(), preorder[v]/sqrtn);
	update(delta[preorder[v]] - 1, -2 + graph[preorder[v]].size(), preorder[v]/sqrtn);
	delta[preorder[v]]++;
	while (curr % sqrtn != 0 && curr <= n) {
		update(delta[curr], 2 - graph[curr].size(), curr/sqrtn);
		update(delta[curr] - 1, -2 + graph[curr].size(), curr/sqrtn);
		delta[curr]++;
		curr++;
	}
	curr = preorder[v] + subsize[v] - 1;
	//cout << curr << endl;
	while (curr % sqrtn != 0) {
		update(delta[curr], 2 - graph[curr].size(), curr/sqrtn);
		update(delta[curr] - 1, -2 + graph[curr].size(), curr/sqrtn);
		delta[curr]++;
		curr--;
	}
	//cout << curr << endl;
	if (curr != 0) {
		update(delta[curr], 2 - graph[curr].size(), curr/sqrtn);
		update(delta[curr] - 1, -2 + graph[curr].size(), curr/sqrtn);
	}
}
int main() {
    //freopen("atlarge.in", "r", stdin);
    //freopen("atlarge.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    sqrtn = (int)round(sqrt(n));
    for(int i = 0; i < n-1; i++) {
    	int u, v; cin >> u >> v;
    	graph[u].push_back(v);
    	graph[v].push_back(u);
    }
    dfs_precomp(1, 0);
    bfs_precomp(n);
    dfs_ans(1, n);
    for(int i = 1; i <= n; i++) {
    	cout << anser[i] << endl;
    }
}