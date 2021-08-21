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
ll expo (ll start, ll pow) {
    if (pow == 0) {
        return 1;
    }
    if (pow == 1) {
        return start % mod;
    }
    ll ans = (expo(start, pow/2)*expo(start, pow/2))%mod;
    if (pow % 2 == 0) {
        return ans;
    }
    else {
        return (ans*start)%mod;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    ll n; cin >> n;
    cout << (expo(2, n) + 1) % mod << endl;
}