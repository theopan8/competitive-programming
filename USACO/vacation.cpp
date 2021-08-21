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
#define maxn 50010
vector<int> graph[maxn];
int parents[maxn];
int visited[maxn];
void dfs (int curr, int p) {
    if (p != -1) parents[curr] = p;
    for(int v : graph[curr]) {
        if (v == p) continue;
        dfs(v, curr);
    }
}
int dp[maxn];
int go (int curr) {
    if (visited[curr] != 0) {
        return dp[curr];
    }
    visited[curr] = 1;
    int val1 = 0;
    int val2 = 1;
    for(int v : graph[curr]) {
        if (parents[curr] == v) continue;
        val1 += go(v);
    }
    for(int v : graph[curr]) {
        if (parents[curr] == v) continue; 
        for(int u : graph[v]) {
            if (parents[v] == u) continue;
            val2 += go(u);
        }
    }
    dp[curr] = max(val1, val2);
    return dp[curr];
}
int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(1, -1);
    cout << go(1) << endl;
    /*for(int i = 1; i <= n; i++) {
        cout << i << " " << dp[i] << endl;
    }
    for(int i = 1; i <= n; i++) {
        cout << parents[i] << endl;
    }*/
}