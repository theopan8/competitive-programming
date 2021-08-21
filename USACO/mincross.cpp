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
#define MaxVal 100010
#define int long long
int tree[MaxVal];
int value[MaxVal];
int value2[MaxVal];
vector<int> first;
vector<int> sec;
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
main() {
    //freopen("mincross.in", "r", stdin);
    //freopen("mincross.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = n; i >= 1; i--) {
        int x; cin >> x;
        value[x] = i;
        first.push_back(x);
    }
    int total = 0;
    for(int i = n; i >= 1; i--) {
        int x; cin >> x;
        value2[x] = i;
        sec.push_back(x);
        total += read(value[x]);
        update(value[x], 1);
    }
    int ans = total;
    for(int i = 0; i < n; i++) {
        total -= n - value[sec[i]];
        total += value[sec[i]] - 1;
        if (total < ans) {
            ans = total;
        }
    }
    for(int i = 0; i < n; i++) {
        total -= n - value2[first[i]];
        total += value2[first[i]] - 1;
        if (total < ans) {
            ans = total;
        }
    }
    cout << ans << endl;
}