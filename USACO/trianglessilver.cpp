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
#define MAXN 100010
#define MOD 1000000007
map<int, vector<int> > xs;
map<int, vector<int> > ys;
map<int, vector<int> > xsums;
map<int, vector<int> > ysums;
vector<pii> points;
int main() {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.push_back(pii(x, y));
        xs[x].push_back(y);
        ys[y].push_back(x);
    }
    for(auto i = xs.begin(); i != xs.end(); i++) {
        sort((i->second).begin(), (i->second).end());
        xsums[i->first].push_back(0);
        for(int j = 0; j < xs[i->first].size(); j++) {
            xsums[i->first].push_back(xsums[i->first][j] + xs[i->first][j]);
        }
    }
    for(auto i = ys.begin(); i != ys.end(); i++) {
        sort((i->second).begin(), (i->second).end());
        ysums[i->first].push_back(0);
        for(int j = 0; j < ys[i->first].size(); j++) {
            ysums[i->first].push_back(ysums[i->first][j] + ys[i->first][j]);
        }
    }
    ll total = 0;
    for(pii p : points) {
        if (xs[p.first].size() == 1 || ys[p.second].size() == 1) continue;
        int x = lower_bound(ys[p.second].begin(), ys[p.second].end(), p.first) - ys[p.second].begin();
        int y = lower_bound(xs[p.first].begin(), xs[p.first].end(), p.second) - xs[p.first].begin();
        x++; y++;
        ll ansx = ((p.first * x - ysums[p.second][x]) + (ysums[p.second][ysums[p.second].size() - 1] - ysums[p.second][x] - p.first * (ysums[p.second].size() - 1 - x))) % MOD;
        ll ansy = ((p.second * y - xsums[p.first][y]) + (xsums[p.first][xsums[p.first].size() - 1] - xsums[p.first][y] - p.second * (xsums[p.first].size() - 1 - y))) % MOD;
        //cout << ansx << " " << ansy << endl;
        total = (total + ansx * ansy) % MOD;
    }
    cout << total << endl;
}