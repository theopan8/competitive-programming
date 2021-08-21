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
#include <cstring>
using namespace std;
#define pii pair<int,int>
#define maxm 100010
#define maxm2 200020
#define maxk 17
int sparse[maxm][maxk];
vector<pii> intervals;
//real one
vector<pii> covers;
map<pii, int> bad;
vector<pair<int,pii > > coord;
map<pii, int> coord_mapping;
map<int,int> visited;
multiset<pii> end_points;
map<int, pii> map_type;
bool comp (pair<int, pii> i, pair<int, pii> j) {
    if (i.first < j.first) {
        return true;
    }
    else if (i.first > j.first) {
        return false;
    }
    else {
        if (i.second.second == 0) {
            return true;
        }
        else {
            return false;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    int c, m; cin >> c >> m;
    for(int i = 0; i < m; i++) {
        int x, l; cin >> x >> l;
        intervals.push_back(pii(x, l+x));
        if (l+x < c) {
            intervals.push_back(pii(x+c, l+x+c));
        }
    }
    sort(intervals.begin(), intervals.end());
    int max_end = 0;
    for(int i = 0; i < intervals.size(); i++) {
        if (max_end < intervals[i].second) {
            max_end = intervals[i].second;
            continue;
        }
        bad[intervals[i]] = 1;
        if (intervals[i].first >= c) {
            bad[pii(intervals[i].first - c, intervals[i].second-c)] = 1;
        }
        if (intervals[i].second < c) {
            bad[pii(intervals[i].first + c, intervals[i].second + c)] = 1;
        }
    }
    for(int i = 0; i < intervals.size(); i++) {
        if (bad[intervals[i]] == 1) {
            continue;
        }
        covers.push_back(intervals[i]);
    }
    for(int i = 0; i < covers.size(); i++) {
        coord.push_back(make_pair(covers[i].first,pii(i+1, 0)));
        coord.push_back(make_pair(covers[i].second,pii(i+1,1)));
        coord_mapping[pii(covers[i].first,i+1)] = covers[i].second;
        map_type[i+1] = pii(covers[i].first, covers[i].second);
    }
    sort(coord.begin(), coord.end(), comp);
    //cout << "size: " << coord.size() << endl;
    for(int i = 0; i < coord.size(); i++) {
        pair<int,pii> x = coord[i];
        //cout << x.first << " " << x.second.first << endl;
        visited[x.second.first] += 1;
        if (visited[x.second.first] == 2) {
            end_points.erase(end_points.find(pii(x.first, x.second.first)));
            if (end_points.size() == 0) {
                break;
            }
            sparse[x.second.first][0] = (*end_points.rbegin()).second;
        }
        else {
            //cout << "push: " << coord_mapping[pii(x.first, x.second.first)] << " " << x.second.first << endl;
            end_points.insert(pii(coord_mapping[pii(x.first, x.second.first)], x.second.first));
        }
    }
    for(int i = 1; i < maxk; i++) {
        for(int j = 1; j <= covers.size(); j++) {
            sparse[j][i] = sparse[sparse[j][i-1]][i-1];
        }
    }
    //sparse[i][j] i is current segment, j is 2^j new segments
    int min = -1;
    for(int i = 1; i <= covers.size(); i++) {
        //cout << i << endl;
        int curr = i;
        int dist = map_type[i].second - map_type[i].first;
        int running_total = 1;
        for(int j = maxk-1; j >= 0; j--) {
            if (sparse[curr][j] == 0) {
                continue;
            }
            //cout << "j: " << j << endl;
            dist += (map_type[sparse[curr][j]].second - map_type[curr].second);
            running_total += (sparse[curr][j] - curr);
            curr = sparse[curr][j];
            //cout << "distance: " << dist << endl;
            //cout << "curr: " << curr << endl;
            //cout << "running total: " << running_total << endl;
            if (dist >= c) {
                break;
            }
        }
        if (dist >= c) {
            if (min == -1 || min > running_total) {
                min = running_total;
            }
        }
    }
    cout << min << endl;
}