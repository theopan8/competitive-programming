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
vector<int> toys;
int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        toys.push_back(a);
    }
    int max = 0;
    int start = 0;
    int end = 0;
    int average = toys[0];
    int curr_l = 0;
    while (start <= end && end <= n-1) {
        if ((long double)average*1.0/(end-start+1) > k) {
            curr_l -= 1;
            if (curr_l < 0) {
                curr_l = 0;
            }
            average -= toys[start];
            start += 1;
        }
        else {
            curr_l += 1;
            end += 1;
            if (curr_l > max) {
                max = curr_l;
            }
            if (end <= n-1) {
                average += toys[end];
            }
        }
    }
    if (curr_l > max) {
        max = curr_l;
    }
    cout << max << endl;
}
