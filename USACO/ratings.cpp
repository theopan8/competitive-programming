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
vector<int> ratings;
int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ratings.push_back(x);
    }
    sort(ratings.begin(), ratings.end());
    int total = 0;
    for(int i = 0; i < k; i++) {
        if (ratings[i] < 0) {
            total += ratings[i];
        }
        else {
            break;
        }
    }
    cout << -total << endl;
}
