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
#define maxn 100005
#define ll long long
#define pii pair<int,int>
ll st[maxn << 2];
ll lazy[maxn << 2];
vector<pii> cows;
bool comp (pii i, pii j) {
    if (i.second < j.second) {
        return true;
    }
    else if (j.second < i.second) {
        return false;
    }
    else {
        if (i.first > j.first) {
            return true;
        }
        else {
            return false;
        }
    }
}
int left (int p) {
    return (p << 1);
}
int right (int p) {
    return (p << 1) + 1;
}
void push (int p, int L, int R) {
    st[p] += (lazy[p]);
    if (L != R) {
        lazy[left(p)] += lazy[p];
        lazy[right(p)] += lazy[p];
    }
    lazy[p] = 0;
}
void update (int p, int L, int R, int i, int j, int val) {
    push(p, L, R);
    if (i > R || j < L) {
        return;
    }
    if (L >= i && R <= j) {
        lazy[p] = val;
        push(p, L, R);
        return;
    }
    update(left(p), L, (L+R)/2, i, j, val);
    update(right(p), (L+R)/2 + 1, R, i, j, val);
    st[p] = min(st[left(p)],st[right(p)]);
}
ll query (int p, int L, int R, int i, int j) {
    push(p, L, R);
    if (i > R || j < L) {
        return -1;
    }
    if (L >= i && R <= j) {
        return st[p];
    }
    int x = query(left(p), L, (L+R)/2, i, j);
    int y = query(right(p), (L+R)/2 + 1, R, i, j);
    if (x == -1) {
        return y;
    }
    if (y == -1) {
        return x;
    }
    return min(x,y);
}
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n , m; cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int c; cin >> c;
        update(1, 1, n, i+1, i+1, c);
    }
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        cows.push_back(pii(a,b));
    }
    sort(cows.begin(), cows.end(), comp);
    int total = 0;
    for(int i = 0; i < cows.size(); i++) {
        if (query(1, 1, n, cows[i].first, cows[i].second) <= 0) {
            continue;
        }
        update(1, 1, n, cows[i].first, cows[i].second, -1);
        total += 1;
    }
    cout << total << endl;
}
