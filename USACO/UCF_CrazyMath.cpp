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
#define mod 1000000000
int a, b;
map<int, int> mem;
ll fibonacci (ll n) {
    if (mem[n] != 0) {
        return mem[n];	
    }
    if (n == 1) {
        return a;
    }
    if (n == 2) {
        return b;
    }
    if (n == 3) {
        return a + b;
    }
    if (n % 2 == 0) {
        mem[n] = (fibonacci(n/2)*(2*fibonacci((n/2)+1) - fibonacci(n/2))) % mod;
        return mem[n];
    }
    else {
        mem[n] = (fibonacci(n/2 + 1)*fibonacci(n/2 + 1) + fibonacci(n/2)*fibonacci(n/2)) % mod;
        return mem[n];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    ll n;
    cin >> a >> b >> n;
    mem[1] = a;
    mem[2] = b;
    mem[3] = a+b;
    ll ans = fibonacci(n+1);
    if (ans < 0) {
        ans += mod;	
    }
    cout << ans << endl;
}