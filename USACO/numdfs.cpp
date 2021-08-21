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
#define maxn 20
vector<int> graph[maxn];
int order[maxn];
int curr_order = 1;
bool bad = false;
int visited[maxn];
void dfs (int start, bool first) {
    if (first) {
        if (order[start-1] != 1) {
            bad = true;
            return;
        }
    }
    cout << start << endl;
    visited[start] = 1;
    int vertex = -1;
    int num_count = 0;
    for(int i = 0; i < graph[start].size(); i++) {
        if (order[graph[start][i]-1] == curr_order+1) {
            vertex = graph[start][i];
        }
        if (visited[graph[start][i]] == 0) {
            num_count += 1;
        }
    }
    if (vertex == -1) {
        if (num_count > 0) {
            bad = true;
            return;
        }
        return;
    }
    curr_order += 1;
    dfs(vertex, false);
    for(int i = 0; i < graph[start].size(); i++) {
        if (visited[graph[start][i]] == 0 && graph[start][i] != vertex) {
            dfs(graph[start][i], false);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, m, v; cin >> n >> m >> v;
    for(int i = 0; i < m; i++) {
        int u, x; cin >> u >> x;
        graph[u].push_back(x);
        graph[x].push_back(u);
    }
    for(int i = 1; i <= n; i++) {
        order[i-1] = i;
    }
    int total = 0;
    do {
        dfs(v, true);
        if (bad) {
            continue;
        }
        else {
            total += 1;
        }
    } while (next_permutation(order,order+n));
    cout << total << endl;
}