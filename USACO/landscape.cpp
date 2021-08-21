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
#define MAXN 100010
ll dp[41][MAXN];
int A[MAXN];
int B[MAXN];
int main() {
    //freopen("landscape.in", "r", stdin);
    //freopen("landscape.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    ll n, x, y, z; cin >> n >> x >> y >> z;
    for(int i = 0; i < n; i++) {
        cin >> A[i];
        cin >> B[i];
    }
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    dp[A[0]][0] = 0;
    for(int i = 0; i < 25; i++) {
        if (i < A[0]) dp[i][0] = (A[0] - i) * y;
        else dp[i][0] = (i - A[0]) * x;
    }
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < 41; j++) {
            if (j < A[i]) {
                if (B[i - 1] >= A[i] - j) dp[j][i] = dp[B[i - 1] - A[i] + j][i - 1] + z * (A[i] - j);
            }
            else {
                if (B[i - 1] + j - A[i] < 25) dp[j][i] = dp[B[i - 1] + j - A[i]][i - 1] + z * (j - A[i]);
            }
        }
        for(int k = 0; k < 25; k++) {
            for(int j = 0; j < 25; j++) {
                if (j < k) {
                    if (dp[j][i] == -1) dp[j][i] = dp[k][i] + (k - j) * y;
                    else dp[j][i] = min(dp[j][i], dp[k][i] + (k - j) * y);
                }
                else {
                    if (dp[j][i] == -1) dp[j][i] = dp[k][i] + (j - k) * x;
                    else dp[j][i] = min(dp[j][i], dp[k][i] + (j - k) * x);
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 25; j++) {
            cout << dp[j][i] << " ";
        }
        cout << endl;
    }
    cout << dp[B[n - 1]][n - 1] << endl;
}