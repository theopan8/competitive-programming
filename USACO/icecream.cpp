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
#define maxn 100010
/*vector<int> childs[maxn];
int costs[maxn];
int subtrees[maxn];
int subtrees_map[maxn];
int value = 1;
void dfs (int start) {
    int max = costs[start];
    for(int i = 0; i < childs[start].size(); i++) {
        dfs(childs[start][i]);
        if (max < subtrees[childs[start][i]]) {
            max = subtrees[childs[start][i]];
        }
    }
    subtrees[start] = max;
}*/
set<int> childs[maxn];
int costs[maxn];
int subtrees[maxn];
int subtrees_map[maxn];
int value = 1;
void dfs (int start) {
    int max = costs[start];
    for(auto i = childs[start].begin(); i != childs[start].end(); i++) {
        dfs(*i);
        if (max < subtrees[*i]) {
            max = subtrees[*i];
        }
    }
    subtrees[start] = max;
}
void preorder (int start) {
    subtrees_map[value] = start; value += 1;
    for(auto i = childs[start].begin(); i != childs[start].end(); i++) {
        preorder(*i);
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        int c; cin >> c;
        costs[i] = c;
    }
    for(int i = 2; i <= n; i++) {
        int p; cin >> p;
        childs[p].insert(i);
    }
    dfs(1);
    preorder(1);
    for(int i = 0; i < q; i++) {
        int x, k; cin >> x >> k;
        if (subtrees[subtrees_map[x]] >= k) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
}
