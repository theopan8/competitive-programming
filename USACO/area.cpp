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
#define ll long long
vector<point> points;
vector<point> hull; //top
vector<point> hull1; //bottom
ll cross(point o, point b, point a) {
    return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first);
}
int main() {
    //freopen("hayfeast.in", "r", stdin);
    //freopen("hayfeast.out", "w", stdout);
    int s; cin >> s;
    for(int i = 0; i < s; i++) {
        int n; cin >> n;
        for(int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            points.push_back(point(x,y));
        }
        sort(points.begin(), points.end());
        //get convex hull
        /*int k = 0;
        for(int i = 0; i < n; i++) {
            while (k >= 2 && cross(hull[k-2], hull[k-1], points[i]) <= 0) {
                k -= 1;
                hull.pop_back();
            }
            k += 1;
            hull.push_back(points[i]);
        }
        int t = hull.size();
        for(int i = n-1; i >= 0; i--) {
            while (k >= t && cross(hull[k-2], hull[k-1], points[i]) <= 0) {
                k -= 1;
                hull.pop_back();
            }
            k += 1;
            hull.push_back(points[i]);
        }*/
        int k = 0;
        for(int i = 0; i < n; i++) {
            while (k >= 2 && cross(hull[k-2], hull[k-1], points[i]) <= 0) {
                k -= 1;
                hull.pop_back();
            }
            k += 1;
            hull.push_back(points[i]);
        }
        int t = 0;
        for(int i = n-1; i >= 0; i--) {
            while (t >= 2 && cross(hull1[t-2], hull1[t-1], points[i]) <= 0) {
                t -= 1;
                hull1.pop_back();
            }
            t += 1;
            hull1.push_back(points[i]);
        }
        /*for(int i = 0; i < hull.size(); i++) {
            cout << "first " << hull[i].first << " " << hull[i].second << endl;
        }
        for(int i = 0; i < hull1.size(); i++) {
            cout << "second " << hull1[i].first << " " << hull1[i].second << endl;
        }*/
        ll area = 0;
        for(int i = 0; i < hull.size()-1; i++) {
            area += cross(hull[i], hull[i+1], point(0,0));
        }
        for(int i = 0; i < hull1.size()-1; i++) {
            area += cross(hull1[i], hull1[i+1], point(0,0));
        }
        cout << abs(area) << endl;
        points.clear();
        hull.clear();
        hull1.clear();
    }
}