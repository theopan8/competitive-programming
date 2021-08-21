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
#define int long long
priority_queue<int> q;
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        q.push(-x);
    }
    int total = 0;
    while (q.size() > 1) {
        int x = q.top();
        q.pop();
        int y = q.top();
        q.pop();
        total += (x+y);
        q.push(x+y);
    }
    cout << -total << endl;
}