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
long double pie = 3.14159265;
vector<point> points;
vector<point> hull; //top
vector<point> hull1; //bottom
ll cross(point o, point b, point a) {
    return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first);
}
double rounder(double var)
{
    double value = (int)(var * 100 + .5);
    return (double)value / 100;
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, c; cin >> n >> c;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.push_back(point(x,y));
    }
    sort(points.begin(), points.end());
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
    double total = 0; //perimeter
    for(int i = 0; i < hull.size()-1; i++) {
        //cout << "first " << hull[i].first << " " << hull[i].second << endl;
        double dx = (hull[i].first - hull[i+1].first);
        double dy = (hull[i].second - hull[i+1].second);
        total += (double)sqrt(1.0*dx*dx + 1.0*dy*dy);
    }
    for(int i = 0; i < hull1.size()-1; i++) {
        //cout << "second " << hull1[i].first << " " << hull1[i].second << endl;
        double dx = (hull1[i].first - hull1[i+1].first);
        double dy = (hull1[i].second - hull1[i+1].second);
        total += (double)sqrt(1.0*dx*dx + 1.0*dy*dy);
    }
    cout << total << endl;
    double area = 0; //area
    for(int i = 0; i < hull.size()-1; i++) {
        area += (double)cross(hull[i], hull[i+1], point(0,0))*1.0/2;
    }
    for(int i = 0; i < hull1.size()-1; i++) {
        area += (double)cross(hull1[i], hull1[i+1], point(0,0))*1.0/2;
    }
    area = abs(area);
    area += pie*c*c;
    for(int i = 0; i < hull.size()-1; i++) {
        double dx = (hull[i].first - hull[i+1].first);
        double dy = (hull[i].second - hull[i+1].second);
        area += (double)sqrt(1.0*dx*dx + 1.0*dy*dy)*c*1.0;
    }
    for(int i = 0; i < hull1.size()-1; i++) {
        double dx = (hull1[i].first - hull1[i+1].first);
        double dy = (hull1[i].second - hull1[i+1].second);
        area += (double)sqrt(1.0*dx*dx + 1.0*dy*dy)*c*1.0;
    }
    total += 2*pie*c;
    //cout << round(total) << endl;*/
    printf("%.2f %.2f", total, area);
    /*cout << " ";
    printf("%.2f", area);*/
    cout << endl;
    //cout << rounder(total) << " " << rounder(area) << endl;
}