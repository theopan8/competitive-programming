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
#include <string>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <stack>
#include <cstring>
#include <deque>
#include <unordered_set>
using namespace std;
#define MAXN 100010
unordered_set<int> graph[MAXN];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        if(x > y) swap(x, y);
        graph[x].insert(y);
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j : graph[i]) {
            if(graph[i].size() > (int)sqrt(n)) {
                for(int k : graph[j])
                    if(graph[i].find(k) != graph[i].end()) ans++;
            }
            else {
                for(int k : graph[i])
                    if(j < k && graph[j].find(k) != graph[j].end()) ans++;
            }
        }
    }
    cout << ans << '\n';
}