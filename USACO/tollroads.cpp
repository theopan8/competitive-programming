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
#define maxn 1010
#define pii pair<int,int>
vector<pair<int, pii> > graph[maxn];
int visited[maxn];
int main() {
    ios_base::sync_with_stdio(0);
    int n, m, x; cin >> n >> m >> x;
    for(int i = 0; i < m; i++) {
        int u, v, c, t; cin >> u >> v >> c >> t;
        graph[u].push_back(make_pair(v, pii(c,t)));
        graph[v].push_back(make_pair(u, pii(c,t)));
    }
    priority_queue<pair<int, pii> > q;
    //(time, (cost, pos))
    q.push(make_pair(0, pii(0, 1)));
    while (!q.empty()) {
        pair<int, pii> phat = q.top();
        int time = -phat.first;
        int cost = phat.second.first;
        int pos = phat.second.second;
        q.pop();
        //cout << time << " " << cost << " " << pos << endl;
        if (visited[pos] != 0 && visited[pos] <= cost) {
            continue;
        }
        if (cost > x) {
            continue;
        }
        if (pos == n && cost <= x) {
            cout << time << endl;
            return 0;
        }
        if (pos == 1) {
            visited[pos] = -1;
        }
        else {
            visited[pos] = cost;
        }
        for(int i = 0; i < graph[pos].size(); i++) {
            if (visited[graph[pos][i].first] == 0 || visited[graph[pos][i].first] > cost + graph[pos][i].second.first) {
                //cout << graph[pos][i].first << " ";
                //cout << time + graph[pos][i].second.second << endl;
                q.push(make_pair(-(time + graph[pos][i].second.second), pii(cost + graph[pos][i].second.first, graph[pos][i].first)));
            }
        }
    }
    cout << -1 << endl;
}