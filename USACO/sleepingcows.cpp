#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 3010;
const ll MOD = 1000000007;
int cows[MAXN];
int barns[MAXN];
int low[MAXN];
int high[MAXN];
ll frontDP[MAXN][MAXN];
ll backDP[MAXN][MAXN];
ll factorial[MAXN];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 1; i <= n; i++)
    	cin >> cows[i];
    for(int i = 1; i <= n; i++)
    	cin >> barns[i];
    factorial[0] = 1;
    for(int i = 1; i <= n; i++)
    	factorial[i] = (factorial[i - 1] * (ll)i) % MOD;
    sort(cows, cows + (n + 1));
    sort(barns, barns + (n + 1));
    ll ans = 0;
    int curr = 1;
    for(int i = 1; i <= n; i++) {
    	while(curr <= n && cows[i] > barns[curr])
    		curr++;
    	low[i] = curr;
    }
   	curr = 1;
   	for(int i = 1; i <= n; i++) {
   		while(curr <= n && cows[curr] <= barns[i])
   			curr++;
   		high[i] = curr - 1;
   	}
    backDP[n][1] = n - low[n] + 1;
    backDP[n][0] = 1;
    for(int i = n - 1; i >= 1; i--) { //cow
    	for(int j = 0; j <= n - i + 1; j++) { //# of paired
    		if(j > 0) backDP[i][j] = (backDP[i + 1][j - 1] * (ll)max(n - low[i] + 1 - (j - 1), 0)) % MOD;
    		backDP[i][j] = (backDP[i][j] + backDP[i + 1][j]) % MOD;
    	}
    }
    /*for(int i = 1; i <= n; i++) {
    	for(int j = 0; j <= n - i + 1; j++) {
    		cout << backDP[i][j] << ' ';
    	}
    	cout << '\n';
    }*/
    frontDP[0][0] = 1;
    frontDP[1][0] = 1;
    frontDP[1][1] = high[1];
    for(int i = 2; i <= n; i++) {
    	for(int j = 0; j <= i; j++) {
    		if(j > 0) frontDP[i][j] = (frontDP[i - 1][j - 1] * (ll)max(high[i] - (j - 1), 0)) % MOD;
    		frontDP[i][j] = (frontDP[i][j] + frontDP[i - 1][j]) % MOD;
    	}
    }
    /*
    for(int i = 1; i < n; i++) { //cow
    	vector<vector<ll>> tempDP(i + 1, vector<ll>(i + 1));
    	tempDP[i][0] = low[i + 1] - low[i];
    	tempDP[i][1] = 1;
    	for(int k = i - 1; k >= 1; k--) {
    		for(int h = 0; h <= min(i - k + 1, n - low[i + 1] + 1); h++) {
    			if(h > 0) tempDP[k][h] = (tempDP[k + 1][h - 1]) % MOD;
    			tempDP[k][h] = (tempDP[k][h] + (tempDP[k + 1][h] * (ll)max(low[i + 1] - low[k] - (i - k - h), 0)) % MOD) % MOD;
    		}
    	}
    	for(int k = max(0, low[i + 2] - low[i + 1]); k <= i; k++)
    		frontDP[i][k] = (factorial[k] * tempDP[1][k]) % MOD;
    }*/
    /*for(int i = 1; i <= n; i++) {
    	for(int j = 0; j <= i; j++) {
    		cout << frontDP[i][j] << ' ';
    	}
    	cout << '\n';
    }*/

    ans = backDP[1][n];
    ans = (ans + backDP[2][n - low[1] + 1]) % MOD;
    ans = (ans + (factorial[n - low[n] + 1] * frontDP[low[n] - 1][n - 1]) % MOD) % MOD;
    for(int i = 2; i < n; i++) {
    	for(int j = 0; j <= n - low[i] + 1; j++) {
    		if(i - 1 - (n - low[i] + 1 - j) >= 0) ans = (ans + factorial[n - low[i] + 1 - j] * ((frontDP[low[i] - 1][i - 1 - (n - low[i] + 1 - j)] * backDP[i + 1][j]) % MOD)) % MOD;
    	}
    }
    cout << ans << '\n';
}