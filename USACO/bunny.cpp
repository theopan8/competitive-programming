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
#define MaxVal 100010
#define ll long long
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
    ios_base::sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        ll a; cin >> a;
        update(i, (int)log2(a));
    }
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        if (x == 1) {
            ll y, z; cin >> y >> z;
            update(y, (int)log2(z));
        }
        else {
            int l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
            int first = read(r1) - read(l1-1);
            int second = read(r2) - read(l2-1);
            if (first > second) {
                cout << 1 << endl;
            }
            else if (first == second) {
                cout << 0 << endl;
            }
            else {
                cout << -1 << endl;
            }
        }
    }
}
