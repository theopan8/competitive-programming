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
#include <cstring>
#include <limits>
using namespace std;
const int maxn = 100010;
struct pieB {
    int bes, els;
    bool operator < (const pieB &other) const {
        return this->els < other.els || (this->els == other.els && this->bes < other.bes);
    }
};
struct pieE {
    int bes, els;
    bool operator < (const pieE &other) const {
        return this->bes < other.bes || (this->bes == other.bes && this->els < other.els);
    }
};
struct State {
    int idx, dist;
};
vector<pieB> bessie;
vector<int> orig_pos;
vector<pieE> elsie;
int answer[maxn];
int values[maxn << 1];
bool comp1 (pieB i, pieB j) {
    return i.els < j.els;
}
bool comp2 (pieE i, pieE j) {
    return i.bes < j.bes;
}
bool comp3 (int i, int j) {
    return bessie[i].els < bessie[j].els || (bessie[i].els == bessie[j].els && bessie[i].bes < bessie[j].bes);
}
int main() {
    ios_base::sync_with_stdio(0);
    //freopen("piepie.in", "r", stdin);
    //freopen("piepie.out", "w", stdout);
    int n, d; cin >> n >> d;
    for(int i = 0; i < n; i++) {
        int b, e; cin >> b >> e;
        bessie.push_back(pieB{b, e});
        orig_pos.push_back(i);
    }
    for(int i = 0; i < n; i++) {
        int b, e; cin >> b >> e;
        elsie.push_back(pieE{b, e});
    }
    sort(orig_pos.begin(), orig_pos.end(), comp3);
    sort(bessie.begin(), bessie.end());
    sort(elsie.begin(), elsie.end());
    queue<State> q;
    for(int i = 0; i < n; i++) {
        if (bessie[i].els == 0) {
            q.push(State{i, 1});
        }
        if (elsie[i].bes == 0) {
            q.push(State{n + i, 1});
        }
    }
    while (!q.empty()) {
        State s = q.front();
        q.pop();
        if (values[s.idx] != 0 && values[s.idx] <= s.dist) {
            continue;
        }
        values[s.idx] = s.dist;
        if (s.idx < n) {
            int low = lower_bound(elsie.begin(), elsie.end(), pieE{bessie[s.idx].bes - d, 0}) - elsie.begin();
            int high = lower_bound(elsie.begin(), elsie.end(), pieE{bessie[s.idx].bes, 0}) - elsie.begin();
            if (low == n || elsie[low].bes > bessie[s.idx].bes) {
                continue;
            }
            if (high == n || elsie[high].bes > bessie[s.idx].bes) {
                high--;
            }
            for(int i = low; i <= high; i++) {
                if (values[i + n] == 0) {
                    q.push(State{i + n, s.dist + 1});
                }
            }
        }
        else {
            int newIdx = s.idx - n;
            int low = lower_bound(bessie.begin(), bessie.end(), pieB{0, elsie[newIdx].els - d}) - bessie.begin();
            int high = lower_bound(bessie.begin(), bessie.end(), pieB{0, elsie[newIdx].els}) - bessie.begin();
            if (low == n || bessie[low].els > elsie[newIdx].els) {
                continue;
            }
            if (high == n || bessie[high].els > elsie[newIdx].els) {
                high--;
            }
            for(int i = low; i <= high; i++) {
                if (values[i] == 0) {
                    q.push(State{i, s.dist + 1});
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        answer[orig_pos[i]] = values[i];
    }
    for(int i = 0; i < n; i++) {
        if (answer[i] == 0) {
            cout << -1 << endl;
        }
        else {
            cout << answer[i] << endl;
        }
    }
}