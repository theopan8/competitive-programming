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
#define maxn 1005
vector<int> graph[maxn];
int visited[maxn][maxn];
void dfs (int start, int index) {
    if (visited[index][start] != 0) {
        return;
    }
    visited[index][start] = 1;
    for(int i = 0; i < graph[start].size(); i++) {
        if (visited[index][graph[start][i]] == 0) {
            dfs(graph[start][i], index);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        graph[y].push_back(x);
    }
    for(int i = 1; i <= n; i++) {
        dfs(i, i);
    }
    int total = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i+1; j <= n; j++) {
            if (visited[i][j] == 0 && visited[j][i] == 0) {
                total += 1;
            }
        }
    }
    cout << total << endl;
}