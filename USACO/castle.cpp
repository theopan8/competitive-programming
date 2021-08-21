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
using namespace std;
#define pii pair<int,int>
#define int long long
int p[100010];
int r[100010];
vector<pair<int,pii> > edges;
int findSet(int i) {
    if (p[i] == i) {
        return (i);
    }
    else {
        p[i] = findSet(p[i]);
        return (p[i]);
    }
}
void unionSet(int i, int j) {
    int x = findSet(i); int y = findSet(j);
    if (x != y) {
        if (r[x] == r[y]) {
            p[x] = y;
            r[y] += 1;
        }
        else if (r[x] > r[y]) {
            p[y] = x;
        }
        else {
            p[x] = y;
        }
    }
}
main() {
    //freopen("hayfeast.in", "r", stdin);
    //freopen("hayfeast.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u,v,w; cin >> u >> v >> w;
        edges.push_back(make_pair(w, pii(u,v)));
    }
    sort(edges.begin(), edges.end());
    for(int i = 1; i <= n; i++) {
        p[i] = i;
    }
    int total = 0;
    for(int i = 0; i < edges.size(); i++) {
        if (findSet(edges[i].second.first) == findSet(edges[i].second.second)) {
            continue;
        }
        total += edges[i].first;
        unionSet(edges[i].second.first, edges[i].second.second);
    }
    cout << total << endl;
}