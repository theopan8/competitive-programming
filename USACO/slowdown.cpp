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
#define MaxVal 100005
int tree[MaxVal];
vector<int> graph[MaxVal];
int visited[MaxVal];
map<int,int> barn_cowmap;
int answer[MaxVal];
int read(int idx){
    int sum = 0;
    while (idx > 0){
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
void update(int idx, int val){
    while (idx <= MaxVal){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}

void dfs (int pasture) {
    if (visited[pasture] != 0) {
        return;
    }
    visited[pasture] = 1;
    answer[barn_cowmap[pasture]] = read(barn_cowmap[pasture]);
    update(barn_cowmap[pasture], 1);
    for(int i = 0; i < graph[pasture].size(); i++) {
        if (visited[graph[pasture][i]] == 0) {
            dfs(graph[pasture][i]);
        }
    }
    update(barn_cowmap[pasture], -1);
}

int main() {
    int n; cin >> n;
    for(int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for(int i = 1; i <= n; i++) {
        int p; cin >> p;
        barn_cowmap[p] = i;
    }
    dfs(1);
    for(int i = 1; i <= n; i++) {
        cout << answer[i] << endl;
    }
}
