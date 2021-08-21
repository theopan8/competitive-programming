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
map<pair<int,int>, int> cow_map;
vector<pair<int,int> > H;
vector<pair<int,int> > cows;
map<pair<int,int>, int> cow_pos;
bool comp1 (pair<int,int> i, pair<int,int> j) {
    return i.second < j.second;
}
bool comp (pair<int,int> i, pair<int,int> j) {
    return i.first < j.first;
}
int main() {
    //freopen("hayfeast.in", "r", stdin);
    //freopen("hayfeast.out", "w", stdout);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        char cow; cin >> cow;
        if (cow == 'H') {
            H.push_back(make_pair(x,y));
            cow_map[make_pair(x,y)] = 1;
        }
        cows.push_back(make_pair(x,y));
    }
    sort(cows.begin(), cows.end(), comp);
    sort(H.begin(), H.end(), comp);
    for(int i = 0; i < n; i++) {
        cow_pos[cows[i]] = i;
    }
    int num_cows = 0;
    int area = -1;
    for(int i = 0; i < H.size(); i++) {
        for(int j = i; j < H.size(); j++) {
            vector<pair<int,int> > act_cows;
            for(int k = cow_pos[H[i]]; k <= cow_pos[H[j]]; k++) {
                act_cows.push_back(cows[k]);
            }
            sort(act_cows.begin(), act_cows.end(), comp1);
            int count = 0;
            int curr_y = 0;
            int last_y = 0;
            for(int k = 0; k < act_cows.size(); k++) {
                if (cow_map[act_cows[k]] == 1) {
                    if (count == 0) {
                        last_y = act_cows[k].second;
                    }
                    count += 1;
                    curr_y = act_cows[k].second;
                }
                else {
                    if (count == 0) {
                        continue;
                    }
                    else {
                        if (count > num_cows) {
                            num_cows = count;
                            area = (-last_y + curr_y)*(H[j].first - H[i].first);
                        }
                        else if (count == num_cows) {
                            if (area == -1) {
                                area = (-last_y + curr_y)*(H[j].first - H[i].first);
                            }
                            else if (area > (-last_y + curr_y)*(H[j].first - H[i].first)) {
                                area = (-last_y + curr_y)*(H[j].first - H[i].first);
                            }
                        }
                        count = 0;
                        curr_y = 0;
                        last_y = 0;
                    }
                }
            }
        }
    }
    cout << num_cows << endl;
    cout << area << endl;
}