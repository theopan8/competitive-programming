#include "grader.h"
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
#include <math.h>
using namespace std;
const int maxn = 100010;
const int maxk = 18;
vector<int> graph[maxn]; //0..n-1
int ancestors[maxk][maxn];
int parents[maxn];
int depth[maxn];
int preorderX[maxn];
int preorderY[maxn];
void addRoad(int a, int b){
    graph[a].push_back(b);
    graph[b].push_back(a);
}
int curr = 0;
void dfs1(int u, int p) {
    curr++;
    preorderX[u] = curr;
    parents[u] = p;
    if (p == -1) depth[u] = 0;
    else depth[u] = depth[p] + 1;
    for(int v : graph[u]) {
        if (v != p) dfs1(v, u);
    }
}
void dfs2(int u, int p) {
    curr++;
    preorderY[u] = curr;
    for(int i = graph[u].size() - 1; i >= 0; i--) {
        if (graph[u][i] != p) dfs2(graph[u][i], u);
    }
}
void buildFarms(){
    dfs1(0, -1);
    curr = 0;
    dfs2(0, -1);
    for(int i = 0; i < maxk; i++) {
        for(int j = 0; j < getN(); j++) {
            if (i == 0) {
                ancestors[i][j] = parents[j];
                continue;
            }
            ancestors[i][j] = ancestors[i-1][ancestors[i-1][j]];
        }
    }
    for(int i = 0; i < getN(); i++) {
        setFarmLocation(i, preorderX[i], preorderY[i]);
    }
}

void notifyFJ(int a, int b){
    if (depth[a] > depth[b]) {
        swap(a,b);
    }
    int ax = preorderX[a];
    int ay = preorderY[a];
    int bx = preorderX[b];
    int by = preorderY[b];
    for(int j = maxk - 1; j >= 0; j--) {
        if ((1 << j) & (depth[b] - depth[a])) {
            b = ancestors[j][b];
        }
    }
    if (a == b) {
        addBox(min(ax, bx), min(ay, by), max(ax, bx), max(ay, by));
    }
    else {
        for(int j = maxk - 1; j >= 0; j--) {
            if (ancestors[j][a] == ancestors[j][b]) {
                continue;
            }
            a = ancestors[j][a];
            b = ancestors[j][b];
        }
        addBox(min(ax, preorderX[a]), min(ay, preorderY[a]), max(ax, preorderX[a]), max(ay, preorderY[a]));
        b = parents[b];
        addBox(min(bx, preorderX[b]), min(by, preorderY[b]), max(bx, preorderX[b]), max(by, preorderY[b]));
    }
}