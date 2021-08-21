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
vector<int> campers;
int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        campers.push_back(x);
    }
    sort(campers.begin(), campers.end());
    int start = 0;
    int end = (campers[n-1] - campers[0])/k + 1;
    while (start + 1 < end) {
        int avg = (start+end)/2;
        int prev = campers[0];
        int staff = 1;
        for(int i = 1; i < n; i++) {
            if (campers[i] - prev <= avg) {
                continue;
            }
            staff += 1;
            prev = campers[i];
        }
        if (staff <= k) {
            end = avg;
        }
        else {
            start = avg;
        }
    }
    int prev = campers[0];
    int staff = 1;
    for(int i = 1; i < n; i++) {
        if (campers[i] - prev <= start) {
            continue;
        }
        staff += 1;
        prev = campers[i];
    }
    if (staff <= k) {
        cout << start << endl;
    }
    else {
        cout << end << endl;
    }
}