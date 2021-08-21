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
typedef pair<ll, ll> pii;
const int MAXK = 50010;
const ll MOD = 1000000007;
vector<vector<int>> graph[MAXK];
vector<ll> dist[MAXK];
vector<ll> dist1[MAXK];
vector<ll> alldistEven[MAXK];
vector<ll> alldistOdd[MAXK];
vector<ll> baddistEven[MAXK];
vector<ll> baddistOdd[MAXK];
void bfs(int x) {
	vector<int> visited(graph[x].size());
	queue<pii> q;
	q.push(pii(0, 0));
	dist[x][0] = 0;
	visited[0] = 1;
	while(!q.empty()) {
		int u = q.front().first;
		int d = q.front().second;
		q.pop();
		for(int v : graph[x][u]) {
			if(!visited[v]) {
				dist[x][v] = d + 1;
				visited[v] = 1;
				q.push(pii(v, dist[x][v]));
			}
		}
	}
}
void bfs1(int x) {
	vector<int> visited(graph[x].size());
	vector<int> visited1(graph[x].size());
	dist1[x][0] = -1;
	queue<pii> q;
	q.push(pii(0, 0));
	visited[0] = 1;
	while(!q.empty()) {
		int u = q.front().first;
		int d = q.front().second;
		q.pop();
		for(int v : graph[x][u]) {
			if(!visited[v]) {
				visited[v] = 1;
				q.push(pii(v, dist[x][v]));
			}
			else if(!visited1[v]) {
				if((dist[x][v] % 2) != ((d + 1) % 2)) {
					visited1[v] = 1;
					dist1[x][v] = d + 1;
					q.push(pii(v, dist1[x][v]));
				}
			}
		}
	}
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int k; cin >> k;
    int maxN = 0;
    int totalN = 0;
    for(int i = 0; i < k; i++) {
    	int n, m; cin >> n >> m;
    	maxN = max(maxN, n);
    	totalN += n;
    	graph[i].resize(n);
    	dist[i].resize(n);
    	dist1[i].resize(n);
    	for(int j = 0; j < m; j++) {
    		int x, y; cin >> x >> y;
    		x--; y--;
    		graph[i][x].push_back(y);
    		graph[i][y].push_back(x);
    	}
    }
    for(int i = 0; i < k; i++) {
    	bfs(i);
    	bfs1(i);
    	for(int j = 0; j < graph[i].size(); j++) {
    		if(dist[i][j] % 2 == 0) alldistEven[i].push_back(dist[i][j]);
    		else alldistOdd[i].push_back(dist[i][j]);
    		if(dist1[i][0] != -1) {
    			if(dist1[i][j] % 2 == 0) {
    				alldistEven[i].push_back(dist1[i][j]);
    				baddistEven[i].push_back(dist1[i][j]);
    			}
    			else {
    				alldistOdd[i].push_back(dist1[i][j]);
    				baddistOdd[i].push_back(dist1[i][j]);
    			}
    		}
    	}
    	sort(alldistEven[i].begin(), alldistEven[i].end());
    	sort(alldistOdd[i].begin(), alldistOdd[i].end());
    	sort(baddistEven[i].begin(), baddistEven[i].end());
    	sort(baddistOdd[i].begin(), baddistOdd[i].end());
    }
    vector<ll> currEven(k);
    vector<ll> currOdd(k);
    ll prevcnt = 0;
    ll ans = 0;
    for(int i = 0; i <= 4 * maxN; i += 2) {
    	ll currcnt = 1;
    	for(int j = 0; j < k; j++) {
    		while(currEven[j] < alldistEven[j].size()) {
    			if(alldistEven[j][currEven[j]] == i) currEven[j]++;
    			else break;
    		}
    		currcnt = (currcnt * currEven[j]) % MOD;
    	}
    	ans = (ans + ((currcnt - prevcnt) * (ll)i) % MOD) % MOD;
    	prevcnt = currcnt;
    }
    prevcnt = 0;
    for(int i = 1; i <= 4 * maxN; i += 2) {
    	ll currcnt = 1;
    	for(int j = 0; j < k; j++) {
    		while(currOdd[j] < alldistOdd[j].size()) {
    			if(alldistOdd[j][currOdd[j]] == i) currOdd[j]++;
    			else break;
    		}
    		currcnt = (currcnt * currOdd[j]) % MOD;
    	}
    	ans = (ans + ((currcnt - prevcnt) * (ll)i) % MOD) % MOD;
    	prevcnt = currcnt;
    }
    ll ansbad = 0;
    vector<ll> badEven(k);
    vector<ll> badOdd(k);
    prevcnt = 0;
    for(int i = 0; i <= 4 * maxN; i += 2) {
    	ll currcnt = 1;
    	for(int j = 0; j < k; j++) {
    		while(badEven[j] < baddistEven[j].size()) {
    			if(baddistEven[j][badEven[j]] == i) badEven[j]++;
    			else break;
    		}
	    	currcnt = (currcnt * badEven[j]) % MOD;
    	}
    	ansbad = (ansbad + ((currcnt - prevcnt) * (ll)i) % MOD) % MOD;
    	prevcnt = currcnt;
    }
    prevcnt = 0;
    for(int i = 1; i <= 4 * maxN; i += 2) {
    	ll currcnt = 1;
    	for(int j = 0; j < k; j++) {
    		while(badOdd[j] < baddistOdd[j].size()) {
    			if(baddistOdd[j][badOdd[j]] == i) badOdd[j]++;
    			else break;
    		}
			currcnt = (currcnt * badOdd[j]) % MOD;
    	}
    	ans = (ans + ((currcnt - prevcnt) * (ll)i) % MOD) % MOD;
    	prevcnt = currcnt;
    }
    cout << ((ans - ansbad) % MOD + MOD) % MOD << '\n';
}