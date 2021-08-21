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
#define pii pair<int,int>
#define maxn 100010
vector<pii> sprinklers;

int main() {
    //freopen("sprinklers.in", "r", stdin);
    //freopen("sprinklers.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        sprinklers.push_back(pii(x,y));
    }
    
}