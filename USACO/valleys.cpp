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
#include <cstring>
using namespace std;
#define ll long long
#define pii pair<int, int>
const int maxn = 751;
struct point {
	int x, y, val;
	bool operator < (const point &other) const {
        return this->val < other.val;
    }
};
int n;
int grid[maxn][maxn];
int visited[maxn][maxn];
int inverse[maxn][maxn];
vector<point> points;

int p[maxn * maxn]; //starting from 1
int addedHole[maxn * maxn];
int p1[maxn * maxn];
int size[maxn * maxn];
int isHole[maxn * maxn]; //0 is hole, 1 is not hole
int numHoles[maxn * maxn];
int currHoles[maxn * maxn];
int setSizes[maxn * maxn];
int findSet(int i) {
    if (p[i] == i) {
        return (i);
    }
    else {
        p[i] = findSet(p[i]);
        return (p[i]);
    }
}
int findSet1(int i) {
    if (p1[i] == i) {
        return (i);
    }
    else {
        p1[i] = findSet1(p1[i]);
        return (p1[i]);
    }
}
void unionSet(int i, int j) {
    int x = findSet(i); int y = findSet(j);
    if (x != y) {
		p[y] = x;
		size[x] += size[y];
		numHoles[x] += numHoles[y];
    }
}
void unionSet1(int i, int j) {
    int x = findSet1(i); int y = findSet1(j);
    if (x != y) {
		p1[y] = x;
		if (isHole[x] == 1 || isHole[y] == 1) {
			isHole[x] = 1;
		}
		else {
			isHole[x] = 0;
		}
    }
}
int dx[] = {1, -1, 0, 0, -1, -1, 1, 1};
int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    freopen("valleys.in", "r", stdin);
    freopen("valleys.out", "w", stdout);
    cin >> n;
    for(int i = 0; i < n; i++) {
    	for(int j = 0; j < n; j++) {
    		cin >> grid[i][j];
    		points.push_back(point{i, j, grid[i][j]});
    	}
    }
    sort(points.begin(), points.end());
    for(int i = 1; i <= n * n; i++) {
    	inverse[points[i - 1].x][points[i - 1].y] = i;
    	p[i] = i;
    	p1[i] = i;
    	size[i] = 1;
    	if (points[i - 1].x == n - 1 || points[i - 1].x == 0 || points[i - 1].y == n - 1 || points[i - 1].y == 0) {
    		//cout << i << endl;
    		isHole[i] = 1;
    	}
    }
    for(int i = points.size() - 1; i >= 0; i--) {
    	int x = points[i].x;
    	int y = points[i].y;
    	visited[x][y] = 1;
    	set<int> prevHoles;
    	for(int j = 0; j < 8; j++) {
    		int new_x = x + dx[j];
    		int new_y = y + dy[j];
    		if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n && visited[new_x][new_y] == 1) {
    			if (isHole[findSet1(inverse[new_x][new_y])] == 0) {
    				prevHoles.insert(findSet1(inverse[new_x][new_y]));
    			}
    		}
    	}
    	for(int j = 0; j < 8; j++) {
    		int new_x = x + dx[j];
    		int new_y = y + dy[j];
    		if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n && visited[new_x][new_y] == 1) {
    			unionSet1(i + 1, inverse[new_x][new_y]);
    		}
    	}
    	if (isHole[findSet1(i + 1)] == 0) {
    		currHoles[i] = prevHoles.size() - 1;
    	}
    	else {
    		currHoles[i] = prevHoles.size();
    	}
    }
    ll total = 0;
    for(int i = 0; i < points.size(); i++) {
    	int x = points[i].x;
    	int y = points[i].y;
    	visited[x][y] = 0;
    	for(int j = 0; j < 4; j++) {
    		int new_x = x + dx[j];
    		int new_y = y + dy[j];
    		if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n && visited[new_x][new_y] == 0) {
    			unionSet(i + 1, inverse[new_x][new_y]);
    		}
    	}
    	numHoles[findSet(i + 1)] += currHoles[i];
    	if (numHoles[findSet(i + 1)] == 0) {
    		total += size[findSet(i + 1)];
    	}
    }
    cout << total << endl;
}