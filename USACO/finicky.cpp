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
#define maxhap 1010
#define maxpos 1010
#define pii pair<int,int>
int dp[maxhap][maxpos];
vector<pii> ;
int main() {
    ios_base::sync_with_stdio(0);
    //just do a dp[curr_happiness][curr_position] = cost currently
    //happiness and curr_position is bounded by 1000 so it is fine
    //we can also coordinate compress and just looks at the positions of the toy places
    //this would drop curr_position to just 100
    int h, e, n; cin >> h >> e >> n;
    for(int i = 0; i < n; i++) {
        int x, c, a; cin >> x >> c >> a;
        
    }
}
