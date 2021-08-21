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
#include <cstring>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, int> pip;
#define MAXN 1000010
vector<pii> points;
int bit[MAXN];
int bit1[MAXN];
int query(int idx){
    int sum = 0;
    while (idx > 0){
        sum += bit[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
void update(int idx, int val){
    while (idx < MAXN){
        bit[idx] += val;
        idx += (idx & -idx);
    }
}
int query1(int idx){
    int sum = 0;
    while (idx > 0){
        sum += bit1[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
void update1(int idx, int val){
    while (idx < MAXN){
        bit1[idx] += val;
        idx += (idx & -idx);
    }
}
int main() {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.push_back(pii(x, y));
    }
    sort(points.begin(), points.end());
    for(pii p : points) {
        update1(p.second, 1);
    }
    int ans = n;
    for(pii p : points) {
        update1(p.second, -1);
        update(p.second, 1);
        int low = 0;
        int high = 1000000;
        while (low < high - 1) {
            int avg = (low + high) / 2;
            int down = max(query(avg), query1(avg));
            int up = max(query(1000000) - query(avg), query1(1000000) - query1(avg));
            ans = min(ans, max(down, up));
            if (down <= up) {
                low = avg;
            }
            else {
                high = avg;
            }
        }
        int down = max(query(low), query1(low));
        int up = max(query(1000000) - query(low), query1(1000000) - query1(low));
        ans = min(ans, max(down, up));
    }
    cout << ans << endl;
}