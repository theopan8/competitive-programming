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
map<char, ll> phat;
multiset<string> phet;
string maskes (string s) {
    string total = "";
    for(int i = 0; i < s.length()-1; i++) {
        if (phat[s[i]] > phat[s[i+1]]) {
            total += "1";
        }
        else {
            total += "0";
        }
    }
    return total;
}
int main() {
    ios_base::sync_with_stdio(0);
    int q; cin >> q;
    phat['0'] = 0;
    phat['1'] = 1;
    phat['2'] = 2;
    phat['3'] = 3;
    phat['4'] = 4;
    phat['5'] = 5;
    phat['6'] = 6;
    phat['7'] = 7;
    phat['8'] = 8;
    phat['9'] = 9;
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        if (x == 1) {
            string y; cin >> y;
            phet.insert(maskes(y));
        }
        else if (x == 2) {
            string y; cin >> y;
            phet.erase(y);
        }
        else {
            string y; cin >> y;
            cout << phet.count(y) << endl;
        }
    }
}