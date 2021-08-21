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
#define maxn 55
#define pii pair<int,int>
int grid[maxn][maxn];
int visited[4][maxn][maxn]; //direction, pos
pii dir[4] = {pii(-1, 0), pii(0, 1), pii(1, 0), pii(0, -1)};
//N E S W
int first_dir;
pii first_pos;
int main() {
    ios_base::sync_with_stdio(0);
    int r, c; cin >> r >> c;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            char x; cin >> x;
            if (x == '_') {
                continue;
            }
            if (x == 'X') {
                grid[i][j] = 1;
            }
            else {
                first_pos = pii(i, j);
                if (x == 'N') {
                    first_dir = 0;
                }
                else if (x == 'E') {
                    first_dir = 1;
                }
                else if (x == 'S') {
                    first_dir = 2;
                }
                else {
                    first_dir = 3;
                }
            }
        }
    }
    priority_queue<pair<pii, pii> > q;
    q.push(make_pair(pii(0, first_dir), first_pos));
    while (!q.empty()) {
        pair<pii, pii> x = q.top();
        q.pop();
        int dist = -x.first.first;
        int direction = x.first.second;
        int pos_x = x.second.first;
        int pos_y = x.second.second;
        //cout << dist << " " << direction << " " << pos_x << " " << pos_y << endl;
        if (visited[direction][pos_x][pos_y] != 0) {
            continue;
        }
        visited[direction][pos_x][pos_y] = 1;
        if (pos_x == 0 || pos_x == r-1) {
            cout << dist << endl;
            return 0;
        }
        if (pos_y == 0 || pos_y == c-1) {
            cout << dist << endl;
            return 0;
        }
        int dx = dir[direction].first;
        int dy = dir[direction].second;
        if (grid[pos_x+dx][pos_y+dy] == 0 && visited[direction][pos_x+dx][pos_y+dy] == 0) {
            q.push(make_pair(pii(-dist, direction), pii(pos_x+dx, pos_y+dy)));
        }
        if (direction == 0) {
            if (visited[direction+1][pos_x][pos_y] == 0) {
                q.push(make_pair(pii(-dist-1, direction+1), pii(pos_x, pos_y)));
            }
            if (visited[direction+3][pos_x][pos_y] == 0) {
                q.push(make_pair(pii(-dist-1, direction +3), pii(pos_x, pos_y)));
            }
        }
        else if (direction == 3) {
            if (visited[direction-1][pos_x][pos_y] == 0) {
                q.push(make_pair(pii(-dist-1, direction-1), pii(pos_x, pos_y)));
            }
            if (visited[direction-3][pos_x][pos_y] == 0) {
                q.push(make_pair(pii(-dist-1, direction -3), pii(pos_x, pos_y)));
            }
        }
        else {
            if (visited[direction-1][pos_x][pos_y] == 0) {
                q.push(make_pair(pii(-dist-1, direction-1), pii(pos_x, pos_y)));
            }
            if (visited[direction+1][pos_x][pos_y] == 0) {
                q.push(make_pair(pii(-dist-1, direction+1), pii(pos_x, pos_y)));
            }
        }
    }
    cout << -1 << endl;
}
