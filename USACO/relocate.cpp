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
#define maxn 10010
#define pii pair<int,int>
vector<int> markets;
int market_map[maxn];
int map_market[7];
vector<pii> graph[maxn];
int dist[7][maxn];
int mark[7][maxn];
void dijsktra (int start, int type) {
    priority_queue<pii> q;
    dist[type][start] = 0;
    q.push(pii(-dist[type][start], start));
    while (!q.empty()) {
        pii vertex_pair = q.top();
        q.pop();
        int vertex = vertex_pair.second;
        int distance = -vertex_pair.first;
        //cout << vertex << endl;
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
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    for(int i = 0; i < k; i++) {
        int x; cin >> x;
        markets.push_back(x);
        market_map[x] = i+1;
    }
    for(int i = 0; i < m; i++) {
        int x, y, l; cin >> x >> y >> l;
        graph[x].push_back(pii(y,l));
        graph[y].push_back(pii(x,l));
    }
    for(int i = 0; i < k; i++) {
        for(int j = 1; j <= n; j++) {
            dist[i][j] = -1;
        }
    }
    for(int i = 0; i < k; i++) {
        dijsktra(markets[i], i);
    }
    /*for(int i = 1; i <= n; i++) {
        cout << i << " " << dist[1][i] << endl;
    }*/
    int real_min = -1;
    do {
        int distance = 0;
        for(int i = 0; i < k-1; i++) {
            distance += dist[market_map[markets[i]]-1][markets[i+1]];
        }
        int min = -1;
        for(int i = 1; i <= n; i++) {
            if (market_map[i] > 0) {
                continue;
            }
            int new_distance = dist[market_map[markets[0]]-1][i] + dist[market_map[markets[k-1]]-1][i];
            if (min == -1) {
                min = new_distance;
            }
            else if (min > new_distance) {
                min = new_distance;
            }
        }
        distance += min;
        if (real_min == -1) {
            real_min = distance;
        }
        else if (real_min > distance) {
            real_min = distance;
        }
    } while (next_permutation(markets.begin(), markets.end()));
    cout << real_min << endl;
}
