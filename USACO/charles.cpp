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
#define maxn 2010
#define pii pair<int,int>
vector<pii> graph[maxn];
vector<pii> graph1[maxn];
vector<pair<int,pii > > edges;
int mark[2][maxn];
int dist[2][maxn];
void dijsktra (int start, int type) {
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
            if (mark[type][graph[vertex][i].first] == 0 && (dist[type][graph[vertex][i].first] > graph[vertex][i].second + dist[type][vertex] || dist[type][graph[vertex][i].first] == -1)) {
                dist[type][graph[vertex][i].first] = graph[vertex][i].second + dist[type][vertex];
                q.push(pii(-dist[type][graph[vertex][i].first], graph[vertex][i].first));
            }
        }
    }
}
void dijsktra1 (int start, int type) {
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
        for(int i = 0; i < graph1[vertex].size(); i++) {
            if (mark[type][graph1[vertex][i].first] == 0 && (dist[type][graph1[vertex][i].first] > graph1[vertex][i].second + dist[type][vertex] || dist[type][graph1[vertex][i].first] == -1)) {
                dist[type][graph1[vertex][i].first] = graph1[vertex][i].second + dist[type][vertex];
                q.push(pii(-dist[type][graph1[vertex][i].first], graph1[vertex][i].first));
            }
        }
    }
}

int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v, t; cin >> u >> v >> t;
        graph[u].push_back(pii(v, t));
        graph[v].push_back(pii(u, t));
        edges.push_back(make_pair(t, pii(u, v)));
    }
    for(int i = 0; i < m; i++) {
        int c; cin >> c;
        graph1[edges[i].second.first].push_back(pii(edges[i].second.second, edges[i].first + c));
        graph1[edges[i].second.second].push_back(pii(edges[i].second.first, edges[i].first + c));
    }
    for(int i = 1; i <= n; i++) {
        dist[0][i] = -1; dist[1][i] = -1;
    }
    dijsktra(1, 0); dijsktra1(1,1);
    cout << dist[1][n] - dist[0][n] << endl;
}