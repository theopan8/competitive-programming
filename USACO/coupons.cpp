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
#define ll long long
#define maxn 50010
#define int long long
set<pii> cows_p;
set<pii> cows_c;
vector<pii> cows;
main() {
    ios_base::sync_with_stdio(0);
    int n, k, m; cin >> n >> k >> m;
    for(int i = 0; i < n; i++) {
        int p, c; cin >> p >> c;
        cows_p.insert(pii(p,i));
        cows_c.insert(pii(c,i));
        cows.push_back(pii(p, c));
    }
    int count_c = 0;
    auto ind_p = cows_p.begin();
    auto ind_c = cows_c.begin();
    int sum = 0;
    int num_cows = 0;
    while (true) {
        if (ind_p != cows_p.end()) {
            if (ind_c != cows_c.end()) {
                if ((*ind_p).first > (*ind_c).first) {
                    if (count_c < k) {
                        count_c += 1;
                        sum += (*ind_c).first;
                        if (sum > m) {
                            break;
                        }
                        ind_c++;
                        num_cows += 1;
                        cows_p.erase(cows_p.find(pii(cows[(*ind_c).second].first,(*ind_c).second)));
                    }
                    else {
                        sum += (*ind_p).first;
                        if (sum > m) {
                            break;
                        }
                        ind_p++;
                        num_cows += 1;
                        cows_c.erase(cows_c.find(pii(cows[(*ind_p).second].second,(*ind_p).second)));
                    }
                }
                else {
                    sum += (*ind_p).first;
                    if (sum > m) {
                        break;
                    }
                    ind_p++;
                    num_cows += 1;
                    cows_c.erase(cows_c.find(pii(cows[(*ind_p).second].second,(*ind_p).second)));
                }
            }
            else {
                sum += (*ind_p).first;
                if (sum > m) {
                    break;
                }
                ind_p++;
                num_cows += 1;
            }
        }
        else {
            if (ind_c != cows_c.end()) {
                if (count_c < k) {
                    count_c += 1;
                    sum += (*ind_c).first;
                    if (sum > m) {
                        break;
                    }
                    ind_c++;
                    num_cows += 1;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
    }
    cout << num_cows << endl;
}