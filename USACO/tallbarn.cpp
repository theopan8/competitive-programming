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
#define ll long long
vector<ll> work;
ll numCows (double minIncr) {
    ll ans = 0;
    for(int i = 0; i < work.size(); i++) {
        ans += (ll)((sqrt(1 + 4*work[i]/minIncr)-1)/2);
    }
    return ans;
}

int main() {
    freopen("tallbarn.in", "r", stdin);
    freopen("tallbarn.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    ll n, k;
    cin >> n >> k;
    k -= n;
    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        work.push_back(a);
    }
    double low = 0;
    double high = pow(10, 18);
    for(int i = 0; i < 200; i++) {
        double avg = (low + high) / 2;
        if (numCows(avg) >= k) {
            low = avg;
        }
        else {
            high = avg;
        }
    }
    double answer = 0;
    ll total = 0;
    for(int i = 0; i < work.size(); i++) {
        total += (ll)((sqrt(1 + 4*work[i]/low)-1)/2);
        answer += 1.0 * work[i] / (ll)(((sqrt(1 + 4*work[i]/low)-1)/2) + 1);
    }
    cout << (ll)round(answer - (k - total)*low) << endl;
}