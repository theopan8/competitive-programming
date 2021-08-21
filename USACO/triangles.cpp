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
#define pii pair<long long,long long>
#define maxn 305
#define ll long long
vector<pii> points;
ll cross(pii o, pii b, pii a) {
    return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first);
}
bool comp (int i, int j) {
    return points[i].second < points[j].second;
}
ll below[maxn][maxn];
ll ans[maxn];
int main() {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.push_back(pii(x,y));
    }
    sort(points.begin(), points.end());
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if (k == i || k == j) {
                    continue;
                }
                if (points[i].first < points[k].first && points[k].first <= points[j].first) {
                    if (cross(points[k], points[i], points[j]) > 0) {
                        //cout << "i " << points[i].first << " " << points[i].second << endl;
                        //cout << "j " << points[j].first << " " << points[j].second << endl;
                        //cout << "k " << points[k].first << " " << points[k].second << endl;
                        below[i][j] += 1;
                        below[j][i] += 1;
                    }
                }
            }
        }
    }
    /*for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << points[i].first << " " << points[i].second << endl;
            cout << points[j].first << " " << points[j].second << endl;
            cout << below[i][j] << endl;
        }
    }*/
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            for(int k = j+1; k < n; k++) {
                vector<int> temp; temp.push_back(i); temp.push_back(j); temp.push_back(k);
                sort(temp.begin(), temp.end(), comp);
                if (points[temp[2]].first >= min(points[temp[1]].first, points[temp[0]].first) && points[temp[2]].first <= max(points[temp[1]].first, points[temp[0]].first)) {
                    ans[below[temp[1]][temp[2]] + below[temp[2]][temp[0]] - below[temp[0]][temp[1]]] += 1;
                }
                else if (points[temp[1]].first >= min(points[temp[0]].first, points[temp[2]].first) && points[temp[1]].first <= max(points[temp[0]].first, points[temp[2]].first)) {
                    if (points[temp[1]].first == min(points[temp[0]].first, points[temp[2]].first)) {
                        ans[max(below[temp[0]][temp[1]] + below[temp[1]][temp[2]] - below[temp[0]][temp[2]], below[temp[0]][temp[2]] - below[temp[1]][temp[2]] - below[temp[0]][temp[1]])] += 1;
                    }
                    else {
                        ans[max(below[temp[0]][temp[1]] + below[temp[1]][temp[2]] - below[temp[0]][temp[2]], below[temp[0]][temp[2]] - below[temp[1]][temp[2]] - below[temp[0]][temp[1]] - 1)] += 1;
                    }
                }
                else {
                    if (points[temp[0]].first == min(points[temp[1]].first, points[temp[2]].first)) {
                        ans[below[temp[2]][temp[1]] - below[temp[2]][temp[0]] - below[temp[0]][temp[1]]] += 1;
                    }
                    else {
                        ans[below[temp[2]][temp[1]] - below[temp[2]][temp[0]] - below[temp[0]][temp[1]] - 1] += 1;
                    }
                }
            }
        }
    }
    for(int i = 0; i < n-2; i++) {
        cout << ans[i] << endl;
    }
}