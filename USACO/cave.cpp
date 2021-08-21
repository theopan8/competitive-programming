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
typedef pair<ll, ll> pii;
#define MAXN 1010
#define MOD 1000000007
char grid[MAXN][MAXN];
int p[MAXN * MAXN];
ll size[MAXN * MAXN];
int n, m;
set<int> curr;
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
        p[x] = y;
    }
}
int toInt(int i, int j) {
    return i * m + j + 1;
}
ll pow(int y) {
    ll ans = 1;
    for(int i = 0; i < y; i++) {
        ans = (ans + ans) % MOD;
    }
    return ans;
}
int main() {
    freopen("cave.in", "r", stdin);
    freopen("cave.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                p[toInt(i, j)] = toInt(i, j);
                size[toInt(i, j)] = (ll)2;
            }
        }
    }
    ll total = 1;
    for(int i = n - 2; i >= 1; i--) {
        for(int j = 1; j < m - 1; j++) {
            if (grid[i][j] == '.' && grid[i][j - 1] == '.') unionSet(toInt(i, j), toInt(i, j - 1));
        }
        set<int> prev;
        for(int j = 1; j < m - 1; j++) {
            if (grid[i][j] == '.') {
                int x = prev.size();
                prev.insert(findSet(toInt(i, j)));
                if (x != prev.size()) curr.insert(findSet(toInt(i, j)));
                if (grid[i+1][j] == '.' && findSet(toInt(i + 1, j)) != findSet(toInt(i, j))) {
                    if ((findSet(toInt(i + 1, j)) - 1) / m > i) size[findSet(toInt(i, j))] = (((size[findSet(toInt(i, j))] - 1 + MOD) % MOD) * size[findSet(toInt(i + 1, j))] + 1) % MOD;
                    else size[findSet(toInt(i, j))] = (((size[findSet(toInt(i, j))] - 1 + MOD) % MOD) * ((size[findSet(toInt(i + 1, j))] - 1 + MOD) % MOD) + 1) % MOD;
                    curr.erase(findSet(toInt(i + 1, j)));
                    unionSet(findSet(toInt(i + 1, j)), findSet(toInt(i, j)));
                }
            }
        }
        /*for(auto j = curr.begin(); j != curr.end(); j++) {
            cout << size[*j] << endl;
        }
        cout << "....." << endl;*/
    }
    for(auto i = curr.begin(); i != curr.end(); i++) {
        total = (total * size[findSet(*i)]) % MOD;
    }
    cout << total << endl;
}