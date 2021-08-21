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
#define MAXN 200010
#define MOD 1000000007
vector<pii> interv;
int n, k;
int range[MAXN];
ll ans = 0;
ll power(ll x) {
    ll ans = 1;
    for(int i = 0; i < k; i++) {
        ans = (ans * x) % MOD;
    }
    return ans;
}
void solve(int x) {
    for(int i = interv[x].first; i <= interv[x].second; i++) {
        range[i]++;
    }
    if (x == n - 1) {
        ll final = 0;
        int curr = 0;
        for(int i = 1; i <= 2 * n; i++) {
            if (range[i] > 0 && curr == 0) {
                final++;
                curr = 1;
            }
            if (range[i] == 0) curr = 0;
        }
        ans = (ans + power(final)) % MOD;
    }
    else {
        solve(x + 1);
    }
    for(int i = interv[x].first; i <= interv[x].second; i++) {
        range[i]--;
    }
    if (x == n - 1) {
        ll final = 0;
        int curr = 0;
        for(int i = 1; i <= 2 * n; i++) {
            if (range[i] > 0 && curr == 0) {
                final++;
                curr = 1;
            }
            if (range[i] == 0) curr = 0;
        }
        ans = (ans + power(final)) % MOD;
    }
    else {
        solve(x + 1);
    }
}
int main() {
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        interv.push_back(pii(l, r - 1));
    }
    solve(0);
    cout << ans << endl;
}