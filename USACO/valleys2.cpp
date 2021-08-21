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
using namespace std;
#define ll long long
const int maxn = 751;
struct point {
	int x, y, val;
	bool operator < (const point &other) const {
        return this->val < other.val;
    }
};
int grid[maxn][maxn];
int visited[maxn][maxn];
int inverse[maxn][maxn];
vector<point> points;

int p[maxn * maxn]; //starting from 1
int size[maxn * maxn];
int region[maxn * maxn]; //0 if region and 1 if not region
int findSet(int i) {
    if (p[i] == i) {
        return (i);
    }
    else {
        p[i] = findSet(p[i]);
        return (p[i]);
    }
}
void unionSet(int i, int j) {
    int x = findSet(i); int y = findSet(j);
    if (x != y) {
		p[y] = x;
		size[x] += size[y];
    }
}

int dx[] = {1, -1, 0, 0, -1, -1, 1, 1};
int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
int n;
int visitDFS[maxn][maxn];
int totalDFS = 0;
bool good = false;
void dfs(int x, int y, int prev) {
    if (visitDFS[x][y] == 1) {
        return;
    }
    totalDFS++;
    visitDFS[x][y] = 1;
    for(int i = 0; i < 8; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n) {
            if (visitDFS[new_x][new_y] == 0 && findSet(inverse[new_x][new_y]) != findSet(prev)) {
                dfs(new_x, new_y, prev);
            }
        }
        else {
            good = true;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    //freopen("valleys.in", "r", stdin);
    //freopen("valleys.out", "w", stdout);
    cin >> n;
    for(int i = 0; i < n; i++) {
    	for(int j = 0; j < n; j++) {
    		cin >> grid[i][j];
    		points.push_back(point{i, j, grid[i][j]});
    	}
    }
    sort(points.begin(), points.end());
    for(int i = 1; i <= n * n; i++) {
    	inverse[points[i].x][points[i].y] = i;
    	p[i] = i;
    	size[i] = 1;
    }
    visited[points[0].x][points[0].y] = 1;
    ll total = 0;
    for(int i = 1; i < n * n; i++) {
    	int x = points[i].x;
    	int y = points[i].y;
    	set<int> regions;
    	for(int j = 0; j < 4; j++) {
    		int new_x = x + dx[j];
    		int new_y = y + dy[j];
    		if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n) {
    			if (visited[new_x][new_y] == 1) {
    				int prev = regions.size();
    				regions.insert(findSet(inverse[new_x][new_y]));
    				if (region[findSet(inverse[new_x][new_y])] == 0) {
    					if (regions.size() != prev) {
    						total += size[findSet(inverse[new_x][new_y])];
                            //cout << total << endl;
    					}
    				}
    			}
    		}
    	}
    	if (regions.size() == 0) {
    		visited[x][y] = 1;
    		continue;
    	}
    	int prev = *regions.begin();
		for(auto it = regions.begin(); it != regions.end(); it++) {
			unionSet(prev, *it);
		}
		unionSet(prev, inverse[x][y]);
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if (findSet(inverse[j][k]) != findSet(prev)) {
                    dfs(j, k, prev);
                    break;
                }
            }
        }
        if (totalDFS != n * n - size[prev] || !good) {
            region[prev] = 1;
        }
        else {
            region[prev] = 0;
        }
        totalDFS = 0;
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                visitDFS[j][k] = 0;
            }
        }
        good = false;
    	visited[x][y] = 1;
    }
    cout << total + n * n << endl;
}