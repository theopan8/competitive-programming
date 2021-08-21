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
ll val[maxn];
vector<int> order;
int tree[maxn];
int parents[maxn];
vector<int> graph[maxn];
int preorder[maxn];
int anser[maxn];
bool comp (int i, int j) {
	return val[i] < val[j];
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
int curr = 0;
void pre_dfs(int start) {
	curr++;
	preorder[start] = curr;
	for(int v : graph[start]) {
		if (parents[start] != v) {
			pre_dfs(v);
		}
	}
}
void dfs_ans(int start) {
	int prev = read(val[start]);
	for(int v : graph[start]) {
		if (parents[start] != v) {
			dfs_ans(v);
		}
	}
	int forw = read(val[start]);
	anser[start] = forw - prev;
	update(val[start], 1);
}
int main() {
	freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
    	ll x; cin >> x;
    	val[i+1] = x;
    	order.push_back(i+1);
    }
    sort(order.begin(), order.end(), comp);
    for(int i = 0; i < n; i++) {
    	val[order[i]] = n - i;
    }
    for(int i = 2; i <= n; i++) {
    	int p; cin >> p;
    	parents[i] = p;
    	graph[p].push_back(i);
    }
    pre_dfs(1);
    dfs_ans(1);
    for(int i = 1; i <= n; i++) {
    	cout << anser[i] << '\n';
    }
}