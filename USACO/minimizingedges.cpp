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
#include <stack>
#include <cstring>
#include <deque>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 100010;
vector<int> graph[MAXN];
int dist[MAXN];
int dist1[MAXN];
int n;
void bfs(int x) {
    vector<int> visited(n + 1);
    queue<pii> q;
    q.push(pii(1, 0));
    dist[1] = 0;
    visited[1] = 1;
    while(!q.empty()) {
        int u = q.front().first;
        int d = q.front().second;
        q.pop();
        for(int v : graph[u]) {
            if(!visited[v]) {
                dist[v] = d + 1;
                visited[v] = 1;
                q.push(pii(v, dist[v]));
            }
        }
    }
}
void bfs1(int x) {
    vector<int> visited(n + 1);
    vector<int> visited1(n + 1);
    dist1[1] = -1;
    queue<pii> q;
    q.push(pii(1, 0));
    visited[1] = 1;
    while(!q.empty()) {
        int u = q.front().first;
        int d = q.front().second;
        q.pop();
        for(int v : graph[u]) {
            if(!visited[v]) {
                visited[v] = 1;
                q.push(pii(v, dist[v]));
            }
            else if(!visited1[v]) {
                if((dist[v] % 2) != ((d + 1) % 2)) {
                    visited1[v] = 1;
                    dist1[v] = d + 1;
                    q.push(pii(v, dist1[v]));
                }
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--) {
        int m; cin >> n >> m;
        for(int i = 0; i < m; i++) {
            int x, y; cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        bfs(1);
        bfs1(1);
        if(dist1[1] == -1) cout << n - 1 << '\n';
        else cout << m << '\n';
        for(int i = 1; i <= n; i++) {
            graph[i].clear();
            dist[i] = 0;
            dist1[i] = 0;
        }
    }
}