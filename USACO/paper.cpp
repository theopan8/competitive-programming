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
#define maxn 1010
#define pii pair<int,int>
int costs[maxn];
vector<int> graph[maxn];
int dist[110][maxn];
int mark[110][maxn];
void dijsktra (int start, int dist_c, int type) {
    priority_queue<pii> q;
    dist[type][start] = 0;
    q.push(pii(-dist[type][start], start));
    while (!q.empty()) {
        pii vertex_pair = q.top();
        q.pop();
        int vertex = vertex_pair.second;
        int distance = -vertex_pair.first;
        if (mark[type][vertex] == 1) {
            continue;
        }
        mark[type][vertex] = 1;
        for(int i = 0; i < graph[vertex].size(); i++) {
            if (mark[type][graph[vertex][i]] == 0 && (dist[type][graph[vertex][i]] > dist_c + dist[type][vertex] || dist[type][graph[vertex][i]] == -1)) {
                dist[type][graph[vertex][i]] = dist_c + dist[type][vertex];
                q.push(pii(-dist[type][graph[vertex][i]], graph[vertex][i]));
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    for(int i = 1; i <= k; i++) {
        int c; cin >> c;
        costs[i] = c;
    }
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= n; j++) {
            dist[i][j] = -1;
        }
    }
    for(int i = 1; i <= k; i++) {
        dijsktra(i, costs[i], i);
    }
    int total = 0;
    for(int i = k+1; i <= n; i++) {
        int min = -1;
        for(int j = 1; j <= k; j++) {
            if (dist[j][i] == 0) {
                continue;
            }
            if (min == -1 || dist[j][i] < min) {
                min = dist[j][i];
            }
        }
        total += min;
    }
    cout << total << endl;
}
