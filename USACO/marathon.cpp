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
#define pii pair<int,int>
#define ll long long
ll st[maxn << 2];
ll st2[maxn << 2];
ll values[maxn];
ll values1[maxn];
vector<pii> checkpoints;
//values is going to be indexed starting at 1
int left (int p) {
    return (p << 1);
}
int right (int p) {
    return (p << 1) + 1;
}
//build sum
void build (int p, int L, int R) {
    if (L == R) {
        st[p] = values[L];
    }
    else {
        build(left(p), L, (L+R)/2);
        build(right(p), (L+R)/2 + 1, R);
        st[p] = st[left(p)] + st[right(p)];
    }
}
ll rmq (int p, int L, int R, int i, int j) {
    if (i > R || j < L) {
        return -1;
    }
    if (L >= i && R <= j) {
        return st[p];
    }
    ll p1 = rmq(left(p), L, (L+R)/2, i , j);
    ll p2 = rmq(right(p), (L+R)/2 + 1, R, i, j);
    if (p1 == -1) {
        return p2;
    }
    if (p2 == -1) {
        return p1;
    }
    return p1 + p2;
}
void update (int p, int L, int R, int i, int val) {
    if (i < L || i > R) {
        return;
    }
    if (L == i && R == i) {
        st[p] += val;
        return;
    }
    st[p] += val;
    update(left(p), L, (L+R)/2, i, val);
    update(right(p), (L+R)/2 + 1, R, i, val);
    //st[p] = st[left(p)] + st[right(p)];
    //cout << L << " " << R << " " << st[p] << endl;
}
//build maximum
void build1 (int p, int L, int R) {
    if (L == R) {
        st2[p] = values1[L];
    }
    else {
        build1(left(p), L, (L+R)/2);
        build1(right(p), (L+R)/2 + 1, R);
        st2[p] = max(st2[left(p)], st2[right(p)]);
    }
}
ll maxq (int p, int L, int R, int i, int j) {
    if (i > R || j < L) {
        return -1;
    }
    if (L >= i && R <= j) {
        return st2[p];
    }
    ll p1 = maxq(left(p), L, (L+R)/2, i , j);
    ll p2 = maxq(right(p), (L+R)/2 + 1, R, i, j);
    return max(p1, p2);
}
void update1 (int p, int L, int R, int i, int val) {
    if (i < L || i > R) {
        return;
    }
    if (L == i && R == i) {
        st2[p] += val;
        return;
    }
    update1(left(p), L, (L+R)/2, i, val);
    update1(right(p), (L+R)/2 + 1, R, i, val);
    st2[p] = max(st2[left(p)], st2[right(p)]);
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, q; cin >> n >> q;
    pii curr_point;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        checkpoints.push_back(pii(x,y));
        if (i == 0) {
            curr_point = pii(x,y);
            continue;
        }
        values[i] = abs(x - curr_point.first) + abs(y - curr_point.second);
        curr_point = pii(x,y);
    }
    for(int i = 2; i <= n-1; i++) {
        values1[i] = values[i-1] + values[i] - abs(checkpoints[i-2].first - checkpoints[i].first) - abs(checkpoints[i-2].second - checkpoints[i].second);
    }
    /*for(int i = 1; i <= n; i++) {
        cout << values1[i] << endl;
    }*/
    build(1, 1, n-1);
    build1(1, 1, n);
    for(int i = 0; i < q; i++) {
        char x; cin >> x;
        if (x == 'Q') {
            int s, e; cin >> s >> e;
            ll curr_len = rmq(1, 1, n-1, s, e-1);
            //cout << "curr_len " << curr_len << endl;
            if (s == e) {
                cout << 0 << endl;
            }
            else if (e - s == 1) {
                cout << curr_len << endl;
            }
            else {
                //cout << "remove " << maxq(1, 1, n, s+1, e-1) << endl;
                cout << curr_len - maxq(1, 1, n, s+1, e-1) << endl;
            }
        }
        else {
            int ind, y, z; cin >> ind >> y >> z;
            //checkpoints[ind-1] = pii(y,z);
            if (ind == 1) {
                int curr_dist = values[1];
                int new_dist = abs(checkpoints[1].first - y) + abs(checkpoints[1].second-z);
                values[1] = new_dist;
                //values1[2] += new_dist-curr_dist;
                update(1, 1, n-1, 1, new_dist-curr_dist);
                update1(1, 1, n, 2, new_dist-curr_dist+abs(checkpoints[0].first - checkpoints[2].first) + abs(checkpoints[0].second - checkpoints[2].second) - (abs(checkpoints[2].first - y) + abs(checkpoints[2].second-z)));
                checkpoints[ind-1] = pii(y,z);
            }
            else if (ind == n) {
                int curr_dist = values[n-1];
                int new_dist = abs(checkpoints[n-2].first - y) + abs(checkpoints[n-2].second-z);
                values[n-1] = new_dist;
                //values1[n-1] += new_dist-curr_dist;
                update(1, 1, n-1, n-1, new_dist-curr_dist);
                update1(1, 1, n, n-1, new_dist-curr_dist + abs(checkpoints[n-1].first - checkpoints[n-3].first) + abs(checkpoints[n-1].second - checkpoints[n-3].second) - (abs(checkpoints[n-3].first - y) + abs(checkpoints[n-3].second - z)));
                checkpoints[ind-1] = pii(y,z);
            }
            else {
                if (ind == n-1) {
                    int curr_dist1 = values[ind];
                    int curr_dist2 = values[ind-1];
                    int new_dist1 = abs(checkpoints[ind].first - y) + abs(checkpoints[ind].second - z);
                    int new_dist2 = abs(checkpoints[ind-2].first - y) + abs(checkpoints[ind-2].second - z);
                    //cout << curr_dist1 << " " << curr_dist2 << " " << new_dist1 << " " << new_dist2 << endl;
                    values[ind] = new_dist1;
                    values[ind-1] = new_dist2;
                    update(1, 1, n-1, ind, new_dist1 - curr_dist1);
                    update(1, 1, n-1, ind-1, new_dist2 - curr_dist2);
                    update1(1, 1, n, ind, new_dist1 + new_dist2 - curr_dist1 - curr_dist2);
                    //update1(1, 1, n, ind+1, new_dist1 - curr_dist1 + abs(checkpoints[ind-1].first - checkpoints[ind+1].first) + abs(checkpoints[ind-1].second - checkpoints[ind+1].second) - (abs(checkpoints[ind+1].first - y) + abs(checkpoints[ind+1].second - z)));
                    update1(1, 1, n, ind-1, new_dist2 - curr_dist2 + abs(checkpoints[ind-1].first - checkpoints[ind-3].first) + abs(checkpoints[ind-1].second - checkpoints[ind-3].second) - (abs(checkpoints[ind-3].first - y) + abs(checkpoints[ind-3].second - z)));
                    checkpoints[ind-1] = pii(y,z);
                }
                else if (ind == 2) {
                    int curr_dist1 = values[ind];
                    int curr_dist2 = values[ind-1];
                    int new_dist1 = abs(checkpoints[ind].first - y) + abs(checkpoints[ind].second - z);
                    int new_dist2 = abs(checkpoints[ind-2].first - y) + abs(checkpoints[ind-2].second - z);
                    values[ind] = new_dist1;
                    values[ind-1] = new_dist2;
                    update(1, 1, n-1, ind, new_dist1 - curr_dist1);
                    update(1, 1, n-1, ind-1, new_dist2 - curr_dist2);
                    update1(1, 1, n, ind, new_dist1 + new_dist2 - curr_dist1 - curr_dist2);
                    update1(1, 1, n, ind+1, new_dist1 - curr_dist1 + abs(checkpoints[ind-1].first - checkpoints[ind+1].first) + abs(checkpoints[ind-1].second - checkpoints[ind+1].second) - (abs(checkpoints[ind+1].first - y) + abs(checkpoints[ind+1].second - z)));
                    //update1(1, 1, n, ind-1, new_dist2 - curr_dist2 + abs(checkpoints[ind-1].first - checkpoints[ind-3].first) + abs(checkpoints[ind-1].second - checkpoints[ind-3].second) - (abs(checkpoints[ind-3].first - y) + abs(checkpoints[ind-3].second - z)));
                    checkpoints[ind-1] = pii(y,z);
                }
                else {
                    int curr_dist1 = values[ind];
                    int curr_dist2 = values[ind-1];
                    int new_dist1 = abs(checkpoints[ind].first - y) + abs(checkpoints[ind].second - z);
                    int new_dist2 = abs(checkpoints[ind-2].first - y) + abs(checkpoints[ind-2].second - z);
                    values[ind] = new_dist1;
                    values[ind-1] = new_dist2;
                    update(1, 1, n-1, ind, new_dist1 - curr_dist1);
                    update(1, 1, n-1, ind-1, new_dist2 - curr_dist2);
                    update1(1, 1, n, ind, new_dist1 + new_dist2 - curr_dist1 - curr_dist2);
                    update1(1, 1, n, ind+1, new_dist1 - curr_dist1 + abs(checkpoints[ind-1].first - checkpoints[ind+1].first) + abs(checkpoints[ind-1].second - checkpoints[ind+1].second) - (abs(checkpoints[ind+1].first - y) + abs(checkpoints[ind+1].second - z)));
                    update1(1, 1, n, ind-1, new_dist2 - curr_dist2 + abs(checkpoints[ind-1].first - checkpoints[ind-3].first) + abs(checkpoints[ind-1].second - checkpoints[ind-3].second) - (abs(checkpoints[ind-3].first - y) + abs(checkpoints[ind-3].second - z)));
                    checkpoints[ind-1] = pii(y,z);
                }
            }
        }
    }
}
