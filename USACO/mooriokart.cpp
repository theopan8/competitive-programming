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
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef pair<long long, long long> pii;
#define mod 1000000007
#define maxk 12
#define maxn 1501
struct edge {
    int v, d;
};
vector<edge> graph[maxn];
vector<int> forest[maxn];
unordered_map<int, pii> distances[maxn];
unordered_map<int, pii> finalDistances[maxn];
int visited[maxn];
int depth[maxn];
int dist[maxn];
int parents[maxn];
int numTrees = 0;
int ancestors[maxk][maxn];
int LCA (int a, int b) {
    if (depth[a] > depth[b]) {
        swap(a,b);
    }
    for(int j = maxk - 1; j >= 0; j--) {
        if ((1 << j) & (depth[b] - depth[a])) {
            b = ancestors[j][b];
        }
    }
    if (a == b) {
        return a;
    }
    for(int j = maxk - 1; j >= 0; j--) {
        if (ancestors[j][a] == ancestors[j][b]) {
            continue;
        }
        a = ancestors[j][a];
        b = ancestors[j][b];
    }
    return parents[a];
}
void dfs (int u, int p) {
    if (p == 0) depth[u] = 1;
    else depth[u] = depth[p] + 1;
    parents[u] = p;
    visited[u] = 1;
    forest[numTrees].push_back(u);
    for (edge e : graph[u]) {
        if (e.v != p) {
            dist[e.v] = dist[u] + e.d;
            dfs(e.v, u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    freopen("mooriokart.in", "r", stdin);
    freopen("mooriokart.out", "w", stdout);
    int n, m, x, y; cin >> n >> m >> x >> y;
    for(int i = 0; i < m; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        graph[a].push_back(edge{b, d});
        graph[b].push_back(edge{a, d});
    }
    for(int i = 1; i <= n; i++) {
        if (!visited[i]) {
            numTrees++;
            dfs(i, 0);
        }
    }
    y -= numTrees * x;
    for(int i = 0; i < maxk; i++) {
        for(int j = 1; j <= n; j++) {
            if (i == 0) {
                ancestors[i][j] = parents[j];
                continue;
            }
            ancestors[i][j] = ancestors[i-1][ancestors[i-1][j]];
        }
    }
    for(int i = 1; i <= numTrees; i++) {
        for(int j = 0; j < forest[i].size(); j++) {
            for(int k = j + 1; k < forest[i].size(); k++) {
                int anc = LCA(forest[i][j], forest[i][k]);
                int pathLen = dist[forest[i][j]] + dist[forest[i][k]] - 2 * dist[anc];
                //cout << forest[i][j] << " " << forest[i][k] << " " << pathLen << endl;
                if (pathLen < y) {
                    distances[i][pathLen].first = (distances[i][pathLen].first + pathLen) % mod;
                    distances[i][pathLen].second = (distances[i][pathLen].second + 1) % mod;
                }
                else {
                    distances[i][y].first = (distances[i][y].first + pathLen) % mod;
                    distances[i][y].second = (distances[i][y].second + 1) % mod;
                }
            }
        }
        /*for(auto j = distances[i].begin(); j != distances[i].end(); j++) {
            cout << j->first << " " << j->second.first << " " << j->second.second << endl;
        }
        cout << endl;*/
    }
    finalDistances[1] = distances[1];
    for(int i = 2; i <= numTrees; i++) {
        for(auto j = finalDistances[i - 1].begin(); j != finalDistances[i - 1].end(); j++) {
            for(auto k = distances[i].begin(); k != distances[i].end(); k++) {
                if (j->first + k->first >= y) {
                    finalDistances[i][y].first = (finalDistances[i][y].first + j->second.first * k->second.second + j->second.second * k->second.first) % mod;
                    finalDistances[i][y].second = (finalDistances[i][y].second + j->second.second * k->second.second) % mod;
                }
                else {
                    finalDistances[i][j->first + k->first].first = (finalDistances[i][j->first + k->first].first + j->second.first * k->second.second + j->second.second * k->second.first) % mod;
                    finalDistances[i][j->first + k->first].second = (finalDistances[i][j->first + k->first].second + j->second.second * k->second.second) % mod;
                }
            }
        }
    }
    /*for(auto i = finalDistances[numTrees].begin(); i != finalDistances[numTrees].end(); i++) {
        cout << i->first << " " << i->second.first << " " << i->second.second << endl;
    }*/
    ll ans = finalDistances[numTrees][y].first + numTrees * x * finalDistances[numTrees][y].second;
    for(int i = 1; i < numTrees; i++) {
        ans = (ans * 2 * i) % mod;
    }
    cout << ans << endl;
}