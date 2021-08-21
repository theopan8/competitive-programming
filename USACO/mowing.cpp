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
using namespace std;
#define ll long long
const int maxn = 200010;
struct pii {
    int x, y;
    bool operator < (const pii &other) const {
        return this->x > other.x;
    }
};
vector<pii> flowers;
ll dp[maxn];
int depth[maxn];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);
    int n, t; cin >> n >> t;
    flowers.push_back(pii{t, t});
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        flowers.push_back(pii{x,y});
    }
    flowers.push_back(pii{0, 0});
    sort(flowers.begin(), flowers.end());
    int maxDepth = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            if (flowers[i].y < flowers[j].y) {
                depth[i] = max(depth[i], depth[j] + 1);
            }
        }
        maxDepth = max(maxDepth, depth[i]);
    }
    depth[n + 1] = maxDepth + 1;
    for(int i = 1; i <= n + 1; i++) {
        for(int j = 0; j < i; j++) {
            if (flowers[i].y < flowers[j].y && depth[i] == depth[j] + 1) {
                if (dp[i] == 0 || dp[i] > dp[j] + (flowers[j].x - flowers[i].x) * (flowers[j].y - flowers[i].y)) {
                    dp[i] = dp[j] + (flowers[j].x - flowers[i].x) * (flowers[j].y - flowers[i].y);
                }
            }
        }
    }
    /*for(int i = 0; i <= n + 1; i++) {
        cout << "Point: " << flowers[i].x << " " << flowers[i].y << endl;
        cout << dp[i] << endl;
    }*/
    cout << dp[n + 1] << endl;
}