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
vector<int> toys;
multiset<int> run_toys;
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        toys.push_back(a);
    }
    int first = 0;
    int last = 1;
    int max_total = 0;
    run_toys.insert(toys[0]);
    bool inc_last = true;
    while (last <= n-1 && first <= last) {
        //cout << first << " " << last << endl;
        if (inc_last) {
            run_toys.insert(toys[last]);
        }
        inc_last = true;
        int max = *run_toys.rbegin();
        int min = *run_toys.begin();
        if (max - min <= k) {
            last += 1;
        }
        else {
            inc_last = false;
            run_toys.erase(run_toys.find(toys[first]));
            if (last - first > max_total) {
                max_total = last - first;
            }
            first += 1;
        }
    }
    if (last - first > max_total) {
        max_total = last - first;
    }
    cout << max_total << endl;
}