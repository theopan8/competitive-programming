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
#include <limits>
using namespace std;
#define maxn 100010
int parents[maxn];
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        parents[i] = i+x;
    }
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        if (x == 1) {
            int a; cin >> a;
            int ans = 0;
            while (true) {
                ans += 1;
                if (parents[a] > n) {
                    break;
                }
                a = parents[a];
            }
            cout << a << " " << ans << endl;
        }
        else {
            int a, b; cin >> a >> b;
            parents[a] = a+b;
        }
    }
}
