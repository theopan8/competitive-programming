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
#define maxn 100010
#define pii pair<int,int>
int p[maxn];
int r[maxn]; //size
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
        if (r[x] > r[y]) {
            p[y] = x;
            r[x] += r[y];
        }
        else {
            p[x] = y;
            r[y] += r[x];
        }
    }
}
vector<pii> points;
set<int> counter;
int main() {
    ios_base::sync_with_stdio(0);
    int n, c; cin >> n >> c;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.push_back(pii(x,y));
    }
    for(int i = 0; i < n; i++) {
        p[i] = i;
        r[i] = 1;
    }
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if (abs(points[i].first - points[j].first) + abs(points[i].second - points[j].second) <= c) {
                unionSet(i, j);
            }
        }
    }
    int max_r = 0;
    for(int i = 0; i < n; i++) {
        counter.insert(findSet(i));
        if (max_r < r[i]) {
            max_r = r[i];
        }
    }
    cout << counter.size() << " " << max_r << endl;
}