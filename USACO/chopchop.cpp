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
using namespace std;
map<int,int> counter;
map<int,int> prevs;
map<int,int> lefts;
map<int,int> rights;
vector<int> veg;
bool go (int s, int e) {
    //cout << s << " " << e << endl;
    if (e - s == 0) {
        return true;
    }
    if (e - s == 1) {
        if (veg[s-1] == veg[e-1]) {
            return false;
        }
        return true;
    }
    int start = s;
    int end = e;
    while (start <= end) {
        //cout << start << " " << end << endl;
        if ((lefts[start] <= e && lefts[start] >= s) || (rights[start] <= e && rights[start] >= s)) {
            if ((lefts[end] <= e && lefts[end] >= s) || (rights[end] <= e && rights[end] >= s)) {
                start += 1;
                end -= 1;
                continue;
            }
            else {
                if (end < e) {
                    return (go(s,end-1) && go(end+1,e));
                }
                return go(s, end-1);
            }
        }
        else {
            if (start > s) {
                return (go(s, start-1) && go(start+1, e));
            }
            return go(start+1, e);
        }
        start += 1;
        end -= 1;
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    for(int i = 0; i < t; i++) {
        int n; cin >> n;
        for(int j = 1; j <= n; j++) {
            int x; cin >> x;
            veg.push_back(x);
            if (counter[x] == 0) {
                counter[x] += 1;
                prevs[x] = j;
                continue;
            }
            lefts[j] = prevs[x];
            rights[prevs[x]] = j;
            prevs[x] = j;
        }
        if (go(1, n)) {
            cout << 1 << endl;
        }
        else {
            cout << 0 << endl;
        }
        counter.clear();
        prevs.clear();
        lefts.clear();
        rights.clear();
        veg.clear();
    }
}