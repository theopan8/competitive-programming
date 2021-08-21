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
#define point pair<int,int>
vector<point> points;
set<point> counter;
int gcdd (int i, int j) {
    //cout << i << " " << j << endl;
    if (i == j) {
        return i;
    }
    else if (i > j) {
        return gcdd(i - j, j);
    }
    else {
        return gcdd(i, j - i);
    }
}
int main() {
    //freopen("hayfeast.in", "r", stdin);
    //freopen("hayfeast.out", "w", stdout);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.push_back(point(x,y));
    }
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            int x = points[j].first - points[i].first;
            int y = points[j].second - points[i].second;
            if (y > 0 && x > 0) {
                int ph = gcdd(x,y);
                counter.insert(point(y/ph, x/ph));
            }
            else if (y == 0) {
                counter.insert(point(0,1));
            }
            else if (x == 0) {
                counter.insert(point(1,0));
            }
            else if (y < 0 && x > 0) {
                int ph = gcdd(abs(y),x);
                counter.insert(point(y/ph, x/ph));
            }
            else if (y > 0 && x < 0) {
                int ph = gcdd(y, abs(x));
                counter.insert(point(-y/ph, abs(x)/ph));
            }
            else {
                int ph = gcdd(abs(y), abs(x));
                counter.insert(point(abs(y)/ph, abs(x)/ph));
            }
        }
    }
    cout << counter.size() << endl;
}