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
typedef pair<int, int> pii;
#define MAXN 50010
int temp[MAXN << 1];
vector<int> b;
vector<int> e;
int pre[MAXN];
int suf[MAXN];
int mapper[MAXN << 1];
set<int> curr;
set<int> curr1;
int main() {
    //freopen("cardgame.in", "r", stdin);
    //freopen("cardgame.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        temp[x] = 1;
        e.push_back(x);
    }
    int x = 0;
    for(int i = 1; i <= n; i++) {
        if (temp[i] == 0) {
            b.push_back(i);
            mapper[i] = x;
            x++;
        }
    }
    sort(b.begin(), b.end());
    for(int i = 0; i < n; i++) {
        if (b[i] > e[i]) {
            
        }
        curr.insert(b[i]);
        auto it = curr.lower_bound(e[i]);
        if (it == curr.end()) {
            continue;
        }

    }
}