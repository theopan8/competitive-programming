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
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, int> pip;
vector<int> graph[110];
int ans[110];
int main() {
    //freopen("revegetate.in", "r", stdin);
    //freopen("revegetate.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    memset(ans, 0, sizeof(ans));
    for(int i = 1; i <= n; i++) {
        set<int> s;
        for(int j : graph[i]) {
            s.insert(ans[j]);
        }
        int curr = s.size();
        int color = 0;
        for(int j = 1; j <= 4; j++) {
            s.insert(j);
            if (s.size() != curr) {
                color = j;
                break;
            }
        }
        ans[i] = color;
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i];
    }
}