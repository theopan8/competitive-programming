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
#include <limits>
using namespace std;
#define maxn 110
#define maxt 20200
#define pii pair<int,int>
vector<int> values;
vector<int> nums;
int farmer[maxt];
int change[maxt];
vector<pii> comb;
int used[maxt];
int main() {
    ios_base::sync_with_stdio(0);
    int n, t; cin >> n >> t;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        values.push_back(x);
    }
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }
    //calculate the change
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2*t; j++) {
            if (j == values[i]) {
                change[j] = 1;
            }
            else if (j > values[i]) {
                if (change[j-values[i]] != 0) {
                    if (change[j-values[i]] + 1 < change[j]) {
                        change[j] = change[j-values[i]] + 1;
                    }
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        
    }
}