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
#define mod 1000000007
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    ll total = 1;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        total *= x;
    }
    ll sum = 0;
    for(ll i = 1; i <= round(sqrt(total)); i++) {
        if (i*i == total) {
            sum = (sum + i) % mod;
        }
        if (total % i == 0) {
            sum = (sum + i) % mod;
            sum = (sum + (total/i)) % mod;
        }
    }
    cout << sum << endl;
}
