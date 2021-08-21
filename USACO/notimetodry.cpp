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
#include <cstring>
#include <deque>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, int> ppi;
const int MAXN = 200010;
int vals[MAXN];
int st[MAXN << 2];
int forwNum[MAXN];
int backNum[MAXN];
int forwPos[MAXN];
int backPos[MAXN];
int ans[MAXN];
map<int, int> mapper;
int left(int p) {
    return (p << 1);
}
int right(int p) {
    return (p << 1) + 1;
}
void build(int p, int L, int R) {
    if(L == R) st[p] = vals[L];
    else {
        build(left(p), L, (L+R)/2);
        build(right(p), (L+R)/2 + 1, R);
        st[p] = min(st[left(p)], st[right(p)]);
    }
}
int query(int p, int L, int R, int i, int j) {
    if(i > R || j < L) return -1;
    if(L >= i && R <= j) return st[p];
    ll p1 = query(left(p), L, (L + R)/2, i , j);
    ll p2 = query(right(p), (L + R)/2 + 1, R, i, j);
    if(p1 == -1) return p2;
    if(p2 == -1) return p1;
    return min(p1, p2);
}
int block;
bool comp(ppi i, ppi j) {
    return i.first.first/block < j.first.first/block || (i.first.first/block == j.first.first/block && i.first.second < j.first.second);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, q; cin >> n >> q;
    block = sqrt(n);
    for(int i = 1; i <= n; i++)
        cin >> vals[i];
    build(1, 1, n);
    for(int i = 1; i <= n; i++) {
        if(mapper[vals[i]] != 0) {
            if(query(1, 1, n, mapper[vals[i]], i) != vals[i]) {
                forwNum[mapper[vals[i]]] = 1;
                backNum[i] = 1;
            }
            forwPos[mapper[vals[i]]] = i;
            backPos[i] = mapper[vals[i]];
        }
        mapper[vals[i]] = i;
    }
    vector<ppi> queries;
    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        queries.push_back(ppi(pii(x, y), i));
    }
    sort(queries.begin(), queries.end(), comp);
    int cnt = 0;
    int numColors = 0;
    for(int i = 0; i < queries.size(); i++) {
        if(i == 0) {
            pii curr = queries[i].first;
            for(int j = curr.first; j <= curr.second; j++) {
                if(curr.first <= backPos[j]) cnt += backNum[j];
                else numColors++;
            }
            ans[queries[i].second] = numColors + cnt;
        }
        else {
            pii prev = queries[i - 1].first;
            pii curr = queries[i].first;
            if(prev.first < curr.first) {
                for(int j = prev.first; j < curr.first; j++) {
                    if(forwPos[j] <= prev.second && forwPos[j] != 0) cnt -= forwNum[j];
                    else numColors--;
                }
            }
            else if(prev.first > curr.first) {
                for(int j = prev.first - 1; j >= curr.first; j--) {
                    if(forwPos[j] <= prev.second && forwPos[j] != 0) cnt += forwNum[j];
                    else numColors++;
                }
            }
            if(prev.second < curr.second) {
                for(int j = prev.second + 1; j <= curr.second; j++) {
                    if(curr.first <= backPos[j]) cnt += backNum[j];
                    else numColors++;
                }
            }
            else if(prev.second > curr.second) {
                for(int j = prev.second; j > curr.second; j--) {
                    if(curr.first <= backPos[j]) cnt -= backNum[j];
                    else numColors--;
                }
            }
            ans[queries[i].second] = numColors + cnt;
        }
    }
    for(int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}