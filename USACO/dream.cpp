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
#include <limits>
using namespace std;
#define pii pair<int, int>
const int maxn = 1001;
int grid[maxn][maxn];
pii directions[4] = {pii(-1, 0), pii(0, 1), pii(1, 0), pii(0, -1)}; //N E S W
struct State {
    int x, y, ifOrange, dir, currDist;
};
int dp[2][4][maxn][maxn];
int main() {
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    queue<State> q;
    State start1 = State{0, 0, 0, 1, 1};
    State start2 = State{0, 0, 0, 2, 1};
    q.push(start1); q.push(start2);
    while (!q.empty()) {
        State onTop = q.front();
        q.pop();
        if (dp[onTop.ifOrange][onTop.dir][onTop.x][onTop.y] != 0) {
            continue;
        }
        //cout << onTop.x << " " << onTop.y << " " << onTop.ifOrange << " " << onTop.dir << " " << onTop.currDist << endl;
        dp[onTop.ifOrange][onTop.dir][onTop.x][onTop.y] = onTop.currDist;
        if (grid[onTop.x][onTop.y] == 4) {
            if (!(onTop.x + directions[onTop.dir].first < 0 || onTop.x + directions[onTop.dir].first >= n || onTop.y + directions[onTop.dir].second < 0 || onTop.y + directions[onTop.dir].second >= m)) {
                int newx = onTop.x + directions[onTop.dir].first;
                int newy = onTop.y + directions[onTop.dir].second;
                if (grid[newx][newy] != 0 && grid[newx][newy] != 3) {
                    if (dp[0][onTop.dir][newx][newy] == 0) {
                        State newState = State{newx, newy, 0, onTop.dir, onTop.currDist + 1};
                        q.push(newState);
                        continue;
                    }
                }
            }
            for(int i = 0; i < 4; i++) {
                if (i == onTop.dir) {
                    continue;
                }
                if (!(onTop.x + directions[i].first < 0 || onTop.x + directions[i].first >= n || onTop.y + directions[i].second < 0 || onTop.y + directions[i].second >= m)) {
                    int newx = onTop.x + directions[i].first;
                    int newy = onTop.y + directions[i].second;
                    if (grid[newx][newy] != 0 && (grid[newx][newy] != 3)) {
                        if (dp[onTop.ifOrange][i][newx][newy] == 0) {
                            State newState = State{newx, newy, 0, i, onTop.currDist + 1};
                            q.push(newState);
                        }
                    }
                }
            }
        }
        else {
            for(int i = 0; i < 4; i++) {
                if (!(onTop.x + directions[i].first < 0 || onTop.x + directions[i].first >= n || onTop.y + directions[i].second < 0 || onTop.y + directions[i].second >= m)) {
                    int newx = onTop.x + directions[i].first;
                    int newy = onTop.y + directions[i].second;
                    if (grid[newx][newy] != 0 && (grid[newx][newy] != 3 || onTop.ifOrange == 1 || grid[onTop.x][onTop.y] == 2)) {
                        if (grid[onTop.x][onTop.y] == 2) {
                            if (dp[1][i][newx][newy] == 0) {
                                State newState = State{newx, newy, 1, i, onTop.currDist + 1};
                                q.push(newState);
                            }
                        }
                        else {
                            if (dp[onTop.ifOrange][i][newx][newy] == 0) {
                                State newState = State{newx, newy, onTop.ifOrange, i, onTop.currDist + 1};
                                q.push(newState);
                            }
                        }
                    }
                }
            }
        }
    }
    int minAns = -1;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 2; j++) {
            if (dp[j][i][n-1][m-1] != 0) {
                if (minAns == -1) {
                    minAns = dp[j][i][n-1][m-1] - 1;
                }
                else {
                    minAns = min(minAns, dp[j][i][n-1][m-1] - 1);
                }
            }
        }
    }
    cout << minAns << endl;
}