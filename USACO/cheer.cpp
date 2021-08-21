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
using namespace std;
#define maxn 10010
#define pii pair<int,int>
int costs[maxn];
vector<pii> graph[maxn];
int main() {
    ios_base::sync_with_stdio(0);
    int n, p; cin >> n >> p;
    for(int i = 0; i < n; i++) {
        int c; cin >> c;
        costs[i+1] = c;
    }
    for(int i = 0; i < p; i++) {
        int s, e, l; cin >> s >> e >> l;
        graph[s].push_back(pii(e,l));
        graph[e].push_back(pii(s,l));
    }
}