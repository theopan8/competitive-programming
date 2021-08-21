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
#define maxk 15
int parents[maxn];
vector<int> graph[maxn];
int depths[maxn];
int ancestors[maxn][maxk];
void dfs (int start, int depth) {
    depths[start] = depth;
    for(int i = 0; i < graph[start].size(); i++) {
        dfs(graph[start][i], depth+1);
    }
}
int LCA (int a, int b) {
    if (depths[a] > depths[b]) {
        swap(a,b);
    }
    for(int j = maxk -1; j >= 0; j--) {
        if ((1 << j) & (depths[b] - depths[a])) {
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
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 2; i <= n; i++) {
        int p; cin >> p;
        parents[i] = p;
        graph[p].push_back(i);
    }
    for(int i = 0; i < maxk; i++) {
        for(int j = 1; j <= n; j++) {
            if (i == 0) {
                ancestors[j][i] = parents[j];
                continue;
            }
            ancestors[j][i] = ancestors[ancestors[j][i-1]][i-1];
        }
    }
    dfs(1, 0);
    for(int i = 0; i < m; i++) {
        int a,b; cin >> a >> b;
        int ancestor = LCA(a,b);
        cout << ancestor << endl;
    }
}
