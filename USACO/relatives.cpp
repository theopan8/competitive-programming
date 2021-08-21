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
#include <cstring>
using namespace std;
#define maxn 17
#define maxb 1 << 17
#define pii pair<int,float>
float graph1[maxn][maxn];
float dp[maxn][maxb];
int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    for(int phat = 0; phat < t; phat++) {
        int n; cin >> n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                float d; cin >> d;
                if (i == j) {
                    continue;
                }
                //cout << d << endl;
                graph1[i][j] = d;
            }
        }
        //look at path that starts at 0 and goes through all other vertices
        for(int i = 1; i < (1 << (n-1)); i++) {
            for(int j = 1; j < n; j++) {
                //cout << j << " " << i << endl;
                if (((i & (1 << (j-1))) == 0)) {
                    continue;
                }
                if ((__builtin_popcount(i) == 1) && ((i & (1 << (j-1))) != 0)) {
                    dp[j][i] = graph1[0][j];
                    //cout << j << " " << i << " " << dp[j][i] << endl;
                    continue;
                }
                float min = -1;
                for(int v = 1; v < n; v++) {
                    if (j == v) {
                        continue;
                    }
                    if ((i & (1 << (v - 1))) == 0) {
                        continue;
                    }
                    if (min == -1 || min > dp[v][i & ~(1 << (j-1))] + graph1[v][j]) {
                        min = dp[v][i & ~(1 << (j-1))] + graph1[v][j];
                    }
                }
                if (min == -1) {
                    continue;
                }
                else {
                    dp[j][i] = min;
                }
                //cout << j << " " << i << " " << dp[j][i] << endl;
            }
        }
        float min = -1;
        for(int i = 1; i < n; i++) {
            //cout << dp[i][(1<<n) - 1] << endl;
            if (dp[i][(1 << (n-1))-1] == 0) {
                continue;
            }
            if (min == -1 || min > dp[i][(1 << (n-1))-1] + graph1[i][0]) {
                min = dp[i][(1 << (n-1))-1] + graph1[i][0];
            }
        }
        printf("%.2f\n", min);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                graph1[i][j] = 0;
            }
        }
        for(int i = 1; i < maxb; i++) {
            for(int j = 1; j < maxn; j++) {
                dp[j][i] = 0;
            }
        }
    }
}