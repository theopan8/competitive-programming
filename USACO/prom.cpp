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
#include <cstring>
#include <stack>
using namespace std;
#define maxn 10010
vector<int> graph[maxn];
vector<int> graph1[maxn];
vector<int> graphcomp[maxn];
int visited[maxn];
int visited1[maxn];
int visitedcomp[maxn];
stack<int> q;
int components[maxn];
int components_size[maxn];
int total_size = 0;
void dfs (int start) {
    visited[start] = 1;
    for(int v: graph[start]) {
        if (visited[v] == 0) {
            dfs(v);
        }
    }
    q.push(start);
}
void dfs1 (int start) {
    visited1[start] = 1;
    total_size += 1;
    for(int v: graph1[start]) {
        if (visited1[v] == 0) {
            dfs1(v);
        }
    }
}
void dfscomp (int start, int type) {
    if (visitedcomp[start] != 0) {
        return;
    }
    visitedcomp[start] = 1;
    components[start] = type;
    components_size[type] += 1;
    for(int v: graphcomp[start]) {
        if (visitedcomp[v] == 0) {
            dfscomp(v, type);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graphcomp[a].push_back(b);
        graphcomp[b].push_back(a);
    }
    int types = 1;
    for(int i = 1; i <= n; i++) {
        if (visitedcomp[i] == 0) {
            dfscomp(i, types);
            types += 1;
        }
    }
    for(int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            dfs(i);
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int v: graph[i]) {
            graph1[v].push_back(i);
        }
    }
    int real_total = 0;
    while (!q.empty()) {
        int x = q.top();
        q.pop();
        //cout << x << endl;
        if (visited1[x] == 0) {
            dfs1(x);
            if (total_size == components_size[components[x]] && components_size[components[x]] != 1) {
                real_total += 1;
            }
        }
        total_size = 0;
    }
    cout << real_total << endl;
}