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
#define maxn 200010
#define maxk 18
#define ll long long
vector<int> adj[maxn];
int subsize[maxn];
int dep[maxn];
int preorder[maxn];
int ancestors[maxk][maxn];
int parents[maxn];
int tree[maxn];
int numseen = 0;
void predfs(int u, int p) {
    preorder[u] = ++numseen;
    dep[u] = p == -1 ? 1 : dep[p]+1;
    parents[u] = p == -1 ? 1 : p;
    subsize[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        predfs(v, u);
        subsize[u] += subsize[v];
    }
}
int LCA (int a, int b) {
    if (dep[a] > dep[b]) {
        swap(a,b);
    }
    for(int j = maxk -1; j >= 0; j--) {
        if ((1 << j) & (dep[b] - dep[a])) {
            b = ancestors[j][b];
        }
    }
    if (a == b) {
        return a;
    }
    for(int j = maxk-1; j >= 0; j--) {
        if (ancestors[j][a] == ancestors[j][b]) {
            continue;
        }
        a = ancestors[j][a];
        b = ancestors[j][b];
    }
    return parents[a];
}
int read(int idx){
    int sum = 0;
    while (idx > 0){
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
void update(int idx ,int val){
    while (idx <= maxn){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    predfs(1, -1);
    for(int i = 0; i < maxk; i++) {
        for(int j = 1; j <= n; j++) {
            if (i == 0) {
                ancestors[i][j] = parents[j];
                continue;
            }
            ancestors[i][j] = ancestors[i-1][ancestors[i-1][j]];
        }
    }
    for(int i = 0; i < m; i++) {
        char x; cin >> x;
        if (x == 'P') {
            int y, z; cin >> y >> z;
            int ancestor = LCA(y, z);
            update(preorder[y], 1);
            update(preorder[z], 1);
            update(preorder[ancestor], -2);
        }
        else {
            int y, z; cin >> y >> z;
            if (preorder[y] > preorder[z]) {
                cout << read(preorder[y]+subsize[y]-1) - read(preorder[y]-1) << endl;
            }
            else {
                cout << read(preorder[z]+subsize[z]-1) - read(preorder[z]-1) << endl;
            }
        }
    }
}