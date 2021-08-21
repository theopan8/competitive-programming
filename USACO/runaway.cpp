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
#define maxn 200005
#define ll long long
#define int long long
vector<ll> graph[maxn];
ll par_dist[maxn];
ll dist[maxn];
int parent[maxn];
int counter[maxn];
vector<int> dist_vec;
int answer[maxn];
//calculates distances to the root
void dist_dfs (int barn, ll distance) {
    dist[barn] = distance;
    for(int i = 0; i < graph[barn].size(); i++) {
        dist_dfs(graph[barn][i], distance+par_dist[graph[barn][i]]);
    }
}
//creates counter
void dfs_count (int barn, int min_l) {
    dist_vec.push_back(barn);
    int lower = 0;
    int higher = dist_vec.size()-1;
    //cout << "length " << higher << endl;
    while (lower < higher) {
        //cout << "lower " << lower << " higher " << higher << endl;
        int average = (lower+higher)/2;
        if (dist[barn] - dist[dist_vec[average]] <= min_l) {
            higher = average;
        }
        else {
            lower = average+1;
        }
    }
    //cout << barn << " " << dist_vec[higher] << endl;
    counter[barn] += 1;
    counter[parent[dist_vec[higher]]] -= 1;
    for(int i = 0; i < graph[barn].size(); i++) {
        dfs_count(graph[barn][i], min_l);
    }
    dist_vec.pop_back();
}
//give us answer
void dfs_total (int barn) {
    if (graph[barn].size() == 0) {
        answer[barn] = counter[barn];
        return;
    }
    int total = counter[barn];
    for(int i = 0; i < graph[barn].size(); i++) {
        dfs_total(graph[barn][i]);
        total += answer[graph[barn][i]];
    }
    answer[barn] = total;
}
main() {
    //freopen("runaway.in", "r", stdin);
    //freopen("runaway.out", "w", stdout);
    ll n, l; cin >> n >> l;
    for(int i = 2; i < n+1; i++) {
        ll p, d; cin >> p >> d;
        parent[i] = p;
        par_dist[i] = d;
        graph[p].push_back(i);
    }
    dist_dfs(1, 0);
    dfs_count(1, l);
    dfs_total(1);
    for(int i = 1; i <= n; i++) {
        cout << answer[i] << endl;
    }
    //cout << counter[1] << " " << counter[2] << " " << counter[3] << " " << counter[4] << endl;
}
