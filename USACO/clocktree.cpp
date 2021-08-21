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
#include <stack>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define MAXN 2510
int vals[MAXN];
int currs[MAXN];
vector<int> graph[MAXN];
int dfs(int u, int p) {
    vector<int> nodes;
    for(int v : graph[u]) {
        if (v != p) {
            currs[v] = (currs[v] + 1) % 12;
            nodes.push_back(dfs(v, u));
        }
    }
    if (nodes.size() == 0) return currs[u];
    int curr = (currs[u] + nodes.size()) % 12;
    for(int i : nodes) {
        if (i == 0) continue;
        curr = (curr + 12 - i) % 12;
    }
    return curr;
}
int main() {
    freopen("clocktree.in", "r", stdin);
    freopen("clocktree.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> vals[i];
        vals[i] = vals[i] % 12;
    }
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    int total = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            currs[j] = vals[j];
        }
        int val = dfs(i, 0);
        if (val == 0 || val == 1) {
            total++;
        }
    }
    cout << total << endl;
}