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
#define dim 55
#define pii pair<int,int>
#define maxn 16
#define maxb 1 << 16
int grid[dim][dim];
int visited_island[dim][dim];
int islands[dim][dim];
pii squares_island[maxn];
int visited_dist[dim][dim];
int distances[maxn][maxn];
vector<pii> graph[maxn];
int dp[maxn][maxb];
void floodfill_island (pii start, int r, int c, int type) {
    queue<pii> q; q.push(start);
    squares_island[type] = start;
    while (!q.empty()) {
        pii pos = q.front();
        int x = pos.first;
        int y = pos.second;
        q.pop();
        if (visited_island[x][y] != 0) {
            continue;
        }
        visited_island[x][y] = 1;
        islands[x][y] = type;
        if (x > 0) {
            if (visited_island[x-1][y] == 0 && grid[x-1][y] == 2) {
                q.push(pii(x-1, y));
            }
        }
        if (y > 0) {
            if (visited_island[x][y-1] == 0 && grid[x][y-1] == 2) {
                q.push(pii(x, y-1));
            }
        }
        if (x < r-1) {
            if (visited_island[x+1][y] == 0 && grid[x+1][y] == 2) {
                q.push(pii(x+1, y));
            }
        }
        if (y < c-1) {
            if (visited_island[x][y+1] == 0 && grid[x][y+1] == 2) {
                q.push(pii(x, y+1));
            }
        }
    }
}
void floodfill_dist (pii start, int r, int c, int type) {
    queue<pair<int, pii> > q; q.push(make_pair(0, start));
    while (!q.empty()) {
        pair<int, pii> pos = q.front();
        q.pop();
        int dist = pos.first;
        int x = pos.second.first;
        int y = pos.second.second;
        if (visited_dist[x][y] == 1) {
            continue;
        }
        visited_dist[x][y] = 1;
        if (x > 0) {
            if (visited_dist[x-1][y] == 0) {
                if (grid[x-1][y] == 1) {
                    q.push(make_pair(dist+1, pii(x-1, y)));
                }
                else if (grid[x-1][y] == 2) {
                    if (islands[x-1][y] == type) {
                        q.push(make_pair(dist, pii(x-1, y)));
                    }
                    else {
                        q.push(make_pair(dist, pii(x-1, y)));
                        if (distances[type][islands[x-1][y]] == 0 || dist < distances[type][islands[x-1][y]]) {
                            distances[type][islands[x-1][y]] = dist;
                            distances[islands[x-1][y]][type] = dist;
                        }
                    }
                }
            }
        }
        if (y > 0) {
            if (visited_dist[x][y-1] == 0) {
                if (grid[x][y-1] == 1) {
                    q.push(make_pair(dist+1, pii(x, y-1)));
                }
                else if (grid[x][y-1] == 2) {
                    if (islands[x][y-1] == type) {
                        q.push(make_pair(dist, pii(x, y-1)));
                    }
                    else {
                        q.push(make_pair(dist, pii(x, y-1)));
                        if (distances[type][islands[x][y-1]] == 0 || dist < distances[type][islands[x][y-1]]) {
                            distances[type][islands[x][y-1]] = dist;
                            distances[islands[x][y-1]][type] = dist;
                        }
                    }
                }
            }
        }
        if (x < r-1) {
            if (visited_dist[x+1][y] == 0) {
                if (grid[x+1][y] == 1) {
                    q.push(make_pair(dist+1, pii(x+1, y)));
                }
                else if (grid[x+1][y] == 2) {
                    if (islands[x+1][y] == type) {
                        q.push(make_pair(dist, pii(x+1, y)));
                    }
                    else {
                        q.push(make_pair(dist, pii(x+1, y)));
                        if (distances[type][islands[x+1][y]] == 0 || dist < distances[type][islands[x+1][y]]) {
                            distances[type][islands[x+1][y]] = dist;
                            distances[islands[x+1][y]][type] = dist;
                        }
                    }
                }
            }
        }
        if (y < c-1) {
            if (visited_dist[x][y+1] == 0) {
                if (grid[x][y+1] == 1) {
                    q.push(make_pair(dist+1, pii(x, y+1)));
                }
                else if (grid[x][y+1] == 2) {
                    if (islands[x][y+1] == type) {
                        q.push(make_pair(dist, pii(x, y+1)));
                    }
                    else {
                        q.push(make_pair(dist, pii(x, y+1)));
                        if (distances[type][islands[x][y+1]] == 0 || dist < distances[type][islands[x][y+1]]) {
                            distances[type][islands[x][y+1]] = dist;
                            distances[islands[x][y+1]][type] = dist;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            visited_dist[i][j] = 0;
        }
    }
}
int main() {
    //This is solution is partially correct
    ios_base::sync_with_stdio(0);
    int r, c; cin >> r >> c;
    //set up the grid with islands, shallow water, and deep water
    //2 --> island, 1 --> shallow, 0 --> deep
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            char x; cin >> x;
            if (x == 'X') {
                grid[i][j] = 2;
            }
            else if (x == 'S') {
                grid[i][j] = 1;
            }
            else {
                grid[i][j] = 0;
            }
        }
    }
    //find the islands with flood fills
    int type = 1;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if (grid[i][j] == 2 && visited_island[i][j] == 0) {
                floodfill_island(pii(i,j), r, c, type);
                type += 1;
            }
        }
    }
    //find pairwise distances between islands using another flood fill
    //Note that type is actually 1 more than the number of islands
    for(int i = 1; i < type; i++) {
        floodfill_dist(squares_island[i], r, c, i);
    }
    for(int i = 1; i < type; i++) {
        for(int j = 1; j < type; j++) {
            if (i != j) {
                graph[i].push_back(pii(j, distances[i][j]));
            }
        }
    }
    for(int i = 0; i < 1 << (type-1); i++) {
        for(int j = 1; j < type; j++) {
            if (((i & (1 << (j-1))) == 0) || (__builtin_popcount(i) == 1)) {
                continue;
            }
            int min = -1;
            for(pii v: graph[j]) {
                if ((i & (1 << (v.first - 1))) == 0) {
                    continue;
                }
                if (dp[v.first][i & ~(1 << (j-1))] == 0 && (i & ~(1 << (j-1))) != 0 && __builtin_popcount((i & ~(1 << (j-1)))) != 1) {
                    continue;
                }
                if (min == -1) {
                    min = dp[v.first][i & ~(1 << (j-1))] + v.second;
                }
                else if (min > dp[v.first][i & ~(1 << (j-1))] + v.second) {
                    min = dp[v.first][i & ~(1 << (j-1))] + v.second;
                }
            }
            if (min == -1) {
                continue;
            }
            else {
                dp[j][i] = min;
            }
        }
    }
    int min = -1;
    for(int i = 1; i < type; i++) {
        //cout << dp[i][(1<<n) - 1] << endl;
        if (dp[i][(1 << (type-1))-1] == 0) {
            continue;
        }
        if (min == -1) {
            min = dp[i][(1 << (type - 1))-1];
        }
        else if (min > dp[i][(1 << (type - 1))-1]) {
            min = dp[i][(1 << (type-1))-1];
        }
    }
    if (min == -1) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << min << endl;
    }
}