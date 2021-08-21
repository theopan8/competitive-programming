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
#include <string>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <stack>
#include <cstring>
#include <deque>
using namespace std;
#define MAXN 10010
struct edge {
    int v, w;
};
struct state {
    int u, p, d;
    bool operator <(const state &other) const {
        return this->d < other.d;
    }
};
vector<edge> graph[MAXN];
int parent[MAXN];
int dist[MAXN];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, m, k; cin >> n >> m >> k;
    for(int i = 0; i < m; i++) {
        int x, y, w; cin >> x >> y >> w;
        graph[x].push_back(edge{y, w});
        graph[y].push_back(edge{x, w});
    }
    for(int i = 1; i <= n; i++)
        dist[i] = 1e9;
    priority_queue<state> pq;
    pq.push(state{n, n, 0});
    while(!pq.empty()) {
        int u = pq.top().u;
        int p = pq.top().p;
        int d = pq.top().d;
        pq.pop();
        if(dist[u] <= d) continue;
        dist[u] = d;
        parent[u] = p;
        for(edge e : graph[u])
            if(dist[e.v] > dist[u] + e.w) pq.push(state{e.v, u, dist[u] + e.w});
    }

}