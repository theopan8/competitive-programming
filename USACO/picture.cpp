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
#define maxn 20010
map<int,map<int, int> > grid;
int ans = 0;
map<int,map<int, int> > visited;
int minx = -1;
int maxx = 0;
int miny = -1;
int maxy = 0;
void floodfill (int x, int y) {
    if (visited[x][y] == 1) {
        return;
    }
    //cout << x << " " << y << endl;
    if (grid[x][y] == 1) {
        ans += 1;
        return;
    }
    visited[x][y] = 1;
    if (x > minx) {
        if (visited[x-1][y] == 0) {
            floodfill(x-1, y);
        }
    }
    if (x < maxx) {
        if (visited[x+1][y] == 0) {
            floodfill(x+1, y);
        }
    }
    if (y > miny) {
        if (visited[x][y-1] == 0) {
            floodfill(x, y-1);
        }
    }
    if (y < maxy) {
        if (visited[x][y+1] == 0) {
            floodfill(x, y+1);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        for(int i = x1; i < x2; i++) {
            for(int j = y1; j < y2; j++) {
                grid[i][j] = 1;
            }
        }
        if (minx == -1 || x1 < minx) {
            minx = x1;
        }
        if (maxx < x2) {
            maxx = x2;
        }
        if (miny == -1 || y1 < miny) {
            miny = y1;
        }
        if (maxy < y2) {
            maxy = y2;
        }
    }
    minx -= 2;
    maxx += 2;
    miny -= 2;
    maxy += 2;
    for(int i = minx; i <= maxx; i++) {
        for(int j = miny; j <= maxy; j++) {
            if (visited[i][j] == 0 && grid[i][j] == 0) {
                floodfill(i, j);
            }
        }
    }
    cout << ans << endl;
}