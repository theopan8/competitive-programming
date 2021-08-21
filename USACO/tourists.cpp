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
#define maxn 200010
#define maxk 21
#define int long long
vector<int> graph[maxn];
int parents[maxn];
int ancestors[maxn][maxk];
int visited[maxn];
int depth[maxn];
/*void dfs (int start, int curr) {
    visited[start] = 1;
    depth[start] = curr;
    for(int i = 0; i < graph[start].size(); i++) {
        if (visited[graph[start][i]] == 0) {
            parents[graph[start][i]] = start;
            dfs(graph[start][i], curr+1);
        }
    }
}*/
void bfs (int start) {
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (visited[x] == 1) {
            continue;
        }
        visited[x] = 1;
        for(int i = 0; i < graph[x].size(); i++) {
            if (visited[graph[x][i]] == 0) {
                q.push(graph[x][i]);
                depth[graph[x][i]] = depth[x]+1;
                parents[graph[x][i]] = x;
            }
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
main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    bfs(1);
    for(int i = 0; i < maxk; i++) {
        for(int j = 1; j <= n; j++) {
            if (i == 0) {
                ancestors[j][i] = parents[j];
                continue;
            }
            ancestors[j][i] = ancestors[ancestors[j][i-1]][i-1];
        }
    }
    int total = 0;
    for(int i = 1; i <= n; i++) {
        int curr = 2*i;
        while (curr <= n) {
            int anc = LCA(i, curr);
            total += depth[i]+depth[curr] - 2*depth[anc] + 1;
            curr += i;
            //cout << anc << " " << depth[i]+depth[curr] - 2*depth[anc] << endl;
        }
    }
    cout << total << endl;
}