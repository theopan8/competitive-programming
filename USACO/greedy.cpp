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
#define maxn 100010
vector<int> cows;
int counter[maxn];
int n;
bool checker (int ind) {
    for(int i = 0; i <= n; i++) {
        counter[i] = 0;
    }
    for(int i = 0; i < ind; i++) {
        counter[cows[i]] += 1;
    }
    int curr = 0;
    for(int i = 1; i <= n; i++) {
        curr += counter[i-1];
        if (curr >= i) {
            return true;
        }
    }
    return false;
}
int main() {
    //freopen("greedy.in", "r", stdin);
    //freopen("greedy.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        int c; cin >> c;
        cows.push_back(n - 1 - c);
    }
    int s = 0;
    int e = n-1;
    while (s < e-1) {
        int average = (s+e)/2;
        if (checker(average)) {
            e = average;
        }
        else {
            s = average;
        }
    }
    if (checker(s)) {
        cout << n - s << endl;
    }
    else if (checker(e)) {
        cout << n - e << endl;
    }
    else {
        cout << 0 << endl;
    }
}