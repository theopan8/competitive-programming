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
vector<point> points1;
vector<point> hull;
vector<point> hull1;
vector<point> hull2;
vector<point> hull3;
vector<point> hullPoints;
vector<point> hullPoints1;
ll cross(point o, point b, point a) {
    return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first);
}
int main() {
    //freopen("curling.in", "r", stdin);
    //freopen("curling.out", "w", stdout);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.push_back(point(x,y));
    }
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points1.push_back(point(x,y));
    }
    sort(points.begin(), points.end());
    sort(points1.begin(), points1.end());
    int k = 0;
    for(int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull[k-2], hull[k-1], points[i]) < 0) {
            k -= 1;
            hull.pop_back();
        }
        k += 1;
        hull.push_back(points[i]);
    }
    int t = 0;
    for(int i = n-1; i >= 0; i--) {
        while (t >= 2 && cross(hull1[t-2], hull1[t-1], points[i]) < 0) {
            t -= 1;
            hull1.pop_back();
        }
        t += 1;
        hull1.push_back(points[i]);
    }
    k = 0;
    for(int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull2[k-2], hull2[k-1], points1[i]) < 0) {
            k -= 1;
            hull2.pop_back();
        }
        k += 1;
        hull2.push_back(points1[i]);
    }
    t = 0;
    for(int i = n-1; i >= 0; i--) {
        while (t >= 2 && cross(hull3[t-2], hull3[t-1], points1[i]) < 0) {
            t -= 1;
            hull3.pop_back();
        }
        t += 1;
        hull3.push_back(points1[i]);
    }
    for(int i = 0; i < hull.size(); i++) {
        hullPoints.push_back(hull[i]);
    }
    for(int i = 1; i < hull1.size() - 1; i++) {
        hullPoints.push_back(hull1[i]);
    }
    for(int i = 0; i < hull2.size(); i++) {
        hullPoints1.push_back(hull2[i]);
    }
    for(int i = 1; i < hull3.size() - 1; i++) {
        hullPoints1.push_back(hull3[i]);
    }
    int dx = hullPoints[0].first; int dy = hullPoints[0].second;
    for(int i = 0; i < hullPoints.size(); i++) {
        hullPoints[i] = point(hullPoints[i].first - dx, hullPoints[i].second - dy);
    }
    for(int i = 0; i < points1.size(); i++) {
        points1[i] = point(points1[i].first - dx, points1[i].second - dy);
    }
    dx = hullPoints1[0].first; dy = hullPoints1[0].second;
    for(int i = 0; i < hullPoints1.size(); i++) {
        hullPoints1[i] = point(hullPoints1[i].first - dx, hullPoints1[i].second - dy);
    }
    for(int i = 0; i < points.size(); i++) {
        points[i] = point(points[i].first - dx, points[i].second - dy);
    }
    /*int total = 0;
    for(int i = 0; i < points.size(); i++) {
        int low = 1;
        int high = hullPoints1.size() - 1;
        int ans = -1;
        while (high > low + 1) {
            int avg = (low + high) / 2;
            if (cross(point(0,0), points[i], hullPoints1[avg]) <= 0  && cross(point(0,0), points[i], hullPoints1[avg + 1]) >= 0 && (cross(hullPoints1[avg+1], hullPoints1[avg], points[i]) <= 0)) {
                ans = avg;
                break;
            }
            if (cross(point(0,0), points[i], hullPoints1[avg]) > 0) {
                high = avg;
            }
            else {
                low = avg;
            }
        }
        if (ans == -1) {
            continue;
        }
        else {
            total += 1;
        }
    }
    int total1 = 0;
    for(int i = 0; i < points1.size(); i++) {
        int low = 1;
        int high = hullPoints.size() - 1;
        int ans = -1;
        while (high > low + 1) {
            int avg = (low + high) / 2;
            if (cross(point(0,0), points1[i], hullPoints[avg]) <= 0  && cross(point(0,0), points1[i], hullPoints[avg + 1]) >= 0 && (cross(hullPoints[avg+1], hullPoints[avg], points1[i]) <= 0)) {
                ans = avg;
                break;
            }
            if (cross(point(0,0), points1[i], hullPoints[avg]) > 0) {
                high = avg;
            }
            else {
                low = avg;
            }
        }
        if (ans == -1) {
            continue;
        }
        else {
            total1 += 1;
        }
    }
    cout << total1 << " " << total << endl;*/
    int total = 0;
    for(int i = 0; i < points.size(); i++) {
        int low = 1;
        int high = hullPoints1.size() - 1;
        bool done = false;
        while (high > low + 1) {
            int avg = (low + high) / 2;
            if (cross(point(0,0), hullPoints1[avg], points[i]) >= 0 && cross(point(0,0), hullPoints1[avg+1], points[i]) <= 0 && cross(hullPoints1[avg], hullPoints1[avg+1], points[i]) >= 0) {
                if (cross(point(0,0), hullPoints1[avg], hullPoints1[avg+1]) == 0) {
                    //all on a line
                    if ((points[i].first >= min(0, hullPoints1[avg+1].first) && points[i].first <= max(0, hullPoints1[avg+1].first)) || (points[i].first >= min(hullPoints1[avg].first, hullPoints1[avg+1].first) && points[i].first <= max(hullPoints1[avg].first, hullPoints1[avg+1].first))) {
                        done = true;
                        break;
                    }
                }
                else {
                    done = true;
                    break;
                }
            }
            if (cross(point(0,0), hullPoints1[avg], points[i]) > 0) {
                low = avg;
            }
            else {
                high = avg;
            }
        }
        if (done) {
            total++;
        }
    }
    cout << total << endl;
}