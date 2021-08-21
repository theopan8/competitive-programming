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
vector<int> graph[MAXN];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    
}