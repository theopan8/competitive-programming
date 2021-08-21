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
#define MaxVal 200010
int tree[MaxVal];

int read(int idx){
    int sum = 0;
    while (idx > 0){
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int idx ,int val){
    while (idx <= MaxVal){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}
int main() {
    //freopen("runaway.in", "r", stdin);
    //freopen("runaway.out", "w", stdout);
    int n, x; cin >> n >> x;
    ll curr_total = 0;
    update(curr_total+n+1, 1);
    ll total = 0;
    for(int i = 0; i < n; i++) {
        ll h; cin >> h;
        if (h >= x) {
            curr_total += 1;
        }
        else {
            curr_total -= 1;
        }
        total += read(curr_total+n+1);
        update(curr_total+n+1, 1);
    }
    cout << total << endl;
}
