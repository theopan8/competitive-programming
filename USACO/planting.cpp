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
vector<pair<pair<ll, ll>, pair<ll,ll> > > regions;
map<ll, ll> counter;
map<ll, ll> count2;
map<ll, ll> distances;
bool comp (pair<pair<ll, ll>, pair<ll, ll> > i, pair<pair<ll, ll>, pair<ll, ll> > j) {
    return i.first.first < j.first.first;
}
struct cmp
{
    bool operator ()(const pair<ll, ll> &a, const pair<ll, ll> &b)
    {
        return a.first < b.first;
    }
};
int main() {
    //freopen("hayfeast.in", "r", stdin);
    //freopen("hayfeast.out", "w", stdout);
    ll n; cin >> n;
    for(int i = 0; i < n; i++) {
        ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        regions.push_back(make_pair(make_pair(x1, i), make_pair(y2, y1)));
        regions.push_back(make_pair(make_pair(x2, i), make_pair(y2, y1)));
    }
    sort(regions.begin(), regions.end(), comp);
    multiset<pair<ll, ll>, cmp> value_y;
    for(int i = 0; i < 2*n; i++) {
        pair<pair<ll, ll>, pair<ll, ll> > point = regions[i];
        counter[point.first.second] += 1;
        /*if (point.second.first == -314 && point.first.second == 43 && point.second.second == 283) {
            cout << value_y.size() << endl;
        }*/
        if (counter[point.first.second] == 2) {
            value_y.erase(make_pair(point.second.first, point.first.second));
            //cout << value_y.count(make_pair(point.second.second, point.first.second)) << endl;
            value_y.erase(make_pair(point.second.second, point.first.second));
        }
        else {
            value_y.insert(make_pair(point.second.first, point.first.second));
            value_y.insert(make_pair(point.second.second, point.first.second));
        }
        ll prev_y = 0;
        ll curr_count = 0;
        ll curr_distance = 0;
        /*if (value_y.size() % 2 != 0) {
            //cout << value_y.size() << endl;
            cout << point.second.first << " " << point.first.second << endl;
            cout << point.second.second << " " << point.first.second << endl;
            cout << "DONE" << endl;
            break;
        }*/
        for(auto j = value_y.begin(); j != value_y.end(); j++) {
            pair<ll, ll> value = *j;
            //cout << curr_count << " ";
            //cout << value.first << " ";
            count2[value.second] += 1;
            if (curr_count == 0) {
                curr_count += 1;
                prev_y = value.first;
            }
            else {
                if (count2[value.second] == 2) {
                    curr_count -= 1;
                    if (curr_count == 0) {
                        curr_distance += value.first - prev_y;
                    }
                }
                else {
                    curr_count += 1;
                }
            }
        }
        //cout << endl;
        //cout << endl;
        count2.clear();
        distances[point.first.first] = curr_distance;
        //cout << curr_distance << endl;
    }
    ll total = 0;
    ll prev_x = -1;
    ll prev_distance = 0;
    for(int i = 0; i < 2*n; i++) {
        pair<pair<ll, ll>, pair<ll, ll> > point = regions[i];
        if (i == 0) {
            prev_x = point.first.first;
            prev_distance = distances[point.first.first];
            continue;
        }
        total += (point.first.first - prev_x)*prev_distance;
        prev_x = point.first.first;
        prev_distance = distances[point.first.first];
    }
    /*for(int i = 0; i < 2*n-1; i++) {
        total += (regions[i+1].first.first - regions[i].first.first)*distances[regions[i].first.first];
    }*/
    cout << total << endl;
}