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
#define maxn2 260000
#define ll long long
int elev[maxn][maxn];
int p[maxn2];
int r[maxn2];
int size[maxn2];
int num_start[maxn2];
int starting[maxn2];
vector<pair<int,pair<int,int> > > edges;
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
    if (r[x] > r[y]) {
        p[y] = x;
        size[x] += size[y];
        num_start[x] += num_start[y];
    }
    else if (r[y] > r[x]) {
        p[x] = y;
        size[y] += size[x];
        num_start[y] += num_start[x];
    }
    else {
        if (x != y) {
            p[x] = y;
            r[y] += 1;
            size[y] += size[x];
            num_start[y] += num_start[x];
        }
    }
}
int mapoint (int x, int y, int z) {
    return x * z + y;
}
int main() {
    ios_base::sync_with_stdio(0);
    int m, n, t; cin >> m >> n >> t;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int el; cin >> el;
            elev[i][j] = el;
        }
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n-1; j++) {
            edges.push_back(make_pair(abs(elev[i][j]-elev[i][j+1]), make_pair(mapoint(i,j,max(m,n)), mapoint(i,j+1,max(m,n)))));
        }
    }
    for(int j = 0; j < n; j++) {
        for(int i = 0; i < m-1; i++) {
            edges.push_back(make_pair(abs(elev[i][j] - elev[i+1][j]), make_pair(mapoint(i,j,max(m,n)), mapoint(i+1,j,max(m,n)))));
        }
    }
    sort(edges.begin(), edges.end());
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int x; cin >> x;
            if (x == 1) {
                starting[mapoint(i, j, max(m,n))] = 1;
            }
        }
    }
    for(int i = 0; i < maxn2; i++) {
        size[i] = 1;
        if (starting[i] == 1) {
            num_start[i] = 1;
        }
    }
    for(int i = 0; i < maxn2; i++) {
        p[i] = i;
    }
    ll total = 0;
    for(int i = 0; i < edges.size(); i++) {
        int length = edges[i].first;
        int x = edges[i].second.first;
        int y = edges[i].second.second;
        unionSet(x,y);
        if (size[findSet(x)] >= t) {
            total += (long long)num_start[findSet(x)]*(long long)length;
            num_start[findSet(x)] = 0;
        }
    }
    cout << total << endl;
}