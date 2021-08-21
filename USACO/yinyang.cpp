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
#define ll long long
const int maxn = 100010;
struct edge {
	int v, d;
};
vector<edge> graph[maxn];
map<int, int> weightWithStop;
map<int, int> weightNoStop;
map<int, int> visitedWeight;
map<int, int> currWithStop;
map<int, int> currNoStop;
int vertexW[maxn];
int visitedC[maxn];
int subtrees[maxn];
int n;
int root;
void subtreeComp(int u, int p) {
	int tot = 1;
	for(edge e : graph[u]) {
		if (e.v != p && visitedC[e.v] == 0) {
			subtreeComp(e.v, u);
			tot += subtrees[e.v];
		}
	}
	subtrees[u] = tot;
}
int centroidComp(int u, int p, int tree_size) {
	for(edge e : graph[u]) {
		if (subtrees[e.v] > tree_size/2 && e.v != p && visitedC[e.v] == 0) {
			return centroidComp(e.v, u, tree_size);
		}
	}
	return u;
}
ll total = 0;
void dfs(int u, int p) {
	for(edge e : graph[u]) {
		if (e.v != p && visitedC[e.v] == 0) {
			vertexW[e.v] = vertexW[u] + e.d;
			if (visitedWeight[vertexW[e.v]] > 0) {
				weightWithStop[vertexW[e.v]]++;
				currWithStop[vertexW[e.v]]++;
			}
			else {
				weightNoStop[vertexW[e.v]]++;
				currNoStop[vertexW[e.v]]++;
			}
			visitedWeight[vertexW[e.v]]++;
			dfs(e.v, u);
			visitedWeight[vertexW[e.v]]--;
			vertexW[e.v] = 0;
			if (u == root) {
				for(auto it = currWithStop.begin(); it != currWithStop.end(); it++) {
					if (it->first == 0) {
						total += it->second;
					}
					total += (ll)it->second * (ll)(weightWithStop[-(it->first)] + weightNoStop[-(it->first)] - currWithStop[-(it->first)] - currNoStop[-(it->first)]);
				}
				for(auto it = currNoStop.begin(); it != currNoStop.end(); it++) {
					if (it->first == 0) {
						total += (ll)it->second * (ll)(weightNoStop[-(it->first)] - currNoStop[-(it->first)]);
					}
					total += (ll)it->second * (ll)(weightWithStop[-(it->first)] - currWithStop[-(it->first)]);
				}
				currWithStop.clear();
				currNoStop.clear();
			}
		}
	}
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    //freopen("yinyang.in", "r", stdin);
    //freopen("yinyang.out", "w", stdout);
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
    	int x, y, w; cin >> x >> y >> w;
    	if (w == 0) w = -1;
    	graph[x].push_back(edge{y, w});
    	graph[y].push_back(edge{x, w});
    }
    queue<int> q;
    subtreeComp(1, -1);
    q.push(centroidComp(1, -1, n));
    while(!q.empty()) {
    	int centroid = q.front();
    	q.pop();
    	if (visitedC[centroid] != 0) {
    		continue;
    	}
    	subtreeComp(centroid, -1);
    	root = centroid;
    	dfs(root, -1);
    	weightWithStop.clear();
    	weightNoStop.clear();
    	visitedC[centroid] = 1;
    	for(edge e : graph[centroid]) {
    		if (visitedC[e.v] == 0) {
    			q.push(centroidComp(e.v, -1, subtrees[e.v]));
    		}
    	}
    }
    cout << total << endl;
}