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
#define MAXN 105
#define MOD 1000000007
ll vals[MAXN];
map<string, int> mapper;
stack<int> st;
ll currMatrix[MAXN][MAXN];
int curr = 0;
ll[][MAXN] mult(ll x[][MAXN], ll y[][MAXN]) {
    ll temp[MAXN][MAXN];
    for(int i = 0; i < MAXN; i++) {
        for(int j = 0; j < MAXN; j++) {
            temp[i][j] = 0;
            for(int k = 0; k < MAXN; k++) {
                temp[i][j] = (temp[i][j] + x[i][k] * y[k][j]) % MOD;
            }
        }
    }
    return temp;
}
ll ones[MAXN][MAXN];
ll[][MAXN] expp(ll x[][MAXN], int y) {
    if (y == 0) return ones;
    if (y == 1) return x;
    ll temp[][MAXN] = expp(x, y/2);
    if (y % 2 == 0) {
        return mult(temp, temp);
    }
    return mult(mult(temp, temp), x);
}
int main() {
    //freopen("cowbasic.in", "r", stdin);
    //freopen("cowbasic.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    memset(ones, 1, sizeof(ones));
    string s;
    while (cin >> s) {
        if (s == "RETURN") {
            cin >> s;
            cout << vals[mapper[s]] << endl;
            return 0;
        }
        else if (s[0] == '}') {

        }
        else if (s[0] - 'a' >= 0) {
            if (mapper.count(s) == 0) {
                mapper[s] = curr;
                curr++;
            }
            cin >> s;

        }
        else {
            st.push(stoi(s));
            cin >> s; cin >> s;
        }
    }
}