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

int main() {
    ios_base::sync_with_stdio(0);
    int x, n; cin >> x >> n;
    int coordx = 0;
    int coordy = 0;
    for(int i = 0; i < n; i++) {
        if (i % 4 == 0) {
            coordx += x;
        }
        else if (i % 4 == 1) {
            coordy -= x;
        }
        else if (i % 4 == 2) {
            coordx -= x;
        }
        else {
            coordy += x;
        }
        x += 1;
    }
    cout << coordx << " " << coordy << endl;
}
