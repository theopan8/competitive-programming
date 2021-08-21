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
typedef pair<ll, ll> pii;
#define MAXN 50010
#define MAXK 30
#define MAXQ 200010
#define MOD 1000000007
int n, k;
int vals[MAXN];
struct query {
    int l, r, idx;
};
int ans[MAXQ];
void solve(vector<query> queries, int L, int R) {
    int avg = (L + R)/2;
    vector<query> left;
    vector<query> right;
    vector<query> curr;
    for(query q : queries) {
        if(q.r < avg) left.push_back(q);
        else if(q.l > avg) right.push_back(q);
        else curr.push_back(q);
    }
    if(L == R) return;
    solve(left, L, avg);
    solve(right, avg + 1, R);
}
int main() {
    //freopen("nondec.in", "r", stdin);
    //freopen("nondec.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> vals[i];
    int q; cin >> q;
    vector<query> queries;
    for(int i = 1; i <= q; i++) {
        int l, r; cin >> l >> r;
        queries.push_back(query{l, r, i});
    }
    solve(queries, 1, n);

}