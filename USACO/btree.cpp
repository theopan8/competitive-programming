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
typedef long long ll;
typedef pair<int, int> pii;
#define MAXN 40010
vector<int> graph[MAXN];
int visit[MAXN];
int subtree[MAXN];
int n;
int sign[MAXN];
void predfs(int u, int p) {
    int tot = 1;
    for(int v : graph[u]) {
        if(v != p && !visit[v]) {
            predfs(v, u);
            tot += subtree[v];
        }
    }
    subtree[u] = tot;
}
int findCentroid(int u, int p, int size) {
    for(int v : graph[u])
        if(v != p && subtree[v] > size / 2 && !visit[v]) return findCentroid(v, u, size);
    visit[u] = 1;
    return u;
}
vector<pii> pairs;
map<int, int> mapper;
void dfs(int u, int p, int curr, int curr1, int curr2, int check1, int check2) {
    curr += sign[u];
    curr1 = max(0, curr1 + sign[u]); //(
    curr2 = max(0, curr2 - sign[u]); //)
    check1 = min(0, check1 + sign[u]); //(
    check2 = max(0, check2 + sign[u]); //)
    if(sign[u] == 1 && check1 == 0) pairs.push_back(pii(curr, curr1));
    else if(sign[u] == -1 && check2 == 0) pairs.push_back(pii(curr, curr2));
    for(int v : graph[u]) {
        if(v != p && !visit[v]) dfs(v, u, curr, curr1, curr2, check1, check2);
    }
}
int ans = 0;
void centroidDecomp(int u) {
    predfs(u, 0);
    int centroid = findCentroid(u, 0, subtree[u]);
    for(int v : graph[centroid]) {
        if(!visit[v]) {
            dfs(v, centroid, 0, 0, 0, 0, 0);
            for(pii p : pairs) {
                if(mapper[-p.first] == 0) continue;
                ans = max(ans, max(mapper[-p.first], p.second));
            }
            pairs.clear();
            dfs(v, centroid, sign[u], max(0, sign[centroid]), max(0, -sign[centroid]), min(0, sign[centroid]), max(0, sign[centroid]));
            for(pii p : pairs)
                mapper[p.first] = max(mapper[p.first], p.second);
        }
    }
    ans = max(ans, mapper[0]);
    mapper.clear();
    for(int v : graph[centroid])
        if(!visit[v]) centroidDecomp(v);
}
int main() {
    //freopen("btree.in", "r", stdin);
    //freopen("btree.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n;
    for(int i = 2; i <= n; i++) {
        int p; cin >> p;
        graph[i].push_back(p);
        graph[p].push_back(i);
    }
    for(int i = 1; i <= n; i++) {
        char c; cin >> c;
        if(c == '(') sign[i] = 1;
        else sign[i] = -1;
    }
    centroidDecomp(1);
    cout << ans << '\n';
}