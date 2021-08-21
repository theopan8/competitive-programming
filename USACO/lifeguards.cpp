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
#define maxn 100010
#define maxk 110
#define pii pair<int,int>
//#define int long long
vector<pii> temp;
vector<pii> guards;
int dp[maxk][maxn];
int jump[maxn];
int n, k;
int main() {
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int s, e; cin >> s >> e;
        temp.push_back(pii(s,e));
    }
    sort(temp.begin(), temp.end());
    int maxend = 0;
    guards.push_back(pii(0, 0));
    for(int i = 0; i < temp.size(); i++) {
        if (temp[i].second > maxend) {
            maxend = temp[i].second;
            guards.push_back(temp[i]);
            continue;
        }
        k--;
        continue;
    }
    if (k <= 0) {
        int last = 0;
        int tot = 0;
        for(pii i : guards) {
            if (i.first >= last) tot += i.second - i.first;
            else tot += i.second - last;
            last = i.second;
        }
        cout << tot << endl;
        return 0;
    }
    int idx = 0;
    for(int i = 1; i < guards.size(); i++) {
        while (idx + 1 < guards.size()) {
            if (guards[idx + 1].second <= guards[i].first) idx++;
            else break;
        }
        jump[i] = idx;
    }
    for(int i = 1; i <= k; i++) {
        dp[i][0] = -1000000000;
    }
    for(int j = 1; j < guards.size(); j++) {
        for(int i = 0; i <= min(j, k); i++) {
            dp[i][j] = max(0, dp[max(0, i - 1)][j - 1]);
            dp[i][j] = max(dp[i][j], dp[max(0, i - (j - jump[j] - 1))][jump[j]] + guards[j].second - guards[j].first);
            if (jump[i] < j - 1) {
                dp[i][j] = max(dp[i][j], dp[max(0, i - (j - jump[j] - 2))][jump[j] + 1] + guards[j].second - guards[jump[j] + 1].second);
            }
        }
        for(int i = min(j - 1, k) + 1; i <= k; i++) {
            dp[i][j] = -1000000000;
        }
    }
    /*for(int i = 0; i < guards.size(); i++) {
        for(int j = 0; j <= k; j++) {
            cout << dp[j][i] << " ";
        }
        cout << endl;
    }*/
    cout << dp[k][guards.size() - 1] << endl;
}