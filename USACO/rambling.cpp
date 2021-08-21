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
using namespace std;

double round2 (long double value) {
    value *= 100;
    int new_val = round(value);
    double ans = (double)1.00*new_val/100.00;
    return (ans + 0.00);
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    long double total = 0;
    for(int i = 0; i < n; i++) {
        string name; double r; int d; cin >> name >> r >> d;
        total += (d - ((1.0)*d/r));
    }
    cout << (double)round2(total)*100.00/100 << endl;
}
