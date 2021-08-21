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
#define maxn 100010
#define pii pair<int,int>
vector<int> graph[maxn];
vector<int> graph_rev[maxn];
int visited[maxn];
int visited1[maxn];
stack<int> q;
int scc[maxn];
int scc_weights[maxn];
map<pii, int> visited_edges;
vector<int> scc_graph[maxn];
vector<int> rev_scc_graph[maxn];
int dp[2][maxn];
void dfs (int start) {
    visited[start] = 1;
    for(int v: graph[start]) {
        if (visited[v] == 0) {
            dfs(v);
        }
    }
    q.push(start);
}
void dfs1 (int start, int type) {
    visited1[start] = 1;
    scc[start] = type;
    scc_weights[type] += 1;
    for(int v: graph_rev[start]) {
        if (visited1[v] == 0) {
            dfs1(v, type);
        }
    }
}
//calculates distance from start to end
int dp_func (int type, int start, int end) {
    if (start == end) {
        return 0;
    }
    int& ans = dp[type][start];
    if (ans != -1) {
        return ans;
    }
    ans = -2;
    for(int v: scc_graph[start]) {
        int curr = dp_func(type, v, end);
        if (curr >= 0) {
            ans = max(ans, scc_weights[start] + curr);
        }
    }
    return ans;
}
int reverse_dp_func (int type, int start, int end) {
    if (start == end) {
        return 0;
    }
    int& ans = dp[type][start];
    if (ans != -1) {
        return ans;
    }
    ans = -2;
    for(int v: rev_scc_graph[start]) {
        int curr = reverse_dp_func(type, v, end);
        //cout << start << " " << v << " " << end << " " << curr << endl;
        if (curr >= 0) {
            ans = max(ans, scc_weights[start] + curr);
        }
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(0);
    //freopen("grass.in", "r", stdin);
    //freopen("grass.out", "w", stdout);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
    }
    //now do kosaraju
    //get stack
    for(int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            dfs(i);
        }
    }
    //reverse edges
    for(int i = 1; i <= n; i++) {
        for(int v: graph[i]) {
            graph_rev[v].push_back(i);
        }
    }
    int type = 1;
    while (!q.empty()) {
        int x = q.top();
        q.pop();
        if (visited1[x] == 0) {
            dfs1(x, type);
            type += 1;
        }
    }
    /*for(int i = 1; i <= n; i++) {
        cout << scc[i] << " ";
    }
    cout << endl;
    for(int i = 1; i < type; i++) {
        cout << scc_weights[i] << " ";
    }
    cout << endl;*/
    //now we have the sccs
    //below creates the scc graph (scc are vertices of the graph)
    //also creates the scc graph with reversed edges
    for(int i = 1; i <= n; i++) {
        for(int v: graph[i]) {
            if (visited_edges[pii(scc[i],scc[v])] == 0 && scc[i] != scc[v]) {
                //cout << scc[i] << " " << scc[v] << endl;
                visited_edges[pii(scc[i],scc[v])] = 1;
                scc_graph[scc[i]].push_back(scc[v]);
                //rev_scc_graph[scc[v]].push_back(scc[i]);
            }
        }
    }
    for(int i = 1; i < type; i++) {
        for(int v: scc_graph[i]) {
            rev_scc_graph[v].push_back(i);
        }
    }
    //now do the dp
    //type-1 is the number of nodes in the scc graph
    memset(dp, -1, sizeof(dp));
    int total = scc_weights[scc[1]];
    for(int i = 1; i < type; i++) {
        int length1 = dp_func(0, i, scc[1]);
        //cout << i << " " << length1 << endl;
        if (length1 < 0) {
            continue;
        }
        for(int v: scc_graph[i]) {
            int length2 = reverse_dp_func(1, v, scc[1]);
            //cout << "real " << i << " " << v << " " << length2 << endl;
            if (length2 >= 0) {
                total = max(total, scc_weights[scc[1]] + length1 + length2);
            }
        }
    }
    cout << total << endl;
}