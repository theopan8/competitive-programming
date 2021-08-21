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
#define pi 3.14159265358979
vector<pair<double,pair<int,int> > > cows;
int main() {
    //freopen("hayfeast.in", "r", stdin);
    //freopen("hayfeast.out", "w", stdout);
    int n, r; cin >> n >> r;
    for(int i = 0; i < n; i++) {
        int x,y; cin >> x >> y;
        pair<int,int> cow (x,y);
        double curr_angle = 0;
        if (x == 0) {
            if (y > 0) {
                curr_angle = (double)pi/2.0;
            }
            else {
                curr_angle = (double)3*pi/2.0;
            }
        }
        else if (x > 0) {
            curr_angle = atan((double)y/x);
        }
        else {
            curr_angle = atan((double)y/x) + (double)pi/2.0;
        }
        double curr_angle1 = acos((double)r/(sqrt(x*x + y*y))) + curr_angle; //end
        double curr_angle2 = acos((double)r/(sqrt(x*x + y*y))) - curr_angle; //start
        cows.push_back(curr_angle1, make_pair(i, 1));
        if (curr_angle2 < 0) {
            curr_angle2 += 2*pi;
        }
        cows.push_back(curr_angle2, make_pair(i, 0));
   }
}