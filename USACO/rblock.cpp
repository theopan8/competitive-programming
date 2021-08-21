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
#define maxn 260
#define pii pair<int,int>
vector<pii> graph[maxn];
int dist[maxn];
int mark[maxn];
vector<int> path[maxn];
void dijsktra (int start) {
    priority_queue<pii> q;
    dist[start] = 0;
    q.push(pii(-dist[start], start));
    while (!q.empty()) {
        pii vertex_pair = q.top();
        q.pop();
        int vertex = vertex_pair.second;
        int distance = -vertex_pair.first;
        if (mark[vertex] == 1) {
            continue;
        }
        mark[vertex] = 1;
        for(int i = 0; i < graph[vertex].size(); i++) {
            if (mark[graph[vertex][i].first] == 0 && (dist[graph[vertex][i].first] > graph[vertex][i].second + dist[vertex] || dist[graph[vertex][i].first] == -1)) {
                dist[graph[vertex][i].first] = graph[vertex][i].second + dist[vertex];
                vector<int> dup = path[vertex];
                dup.push_back(vertex);
                path[graph[vertex][i].first] = dup;
                q.push(pii(-dist[graph[vertex][i].first], graph[vertex][i].first));
            }
        }
    }
}
void dijsktra2 (int start) {
    priority_queue<pii> q;
    dist[start] = 0;
    q.push(pii(-dist[start], start));
    while (!q.empty()) {
        pii vertex_pair = q.top();
        q.pop();
        int vertex = vertex_pair.second;
        int distance = -vertex_pair.first;
        if (mark[vertex] == 1) {
            continue;
        }
        mark[vertex] = 1;
        for(int i = 0; i < graph[vertex].size(); i++) {
            if (mark[graph[vertex][i].first] == 0 && (dist[graph[vertex][i].first] > graph[vertex][i].second + dist[vertex] || dist[graph[vertex][i].first] == -1)) {
                dist[graph[vertex][i].first] = graph[vertex][i].second + dist[vertex];
                q.push(pii(-dist[graph[vertex][i].first], graph[vertex][i].first));
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
        int a, b, l; cin >> a >> b >> l;
        graph[a].push_back(pii(b,l));
        graph[b].push_back(pii(a,l));
    }
    for(int i = 1; i <= n; i++) {
        dist[i] = -1;
    }
    dijsktra(1);
    path[n].push_back(n);
    vector<int> real_path = path[n];
    int original_dist = dist[n];
    int new_dist = 0;
    for(int i = 0; i < real_path.size()-1; i++) {
        int x = real_path[i];
        int y = real_path[i+1];
        if (i > 0) {
            int z = real_path[i-1];
            for(int j = 0; j < graph[x].size(); j++) {
                if (graph[x][j].first == z) {
                    graph[x][j] = pii(graph[x][j].first, (graph[x][j].second)/2);
                    break;
                }
            }
            for(int j = 0; j < graph[z].size(); j++) {
                if (graph[z][j].first == x) {
                    graph[z][j] = pii(graph[z][j].first, (graph[z][j].second)/2);
                }
            }
        }
        for(int j = 0; j < graph[x].size(); j++) {
            if (graph[x][j].first == y) {
                graph[x][j] = pii(graph[x][j].first, 2*graph[x][j].second);
                break;
            }
        }
        for(int j = 0; j < graph[y].size(); j++) {
            if (graph[y][j].first == x) {
                graph[y][j] = pii(graph[y][j].first, 2*graph[y][j].second);
                break;
            }
        }
        for(int j = 1; j <= n; j++) {
            dist[j] = -1;
            mark[j] = 0;
        }
        dijsktra2(1);
        if (new_dist < dist[n]) {
            new_dist = dist[n];
        }
    }
    cout << new_dist - original_dist << endl;
}
