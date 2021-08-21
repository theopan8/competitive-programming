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
#include <cstring>
using namespace std;
const int maxn = 100010;
vector<int> graph[maxn];
int before[maxn];
int degree[maxn];
vector<int> after[maxn];
queue<int> good;
int visited[maxn];
void dfs (int u, int p) {
    visited[u] = 1;
    for(int v : graph[u]) {
        if (v != p && after[v].size() == 0) {
            dfs(v, u);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    //freopen("gathering.in", "r", stdin);
    //freopen("gathering.out", "w", stdout);
    int n, m; cin >> n >> m;
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for(int i = 1; i <= n; i++) {
        degree[i] = graph[i].size();
    }
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        before[y]++;
        after[x].push_back(y);
    }
    for(int i = 1; i <= n; i++) {
        if (graph[i].size() == 1) {
            if (before[i] == 0) {
                good.push(i);
            }
        }
    }
    int total = 0;
    while (!good.empty() && total < n - 1) {
        int u = good.front();
        total++;
        good.pop();
        degree[u]--;
        for(int v : after[u]) {
            before[v]--;
        }
        for(int v : graph[u]) {
            degree[v]--;
        }
        for(int v : after[u]) {
            if (before[v] == 0 && degree[v] == 1) {
                good.push(v);
            }
        }
        for(int v : graph[u]) {
            if (before[v] == 0 && degree[v] == 1) {
                good.push(v);
            }
        }
    }
    if (good.empty()) {
        for(int i = 0; i < n; i++) {
            cout << 0 << endl;
        }
    }
    else {
        dfs(good.front(), -1);
        for(int i = 1; i <= n; i++) {
            cout << visited[i] << endl;
        }
    }
}