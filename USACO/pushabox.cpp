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
using namespace std;
#define maxc 1500
#define maxr 1500
#define maxv 2250000
#define pii pair<int,int>
#define pip pair<int, pair<int,int> >
struct Edge {
	int u;
	int v;
	int bcc;
	int other (int vertex) {
		return u + v - vertex;
	}
};
vector<Edge*> graph[maxv];
char grid[maxr][maxc];
int toInt (int r, int c) {
	return maxc * r + c;
}
int E = 0;
Edge edges[2*maxv];
void addEdge (int u, int v) {
	edges[E] = Edge{u,v,0};
	graph[u].push_back(&edges[E]);
	graph[v].push_back(&edges[E]);
	E++;
}
int low[maxv];
int disc[maxv];
int parent[maxv];
int visited[maxv];
stack<Edge*> edges_stack;
int t = 0;
int bcc_count = 0;
int artic_points[maxv];
void dfs_bic (int v) {
	t++;
    disc[v] = t;
    low[v] = t;
    visited[v] = 1;
    int child = 0;
    for(Edge* e : graph[v]) {
    	int u = e->other(v);
        if (visited[u] == 0) {
            child += 1;
            edges_stack.push(e);
            parent[u] = v;
            dfs_bic(u);
            low[v] = min(low[v], low[u]);
            if ((parent[v] == 0 && child > 1) || (parent[v] != 0 && low[u] >= disc[v])) {
            	artic_points[v] = 1;
            	bcc_count++;
                while (edges_stack.top() != e) {
                    edges_stack.top()->bcc = bcc_count;
                    edges_stack.pop();
                }
                edges_stack.top()->bcc = bcc_count;
                edges_stack.pop();
            }
        }
        else if (parent[v] != u) {
            if (disc[u] < low[v]) {
            	low[v] = disc[u];
            	edges_stack.push(e);
            }
        }
    }
}
pii bessie;
pii box;
pii dir[4] = {pii(1,0), pii(0,1), pii(-1, 0), pii(0, -1)};
int bfs_visit[4][maxr][maxc];
int fast_edge[4][maxr][maxc];
int temp_visit[maxr][maxc];
int n, m;
void dfs_check (int x, int y) {
	if (temp_visit[x][y] != 0) return;
	temp_visit[x][y] = 1;
	for(int i = 0; i < 4; i++) {
		int new_x = x + dir[i].first;
		int new_y = y + dir[i].second;
		if (new_x < 0 || new_x >= n) continue;
		if (new_y < 0 || new_y >= m) continue;
		if (grid[new_x][new_y] == '#' || grid[new_x][new_y] == 'B') continue;
		if (temp_visit[new_x][new_y] == 0) dfs_check(new_x, new_y); 
	}
}
void bfs () {
	queue<pip> q;
	dfs_check(bessie.first, bessie.second);
	for(int i = 0; i < 4; i++) {
		int new_x = box.first + dir[i].first;
		int new_y = box.second + dir[i].second;
		if (new_x < 0 || new_x >= n) continue;
		if (new_y < 0 || new_y >= m) continue;
		if (grid[new_x][new_y] == '#') continue;
		if (temp_visit[new_x][new_y] == 1) q.push(pip(i, box));
	}
	while (!q.empty()) {
		pip point = q.front();
		q.pop();
		int director = point.first;
		int pos_x = point.second.first;
		int pos_y = point.second.second;
		int cow_x = pos_x + dir[director].first;
		int cow_y = pos_y + dir[director].second;
		if (bfs_visit[director][pos_x][pos_y] == 1) continue;
		bfs_visit[director][pos_x][pos_y] = 1;
		//cout << director << " " << pos_x << " " << pos_y << '\n';
		for(int i = 0; i < 4; i++) {
			int new_x = pos_x + dir[i].first;
			int new_y = pos_y + dir[i].second;
			if (new_x < 0 || new_x >= n) continue;
			if (new_y < 0 || new_y >= m) continue;
			if (grid[new_x][new_y] == '#') continue;
			for(int j = 0; j < 4; j++) {
				bool done = false;
				if (fast_edge[j][cow_x][cow_y] == 0) continue;
				for(int k = 0; k < 4; k++) {
					if (fast_edge[k][new_x][new_y] == 0) continue;
					if (fast_edge[k][new_x][new_y] == fast_edge[j][cow_x][cow_y]) {
						done = true;
						bfs_visit[i][pos_x][pos_y] = 1;
						int new_x2 = pos_x + dir[(i+2)%4].first;
						int new_y2 = pos_y + dir[(i+2)%4].second;
						if (new_x2 < 0 || new_x2 >= n) break;
						if (new_y2 < 0 || new_y2 >= m) break;
						if (grid[new_x2][new_y2] == '#') break;
						if (bfs_visit[i][new_x2][new_y2] == 0) q.push(pip(i, pii(new_x2, new_y2))); break;
					}
				}
				if (done) break;
			}
		}
	}
}
int main() {
    freopen("pushabox.in", "r", stdin);
    freopen("pushabox.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int q; cin >> n >> m >> q;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'A') bessie = pii(i,j);
            if (grid[i][j] == 'B') box = pii(i,j);
        }
    }
    for(int i = 0; i < n; i++) {
    	for(int j = 0; j + 1 < m; j++) {
    		if (grid[i][j] != '#' && grid[i][j+1] != '#') {
    			addEdge(toInt(i, j), toInt(i, j+1));
    		}
    	}
    }
    for(int i = 0; i + 1 < n; i++) {
    	for(int j = 0; j < m; j++) {
    		if (grid[i][j] != '#' && grid[i+1][j] != '#') {
    			addEdge(toInt(i, j), toInt(i+1,j));
    		}
    	}
    }
    //cout << E << '\n';
    //biconnected components
    for(int i = 0; i < n; i++) {
    	for(int j = 0; j < m; j++) {
    		if (grid[i][j] != '#') {
    			int u = toInt(i, j);
    			if (visited[u] == 0) {
    				dfs_bic(u);
    				if (!edges_stack.empty()) {
    					bcc_count++;
    				}
    				while (!edges_stack.empty()) {
    					edges_stack.top()->bcc = bcc_count;
    					edges_stack.pop();
    				}
    			}
    		}
    	}
    }
    for(int i = 0; i < E; i++) {
    	int p1 = edges[i].u;
    	int p2 = edges[i].v;
    	int val = edges[i].bcc;
    	//cout << val << '\n';
    	int y1 = p1 % maxc;
    	int x1 = (p1 - y1) / maxc;
    	int y2 = p2 % maxc;
    	int x2 = (p2 - y2) / maxc;
    	int ans = 0;
    	for(int j = 0; j < 4; j++) {
    		if (x1 + dir[j].first == x2 && y1 + dir[j].second == y2) {
    			ans = j;
    			break;
    		}
    	}
    	fast_edge[ans][x1][y1] = val;
    	fast_edge[(ans + 2) % 4][x2][y2] = val;
    	//cout << x1 << " " << y1 << " " << x2 << " " << y2 << '\n';
    	//cout << ans << " " << (ans + 2) % 4 << '\n';
    }
    bfs();
    /*for(int i = 0; i < n; i++) {
    	for(int j = 0; j < m; j++) {
    		for(int k = 0; k < 4; k++) {
    			cout << k << " " << i << " " << j << '\n';
    			cout << bfs_visit[k][i][j] << '\n';
    		}
    	}
    }*/
    for(int i = 0; i < q; i++) {
    	int x, y; cin >> x >> y;
    	x--; y--;
    	//cout << x << " " << y << endl;
    	bool good = false;
    	for(int j = 0; j < 4; j++) {
    		if (bfs_visit[j][x][y] == 1 || (x == box.first && y == box.second)) {
    			good = true;
    			break;
    		}
    	}
    	if (good) {
    		cout << "YES" << '\n';
    	}
    	else {
    		cout << "NO" << '\n';
    	}
    }
}