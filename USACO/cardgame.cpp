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
const int maxn = 50001;
int usedCards[2*maxn];
vector<int> bessieCards;
vector<int> elsieCards;
int main() {
    //freopen("cardgame.in", "r", stdin);
    //freopen("cardgame.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        usedCards[x] = 1;
        elsieCards.push_back(x);
    }
    sort(elsieCards.begin(), elsieCards.end());
    for(int i = 1; i <= 2*n; i++) {
        if (usedCards[i] == 0) {
            bessieCards.push_back(i);
        }
    }
    int total = 0;
    for(int i = 0; i < n/2; i++) {
        if (total ) {

        }
    }
}