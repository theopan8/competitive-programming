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
typedef long long ll;
typedef pair<int, int> pii;
#define MAXN 610
int grid[MAXN][MAXN];
vector<pii> cows;
int pre1[MAXN][MAXN];
int pre2[MAXN][MAXN];
int main() {
    //freopen("triangles.in", "r", stdin);
    //freopen("triangles.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            char c; cin >> c;
            if(c == '*') {
                grid[i][j] = 1;
                cows.push_back(pii(i, j));
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            pre1[i][j] = pre1[i - 1][j - 1] + grid[i][j];
            pre2[i][j] = pre2[i - 1][j + 1] + grid[i][j];
        }
    }
    int ans = 0;
    for(int i = 0; i < cows.size(); i++) {
        for(int j = i + 1; j < cows.size(); j++) {
            int x1 = cows[i].first;
            int y1 = cows[i].second;
            int x2 = cows[j].first;
            int y2 = cows[j].second;
            int dist = abs(x1 - x2) + abs(y1 - y2);
            if(x2 == x1 + dist/2 && y2 == y1 + dist/2) {
                ans += pre1[min(n, x1 + dist)][y1] - pre1[min(n, max(0, x1 + dist/2 - 1))][max(0, y1 - dist/2 - 1)];
                ans += pre1[x1][min(n, y1 + dist)] - pre1[max(0, x1 - dist/2 - 1)][min(n, max(0, y1 + dist/2 - 1))];
            }
            else if(x2 == x1 + dist/2 && y2 == y1 - dist/2) {
                ans += pre2[x1][max(0, y1 - dist)] - pre2[max(0, x1 - dist/2 - 1)][min(n, max(0, y1 - dist/2 + 1))];
                ans += pre2[min(n, x1 + dist)][y1] - pre2[min(n, max(0, x1 + dist/2 - 1))][min(n, y1 + dist/2 + 1)];
            }
            else if(x2 == x1 - dist/2 && y2 == y1 + dist/2) {
                ans += pre2[max(0, x1 - dist/2)][max(0, y1 - dist/2)] - pre2[max(0, x1 - dist - 1)][min(n, y1 + 1)];
                ans += pre2[min(n, x1 + dist/2)][min(n, y1 + dist/2)] - pre2[max(0, x1 - 1)][min(n, y1 + dist + 1)];
            }
            else if(x2 == x1 - dist/2 && y2 == y1 - dist/2) {
                ans += pre1[min(n, x1 + dist/2)][max(0, y1 - dist/2)] - pre1[max(0, x1 - 1)][max(0, y1 - dist - 1)];
                ans += pre1[max(0, x1 - dist/2)][min(n, y1 + dist/2)] - pre1[max(0, x1 - dist - 1)][max(0, y1 - 1)];
            }
            else {
                if()
            }
    }
}