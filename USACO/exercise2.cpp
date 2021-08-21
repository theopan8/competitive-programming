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
typedef __uint128_t L;
#define MAXN 7510
ll MOD;
struct FastMod {
    ll b, m;
    FastMod(ll b) : b(b), m(ll((L(1) << 64) / b)) {}
    ll reduce(ll a) {
        ll q = (ll)((L(m) * a) >> 64);
        ll r = a - q * b;
        return r >= b ? r - b : r;
    }
};
FastMod F1(2);
FastMod F2(2);
ll poww(ll x, ll y) {
    if (y == 0) return (ll)1;
    if (y == 1) return x;
    ll z = poww(x, y / (ll)2);
    if (y % 2 == 0) return F2.reduce(z * z);
    else return F2.reduce(F2.reduce(z * z) * x);
}
ll CPNP[MAXN];
ll CPNPall[MAXN];
ll CPNPmult[MAXN];
ll factorial[MAXN];
ll rangefac[MAXN][MAXN];
ll inv[MAXN];
int sieves[MAXN];
vector<ll> primes;
int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    ll n; cin >> n >> MOD;
    F1 = FastMod(MOD - (ll)1);
    F2 = FastMod(MOD);
    factorial[0] = 1;
    inv[0] = 1;
    for(ll i = 1; i <= n; i++) {
        factorial[i] = F1.reduce(factorial[i - 1] * i);
    }
    for(ll i = 0; i <= n; i++) {
        rangefac[i][i] = 1;
        for(ll j = i + 1; j <= n; j++)
            rangefac[j][i] = F1.reduce(rangefac[j - 1][i] * j);
    }
    for(int i = 2; i <= n; i++) {
        if (sieves[i] == 0) {
            primes.push_back(i);
            for(int j = 2 * i; j <= n; j += i)
                sieves[j] = 1;
        }
    }
    ll ans = 1;
    for(ll p : primes) {
        ll curr = p;
        while(curr <= n) {
            CPNPall[0] = 1;
            CPNPmult[0] = 0;
            CPNP[0] = 1;
            for(ll i = 1; i <= n; i++) {
                CPNPall[i] = F1.reduce(CPNP[i - 1] + F1.reduce((i - 1) * CPNPall[i - 1]));
                if (i >= curr) CPNPmult[i] = F1.reduce(rangefac[i - 1][i - curr] * CPNP[i - curr]);
                if (i > curr) CPNPmult[i] = F1.reduce(CPNPmult[i] + F1.reduce(rangefac[i - 1][i - curr - 1] * CPNPmult[i - curr]));
                CPNP[i] = F1.reduce(F1.reduce(CPNPall[i] - CPNPmult[i]) + MOD - (ll)1);
            }
            ll exp = F1.reduce(F1.reduce(factorial[n] - CPNP[n]) + MOD - (ll)1);
            ans = F2.reduce(ans * poww(p, exp));
            memset(CPNP, 0, sizeof(CPNP));
            memset(CPNPmult, 0, sizeof(CPNPmult));
            memset(CPNPall, 0, sizeof(CPNPall));
            //cout << curr << " " << exp << endl;
            curr *= p;
        }
    }
    cout << ans << endl;
}