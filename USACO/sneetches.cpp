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
#include <limits>
using namespace std;
#define maxn 100005
#define ll long long
//left P, left S, max len total P, right P, right S, max len total S
ll st[7][maxn << 2];
ll lazy[maxn << 2];
int left (int p) {
    return (p << 1);
}
int right (int p) {
    return (p << 1) + 1;
}
void build (int p, int L, int R) {
    if (L == R) {
        st[0][p] = 1;
        st[1][p] = 0;
        st[2][p] = 1;
        st[3][p] = 1;
        st[4][p] = 0;
        st[5][p] = 0;
    }
    else {
        st[0][p] = (R-L+1);
        st[1][p] = 0;
        st[2][p] = (R-L+1);
        st[3][p] = (R-L+1);
        st[4][p] = 0;
        st[5][p] = 0;
        build(left(p), L, (L+R)/2);
        build(right(p), (L+R)/2 + 1, R);
    }
}
void push (int p, int L, int R) {
    if (lazy[p] % 2 != 0) {
        ll uno, dos, tres, cuatro, cinco, seis;
        uno = st[0][p];
        dos = st[1][p];
        tres = st[2][p];
        cuatro = st[3][p];
        cinco = st[4][p];
        seis = st[5][p];
        st[0][p] = dos;
        st[1][p] = uno;
        st[2][p] = seis;
        st[3][p] = cinco;
        st[4][p] = cuatro;
        st[5][p] = tres;
    }
    if (L != R) {
        lazy[left(p)] += lazy[p];
        lazy[right(p)] += lazy[p];
    }
    lazy[p] = 0;
}
void update (int p, int L, int R, int i, int j, int val) {
    push(p, L, R);
    if (i > R || j < L) {
        //cout << p << " " << st[5][p] << " " << st[2][p] << endl;
        //cout << st[0][p] << " " << st[1][p] << " " << st[3][p] << " " << st[4][p] << endl;
        return;
    }
    if (L >= i && R <= j) {
        lazy[p] += val;
        push(p, L, R);
        //cout << p << " " << st[5][p] << " " << st[2][p] << endl;
        //cout << st[0][p] << " " << st[1][p] << " " << st[3][p] << " " << st[4][p] << endl;
        return;
    }
    update(left(p), L, (L+R)/2, i, j, val);
    update(right(p), (L+R)/2 + 1, R, i, j, val);
    st[0][p] = st[0][left(p)];
    if (st[0][left(p)] == (L+R)/2 - L + 1) {
        st[0][p] += st[0][right(p)];
    }
    st[1][p] = st[1][left(p)];
    if (st[1][left(p)] == (L+R)/2 - L + 1) {
        st[1][p] += st[1][right(p)];
    }
    st[2][p] = max(st[2][left(p)], max(st[2][right(p)], st[3][left(p)] + st[0][right(p)]));
    st[3][p] = st[3][right(p)];
    if (st[3][right(p)] == R - (L+R)/2) {
        st[3][p] += st[3][left(p)];
    }
    st[4][p] = st[4][right(p)];
    if (st[4][right(p)] == R - (L+R)/2) {
        st[4][p] += st[4][left(p)];
    }
    st[5][p] = max(st[5][left(p)], max(st[5][right(p)], st[4][left(p)] + st[1][right(p)]));
    //cout << p << " " << st[5][p] << " " << st[2][p] << endl;
    //cout << st[0][p] << " " << st[1][p] << " " << st[3][p] << " " << st[4][p] << endl;
    //st[p] = st[left(p)] + st[right(p)];
}
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, s; cin >> n >> s;
    build(1, 1, n);
    for(int i = 1; i <= n; i++) {
        char x; cin >> x;
        if (x == 'S') {
            update(1, 1, n, i, i, 1);
        }
    }
    for(int i = 0; i < s; i++) {
        int x, y; cin >> x >> y;
        update(1, 1, n, x, y, 1);
        push(1, 1, n);
        cout << st[5][1] << " " << st[2][1] << endl;
    }
}
/*        1
        2   3
       4 5  6 7*/
//SSSPPP
//SPPSPP