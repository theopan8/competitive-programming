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
using namespace std;
#define ll long long
int cows[3000005];
int main() {
    freopen("empty.in", "r", stdin);
    freopen("empty.out", "w", stdout);
    int n, k; cin >> n >> k;
    for(int i = 0; i < k; i++) {
        ll x, y, a, b; cin >> x >> y >> a >> b;
        for(int i = 1; i <= y; i++) {
            cows[(a*i + b)%n] += x;
        }
    }
    for(int i = 0; i < n-1; i++) {
        if (cows[i] == 0 || cows[i] == 1) {
            continue;
        }
        cows[i+1] += cows[i]-1;
        cows[i] = 1;
    }
    if (cows[n-1] <= 1) {
        for(int i = 0; i < n; i++) {
            if (cows[i] == 0) {
                cout << i << endl;
                break;
            }
        }
    }
    else {
        int target = cows[n-1]-1;
        int curr_total = 0;
        for(int i = 0; i < n; i++) {
            if (cows[i] == 0) {
                curr_total += 1;
                if (curr_total == target + 1) {
                    cout << i << endl;
                    break;
                }
                continue;
            }
        }
    }
}
