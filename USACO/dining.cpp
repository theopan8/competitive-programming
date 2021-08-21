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
#include <iterator>
#include <limits>
using namespace std;
#define ll long long
const int maxn = 50010;
struct edge {
    int u; ll time;
};
struct State {
    int u; ll currDist;
    bool operator <(const State &other) const {
        return this->currDist > other.currDist;
    }
};
vector<edge> graph[maxn];
ll haybalesArray[maxn];
vector<int> haybalesIndex;
ll distN[maxn];
ll distBale[maxn];
int indexer[maxn];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    freopen("dining.in", "r", stdin);
    freopen("dining.out", "w", stdout);
    int n, m, k; cin >> n >> m >> k;
    for(int i = 0; i < m; i++) {
        int a, b, t; cin >> a >> b >> t;
        graph[a].push_back(edge{b, t});
        graph[b].push_back(edge{a, t});
    }
    for(int i = 0; i < k; i++) {
        int idx; ll yummy; cin >> idx >> yummy;
        haybalesArray[idx] = max(haybalesArray[idx], yummy);
    }
    for(int i = 1; i <= n; i++) {
        if (haybalesArray[i] != 0) {
            haybalesIndex.push_back(i);
        }
    }
    priority_queue<State> pq;
    for(int i = 1; i <= n; i++) {
        distN[i] = -1;
    }
    pq.push(State{n, 0});
    distN[n] = 0;
    while (!pq.empty()) {
        State s = pq.top();
        pq.pop();
        if (s.currDist == distN[s.u]) {
            for(edge e : graph[s.u]) {
                if (distN[e.u] > distN[s.u] + e.time || distN[e.u] == -1) {
                    distN[e.u] = distN[s.u] + e.time;
                    pq.push(State{e.u, distN[e.u]});
                }
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        distBale[i] = -0x7fffffff;
    }
    for(int bale : haybalesIndex) {
        pq.push(State{bale, -haybalesArray[bale] + distN[bale]});
        distBale[bale] = -haybalesArray[bale] + distN[bale];
    }
    while (!pq.empty()) {
        State s = pq.top();
        pq.pop();
        if (s.currDist == distBale[s.u]) {
            for (edge e : graph[s.u]) {
                if (distBale[e.u] > distBale[s.u] + e.time || distBale[e.u] == -0x7fffffff) {
                    distBale[e.u] = distBale[s.u] + e.time;
                    pq.push(State{e.u, distBale[e.u]});
                }
            }
        }
    }
    for(int i = 1; i < n; i++) {
        if (distN[i] >= distBale[i]) {
            cout << 1 << endl;
        }
        else {
            cout << 0 << endl;
        }
    }
}