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
typedef long long ll;
typedef pair<int, int> pii;
#define MAXN 1010
int minX[MAXN * MAXN];
int minY[MAXN * MAXN];
int maxX[MAXN * MAXN];
int maxY[MAXN * MAXN];
int grid[MAXN][MAXN];
int prefix[MAXN][MAXN];
int canBeFirst[MAXN * MAXN];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);
    int n; cin >> n;
    for(int i = 1; i <= n * n; i++) {
        minX[i] = n + 1;
        minY[i] = n + 1;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 0) continue;
            minX[grid[i][j]] = min(minX[grid[i][j]], i);
            minY[grid[i][j]] = min(minY[grid[i][j]], j);
            maxX[grid[i][j]] = max(maxX[grid[i][j]], i);
            maxY[grid[i][j]] = max(maxY[grid[i][j]], j);
        }
    }
    int tot = 0;
    for(int i = 1; i <= n * n; i++) {
        if (maxX[i] != 0) {
            tot++;
            prefix[minX[i]][minY[i]]++;
            prefix[maxX[i] + 1][maxY[i] + 1]++;
            prefix[minX[i]][maxY[i] + 1]--;
            prefix[maxX[i] + 1][minY[i]]--;
        }
    }
    if (tot == 1) {
        cout << n * n - 1 << endl;
        return 0;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            prefix[i][j] += prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
            if (grid[i][j] == 0) continue;
            if (prefix[i][j] > 1) {
                canBeFirst[grid[i][j]] = 1;
            }
        }
    }
    int total = n * n;
    for(int i = 1; i <= n * n; i++) {
        total -= canBeFirst[i];
    }
    cout << total << endl;
}