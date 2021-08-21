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
#define maxn 100005
//#define int long long
map<int,int> barns;
vector<pair<int,int> > graph[maxn];
int visited[maxn];
int visited1[maxn];
int total = 0;
int subtrees[maxn];
int answers[maxn];
int dfs (int start, int dist) {
    if (visited[start]) {
        return 0;
    }
    visited[start] = 1;
    total += barns[start]*dist;
    if (start != 1) {
        if (graph[start].size() == 1) {
            subtrees[start] = barns[start];
            return barns[start];
        }
    }
    subtrees[start] = barns[start];
    for(int i = 0; i < graph[start].size(); i++) {
        if (visited[graph[start][i].first] == 0) {
            subtrees[start] += dfs(graph[start][i].first, dist + graph[start][i].second);
        }
    }
    return subtrees[start];
}
void dfs1 (int start, int curr_incon) {
    if (visited1[start]) {
        return;
    }
    visited1[start] = 1;
    answers[start] = curr_incon;
    for(int i = 0; i < graph[start].size(); i++) {
        if (!visited1[graph[start][i].first]) {
            int curr = curr_incon + (subtrees[1]-subtrees[graph[start][i].first])*graph[start][i].second - subtrees[graph[start][i].first]*graph[start][i].second;
            //cout << "curr: " << curr << endl;
            dfs1(graph[start][i].first, curr);
        }
    }
}
int main() {
    //freopen("hayfeast.in", "r", stdin);
    //freopen("hayfeast.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        int c; cin >> c;
        barns[i] = c;
    }
    for(int i = 0; i < n-1; i++) {
        int a, b, l; cin >> a >> b >> l;
        graph[a].push_back(make_pair(b, l));
        graph[b].push_back(make_pair(a, l));
    }
    dfs(1, 0);
    dfs1(1, total);
    int min = -1;
    /*for(int i = 1; i <= n; i++) {
        cout << subtrees[i] << endl;
    }*/
    for(int i = 1; i <= n; i++) {
        //cout << answers[i] << endl;
        if (min == -1) {
            min = answers[i];
        }
        else {
            if (answers[i] < min) {
                min = answers[i];
            }
        }
    }
    cout << min << endl;
}
