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
#define maxn 100005
#define maxk 19
vector<int> graph[maxn];
int parents[maxn];
int depth[maxn];
int visited[maxn];
int ancestors[maxn][maxk];
void dfs (int curr_depth, int parent) {
    if (visited[parent] != 0) {
        return;
    }
    visited[parent] = 1;
    for(int i = 0; i < graph[parent].size(); i++) {
        if (visited[graph[parent][i]] == 0) {
            parents[graph[parent][i]] = parent;
            depth[graph[parent][i]] = curr_depth + 1;
            dfs(curr_depth + 1, graph[parent][i]);
        }
    }
}
int LCA (int a, int b) {
    if (depth[a] > depth[b]) {
        swap(a,b);
    }
    for(int j = maxk -1; j >= 0; j--) {
        if ((1 << j) & (depth[b] - depth[a])) {
            b = ancestors[b][j];
        }
    }
    if (a == b) {
        return a;
    }
    for(int j = maxk-1; j >= 0; j--) {
        if (ancestors[a][j] == ancestors[b][j]) {
            continue;
        }
        a = ancestors[a][j];
        b = ancestors[b][j];
    }
    return parents[a];
}

int main() {
    //freopen("hayfeast.in", "r", stdin);
    //freopen("hayfeast.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(0, 1);
    for(int i = 0; i < maxk; i++) {
        for(int j = 1; j <= n; j++) {
            if (i == 0) {
                ancestors[j][i] = parents[j];
                continue;
            }
            ancestors[j][i] = ancestors[ancestors[j][i-1]][i-1];
        }
    }
    for(int i = 0; i < q; i++) {
        int a,b; cin >> a >> b;
        int ancestor = LCA(a,b);
        cout << (depth[a]-depth[ancestor]) + (depth[b] - depth[ancestor]) << endl;
    }
}
