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
#define pii pair<long long,int>
#define maxn 100010
vector<long long> prefix;
long long dp[maxn];
int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    long long curr = 0;
    prefix.push_back(curr);
    for(int i = 0; i < n; i++) {
        long long x; cin >> x;
        curr += x;
        prefix.push_back(curr);
    }
    priority_queue<pii> q;
    q.push(pii(0, -1));
    for(int i = 0; i <= n; i++) {
        while (q.top().second < i-k-1) {
            q.pop();
        }
        dp[i] = q.top().first + prefix[i];
        q.push(pii(dp[i] - prefix[i+1], i));
    }
    cout << dp[n] << endl;
}