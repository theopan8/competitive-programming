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
#include <iterator>
using namespace std;
#define ll long long
map<int, int> one;
map<int, map<int, int> > two;
map<int, map<int, map<int, int> > > three;
map<int, map<int, map<int, map<int, int> > > > four;
map<int, map<int, map<int, map<int, map<int, int> > > > > five;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    //freopen("cowpatibility.in", "r", stdin);
    //freopen("cowpatibility.out", "w", stdout);
    int n; cin >> n;
    ll total = 0;
    for(int i = 0; i < n; i++) {
        int a, b, c, d, e; cin >> a >> b >> c >> d >> e;
        vector<int> list;
        list.push_back(a); list.push_back(b); list.push_back(c); list.push_back(d); list.push_back(e);
        sort(list.begin(), list.end());
        ll ones = 0;
        ll twos = 0;
        ll threes = 0;
        ll fours = 0;
        ll fives = 0;
        for(int j = 0; j < 5; j++) {
            ones += one[list[j]];
            one[list[j]] += 1;
        }
        for(int j = 0; j < 5; j++) {
            for(int k = j + 1; k < 5; k++) {
                twos += two[list[j]][list[k]];
                two[list[j]][list[k]] += 1;
            }
        }
        for(int j = 0; j < 5; j++) {
            for(int k = j + 1; k < 5; k++) {
                for(int h = k + 1; h < 5; h++) {
                    threes += three[list[j]][list[k]][list[h]];
                    three[list[j]][list[k]][list[h]] += 1;
                }
            }
        }
        for(int j = 0; j < 5; j++) {
            for(int k = j + 1; k < 5; k++) {
                for(int h = k + 1; h < 5; h++) {
                    for(int m = h + 1; m < 5; m++) {
                        fours += four[list[j]][list[k]][list[h]][list[m]];
                        four[list[j]][list[k]][list[h]][list[m]] += 1;
                    }
                }
            }
        }
        for(int j = 0; j < 5; j++) {
            for(int k = j + 1; k < 5; k++) {
                for(int h = k + 1; h < 5; h++) {
                    for(int m = h + 1; m < 5; m++) {
                        for(int s = m + 1; s < 5; s++) {
                            fives += five[list[j]][list[k]][list[h]][list[m]][list[s]];
                            five[list[j]][list[k]][list[h]][list[m]][list[s]] += 1;
                        }
                    }
                }
            }
        }
        total += fives - fours + threes - twos + ones;
    }
    cout << n * (n - 1) / 2 - total << endl;
}