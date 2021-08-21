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
#define ll long long
vector<pair<ll,pair<ll,ll> > > builds;
map<ll, ll> counter;
multiset<ll> heights;
bool comp (pair<ll, pair<ll,ll> > i, pair<ll, pair<ll, ll> > j) {
    return i.first < j.first;
}
int main() {
    //freopen("censor.in", "r", stdin);
    //freopen("censor.out", "w", stdout);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int a, b, h; cin >> a >> b >> h;
        builds.push_back(make_pair(a, make_pair(h, i)));
        builds.push_back(make_pair(b, make_pair(h, i)));
    }
    sort(builds.begin(), builds.end(), comp);
    ll area = 0;
    for(int i = 0; i < 2*n-1; i++) {
        pair<ll, pair<ll,ll> > build = builds[i];
        counter[build.second.second] += 1;
        if (counter[build.second.second] == 2) {
            heights.erase(heights.find(build.second.first));
        }
        else {
            heights.insert(build.second.first);
        }
        if (heights.size() == 0) {
            continue;
        }
        ll height = *heights.rbegin();
        //cout << height << endl;
        area += height*(builds[i+1].first - builds[i].first);
    }
    cout << area << endl;
}