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
#define maxn 50005
#define maxk 17
vector<int> heights;
int rmq[maxn][maxk];
int rmq2[maxn][maxk];

int _rmq_ (int i, int j) {
    if (i == j) {
        return heights[i];
    }
    int a = i;
    int b = j;
    int value = 0;
    for(int k = maxk-1; k >= 0; k--) {
        if (a == b + 1) {
            break;
        }
        if (a + (1 << k) - 1 <= b) {
            value = max(value, rmq[a][k]);
            //cout << "power: " << k << " value: " << value << endl;
            a += (1 << k);
        }
    }
    return value;
}
int _rmq_2 (int i, int j) {
    if (i == j) {
        return heights[i];
    }
    int a = i;
    int b = j;
    int value = 1000005;
    for(int k = maxk-1; k >= 0; k--) {
        if (a == b+1) {
            break;
        }
        if (a + (1 << k) - 1 <= b) {
            value = min(value, rmq2[a][k]);
            //cout << "power: " << k << " value: " << value << endl;
            a += (1 << k);
        }
    }
    return value;
}

int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++) {
        int h; cin >> h;
        heights.push_back(h);
    }
    for(int i = 0; i < maxk; i++) {
        for(int j = 0; j < n; j++) {
            if (i == 0) {
                rmq[j][i] = heights[j];
                rmq2[j][i] = heights[j];
                continue;
            }
            if (j + (1<< (i-1)) < n) {
                rmq[j][i] = max(rmq[j][i-1], rmq[j+(1 << (i-1))][i-1]);
                rmq2[j][i] = min(rmq2[j][i-1], rmq2[j+(1 << (i-1))][i-1]);
            }
        }
    }
    //int x = _rmq_(0, 4);
    //int x = _rmq_2(0,4);
    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        cout << _rmq_(x-1, y-1) - _rmq_2(x-1, y-1) << endl;
        //cout << x << " " << y << endl;
        //cout << "min: " << _rmq_2(x-1,y-1) << endl;
        //cout << "max: " << _rmq_(x-1,y-1) << endl;
    }
}
