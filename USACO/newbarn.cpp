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
#define ll long long
#define maxn 100005
#define maxk 18
#define pci pair<char, int>
#define pii pair<int, int>
vector<int> graph[maxn];
int parents[maxn];
int depth[maxn];
int visited[maxn];
int ancestors[maxk][maxn];
int components[maxn];
int num_components = 0;
int num_nodes = 0;
pii diameters[maxn];
int LCA (int a, int b) {
    if (depth[a] > depth[b]) {
        swap(a,b);
    }
    for(int j = maxk -1; j >= 0; j--) {
        if ((1 << j) & (depth[b] - depth[a])) {
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
int calc_dist (int a, int b) {
    int anc = LCA(a,b);
    return (depth[a] + depth[b] - 2*depth[anc]);
}
int main() {
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        char x; cin >> x;
        if (x == 'B') {
            int y; cin >> y;
            num_nodes++;
            if (y == -1) {
                num_components++;
                components[num_nodes] = num_components;
                diameters[components[num_nodes]] = pii(num_nodes, num_nodes);
            }
            else {
                parents[num_nodes] = y;
                components[num_nodes] = components[y];
                depth[num_nodes] = depth[y] + 1;
                for(int j = 0; j < maxk; j++) {
                    if (j == 0) {
                        ancestors[j][num_nodes] = parents[num_nodes];
                        continue;
                    }
                    ancestors[j][num_nodes] = ancestors[j-1][ancestors[j-1][num_nodes]];
                }
                int curr_diam = calc_dist(diameters[components[num_nodes]].first, diameters[components[num_nodes]].second);
                if (curr_diam < calc_dist(diameters[components[num_nodes]].first, num_nodes)) diameters[components[num_nodes]] = pii(diameters[components[num_nodes]].first, num_nodes);
                if (curr_diam < calc_dist(diameters[components[num_nodes]].second, num_nodes)) diameters[components[num_nodes]] = pii(diameters[components[num_nodes]].second, num_nodes);
            }
        }
        else {
            int y; cin >> y;
            cout << max(calc_dist(diameters[components[y]].first, y), calc_dist(diameters[components[y]].second, y)) << '\n';
        }
    }
}