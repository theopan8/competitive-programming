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
#include <cstring>
using namespace std;
#define maxn 40110
#define pii pair<int,int>
vector<pii> graph[maxn];
vector<int> candy_eat;
vector<int> q;
int max_length = 0;
int indexes[maxn];
int dp[maxn];
int visited[maxn];
void topological (int start) {
    visited[start] = 1;
    for(pii v: graph[start]) {
        if (visited[v.first] == 0) {
            topological(v.first);
        }
    }
    int max = 0;
    for(pii v: graph[start]) {
        if (max < dp[v.first] + v.second) {
            max = dp[v.first] + v.second;
        }
    }
    dp[start] = max;
    q.push_back(start);
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, nopt, f, m; cin >> n >> nopt >> f >> m;
    for(int i = 0; i < nopt; i++) {
        int c; cin >> c;
        candy_eat.push_back(c);
    }
    for(int i = 0; i < f; i++) {
        int fn; cin >> fn;
        if (fn == n) {
            continue;
        }
        graph[fn].push_back(pii(fn+m,0));
    }
    for(int i = 0; i < nopt; i++) {
        for(int j = candy_eat[i]; j <= m+n; j++) {
            graph[j].push_back(pii(j-candy_eat[i], candy_eat[i]));
        }
    }
    topological(n);
    reverse(q.begin(), q.end());
    for(int i = 0; i < q.size(); i++) {
        indexes[q[i]] = i+1;
    }
    bool bad = false;
    for(int i = 0; i <= n+m; i++) {
        if (indexes[i] == 0) {
            continue;
        }
        for(pii v: graph[i]) {
            if (indexes[v.first] == 0) {
                continue;
            }
            if (indexes[i] > indexes[v.first]) {
                bad = true;
            }
        }
    }
    if (bad) {
        cout << -1 << endl;
    }
    else {
        cout << dp[n] << endl;
    }
}