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
#define maxn 510
vector<int> graph[maxn];
int visited[maxn];
int bad_edges[maxn][maxn];
int vertex_sizes[maxn];
int flood = 0;
int floodfill (int point, int n) {
    queue<int> q;
    q.push(point);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (visited[x] != 0) {
            continue;
        }
        visited[x] = 1;
        flood += 1;
        for(int v: graph[x]) {
            if (visited[v] != 0) {
                continue;
            }
            if (bad_edges[v][x] <= 0) {
                continue;
            }
            q.push(v);
        }
    }
    for(int i = 1; i <= n; i++) {
        visited[i] = 0;
    }
    int dup = flood;
    flood = 0;
    return dup;
}
void fleury (int point, int n) {
    int original = floodfill(point, n);
    //cout << point << " original " << original << endl;
    cout << point << endl;
    for(int i = 0; i < graph[point].size(); i++) {
        int v = graph[point][i];
        if (bad_edges[point][v] == 0) {
            continue;
        }
        bad_edges[point][v] -= 1; bad_edges[v][point] -= 1;
        //cout << v << " floodfill " << floodfill(point,n) << endl;
        if (floodfill(point, n) == original || vertex_sizes[point] == 1) {
            vertex_sizes[v] -= 1;
            vertex_sizes[point] -= 1;
            fleury(v, n);
            break;
        }
        bad_edges[point][v] += 1; bad_edges[v][point] += 1;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    int f; cin >> f;
    int n = 0;
    for(int i = 0; i < f; i++) {
        int x, y; cin >> x >> y;
        if (n < x) {
            n = x;
        }
        if (n < y) {
            n = y;
        }
        bad_edges[x][y] += 1;
        bad_edges[y][x] += 1;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    int start = 0;
    for(int i = 1; i <= n; i++) {
        if (graph[i].size() % 2 == 1) {
            start = i;
            break;
        }
    }
    for(int i = 1; i <= n; i++) {
        vertex_sizes[i] = graph[i].size();
    }
    for(int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end());
    }
    if (start == 0) {
        fleury(1, n);
    }
    else {
        fleury(start, n);
    }
}