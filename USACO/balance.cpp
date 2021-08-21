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
#define point pair<long long, long long>
#define ll long long
#define ld long double
const int maxn = 100010;
vector<point> points;
vector<point> hull;
ll lefter[maxn];
ll righter[maxn];
ll cross(point o, point b, point a) {
    return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    int n; cin >> n;
    points.push_back(point(0, 0));
    for(int i = 1; i <= n; i++) {
        ll f; cin >> f;
        points.push_back(point(i,f));
    }
    points.push_back(point(n + 1, 0));
    sort(points.begin(), points.end());
    int k = 0;
    for(int i = 0; i < n + 1; i++) {
        while (k >= 2 && cross(hull[k-2], hull[k-1], points[i]) <= 0) {
            k -= 1;
            hull.pop_back();
        }
        k += 1;
        hull.push_back(points[i]);
    }
    int curr = 1;
    for(int i = 0; i < hull.size() - 1; i++) {
        while (hull[i].first <= curr && curr <= hull[i + 1].first && curr <= n) {
            if (hull[i].first == curr) {
                lefter[curr] = i;
                righter[curr] = i;
            }
            else if (hull[i + 1].first == curr) {
                lefter[curr] = i + 1;
                righter[curr] = i + 1;
            }
            else {
                lefter[curr] = i;
                righter[curr] = i + 1;
            }
            curr++;
        }
    }
    for(int i = 1; i <= n; i++) {
        if (lefter[i] == righter[i]) {
            cout << (ll)100000*hull[lefter[i]].second << endl;
        }
        else {
            cout << (ll)((ld)100000*hull[lefter[i]].second + (ld)100000*(i - hull[lefter[i]].first)*(hull[righter[i]].second - hull[lefter[i]].second)/(ld)(hull[righter[i]].first - hull[lefter[i]].first)) << endl;
        }
    }
}