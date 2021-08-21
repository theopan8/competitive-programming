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
typedef long long ll;
typedef pair<int, int> pii;
#define MAXN 100010
int a[MAXN];
int b[MAXN];
int main() {
    //freopen("friendcross.in", "r", stdin);
    //freopen("friendcross.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[x] = i;
    }
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        b[x] = i;
    }

}