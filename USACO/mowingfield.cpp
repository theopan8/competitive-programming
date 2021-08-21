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
#define MAXN 100010
struct coord {
    int t; ll x1, x2, x3;
};
struct event {
    ll x; int e; coord type; int t;
    bool operator <(const event &other) const {
        return this->x < other.x || (this->x == other.x && this->e < other.e);
    }
};
vector<pii> points;
vector<coord> xs;
vector<coord> ys;
vector<event> events;
vector<ll> Ys[MAXN];
vector<ll> bit[MAXN + 10];
int n;
void preOp(int x, int y) {
    for (int i = x; i > 0; i -= i & -i) {
        Ys[i].push_back(y);
    }
}
void interProcessing() {
    for (int i = 1; i <= n; i++) {
        sort(Ys[i].begin(), Ys[i].end());
        bit[i].resize(1 + Ys[i].size());
    }
}
int query(int x, int y) {
    int answer = 0;
    for (int i = x; i > 0; i -= i & -i) {
        int normalizedY = lower_bound(Ys[i].begin(), Ys[i].end(), y) - Ys[i].begin();
        for (int j = normalizedY + 1; j > 0; j -= j & -j) {
            answer += bit[i][j];
        }
    }
    return answer;
}
void update(int x, int y, int addValue) {
    for (int i = x; i <= MAXN - 1; i += i & -i) {
        int normalizedY = lower_bound(Ys[i].begin(), Ys[i].end(), y) - Ys[i].begin();
        for (int j = normalizedY + 1; j < bit[i].size(); j += j & -j) {
            bit[i][j] += addValue;
        }
    }
}
int main() {
    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int T; cin >> n >> T;
    for(int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        points.push_back(pii(x + 1, y + 1));
    }
    for(int i = 0; i < n - 1; i++) {
        if (points[i].first == points[i + 1].first) xs.push_back(coord{i + 1, points[i].first, min(points[i].second, points[i + 1].second), max(points[i].second, points[i + 1].second)});
        else ys.push_back(coord{i + 1, points[i].second, min(points[i].first, points[i + 1].first), max(points[i].first, points[i + 1].first)});
    }
    for(coord i : ys) {
        if (i.x2 + 1 <= i.x3 - 1) {
            events.push_back(event{i.x2 + 1, 0, i, i.t});
            events.push_back(event{i.x3 - 1, 2, i, i.t});
        }
    }
    for(coord i : xs) {
        events.push_back(event{i.x1, 1, i, i.t});
    }
    sort(events.begin(), events.end());
    for(event i : events) {
        if (i.e == 0) {
            preOp(i.t, i.type.x1);
        }
        if (i.e == 1) {
            preOp(i.t - T, i.type.x3 - 1);
            preOp(i.t - T, i.type.x2);
            preOp(n, i.type.x3 - 1);
            preOp(n, i.type.x2);
            preOp(min(i.t + T - 1, n), i.type.x3 - 1);
            preOp(min(i.t + T - 1, n), i.type.x2);
        }
    }
    interProcessing();
    ll ans = 0;
    for(event i : events) {
        if (i.e == 0) {
            update(i.t, i.type.x1, 1);
        }
        if (i.e == 1) {
            if (i.type.x2 + 1 <= i.type.x3 - 1) {
                if (i.t > T) ans += query(i.t - T, i.type.x3 - 1) - query(i.t - T, i.type.x2);
                //cout << i.t + T << " " << MAXN - 1 << " " << i.type.x2 - 1 << " " << i.type.x3 << endl;
                ans += query(n, i.type.x3 - 1) - query(n, i.type.x2) - query(min(i.t + T - 1, n), i.type.x3 - 1) + query(min(i.t + T - 1, n), i.type.x2);
            }
        }
        if (i.e == 2) {
            update(i.t, i.type.x1, -1);
        }
    }
    cout << ans << endl;
}