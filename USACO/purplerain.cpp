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
#define maxn 100010
vector<int> str;
vector<int> str2;
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    string s; cin >> s;
    int n = s.length();
    int curr = 0;
    str.push_back(0);
    str2.push_back(0);
    for(int i = 0; i < n; i++) {
        if (s[i] == 'B') {
            curr += 1;
            str.push_back(curr);
            str2.push_back(curr);
        }
        else {
            curr -= 1;
            str.push_back(curr);
            str2.push_back(curr);
        }
    }
    sort(str.begin(), str.end());
    int min = str[0];
    int max = str[str.size()-1];
    int min_index = -1;
    int max_index = -1;
    for(int i = 0; i < str.size(); i++) {
        if (min_index != -1) {
            if (str2[i] == max) {
                max_index = i;
                break;
            }
            continue;
        }
        if (str2[i] == min) {
            min_index = i;
        }
    }
    if (min_index == -1 || max_index == -1) {
        min_index = numeric_limits<int>::max();
        max_index = numeric_limits<int>::max();
    }
    //cout << min_index + 1 << " " << max_index << endl;
    int min_index2 = -1;
    int max_index2 = -1;
    for(int i = 0; i < str.size(); i++) {
        if (max_index2 != -1) {
            if (str2[i] == min) {
                min_index2 = i;
                break;
            }
            continue;
        }
        if (str2[i] == max) {
            max_index2 = i;
        }
    }
    if (min_index2 == -1 || max_index2 == -1) {
        min_index2 = numeric_limits<int>::max();
        max_index2 = numeric_limits<int>::max();
    }
    //cout << max_index2+1 << " " << min_index2 << endl;
    if (max_index2 < min_index) {
        cout << max_index2+1 << " " << min_index2 << endl;
    }
    else if (max_index2 > min_index) {
        cout << min_index+1 << " " << max_index << endl;
    }
    else {
        if (max_index < min_index2) {
            cout << min_index+1 << " " << max_index << endl;
        }
        else {
            cout << max_index2+1 << " " << min_index2 << endl;
        }
    }
}
