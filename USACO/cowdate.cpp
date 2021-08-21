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
const int maxn = 1000010;
struct state {
    double prob, probN;
};
double p[maxn];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    freopen("cowdate.in", "r", stdin);
    freopen("cowdate.out", "w", stdout);
    int n; cin >> n;
    double maxProb = 0;
    for(int i = 0; i < n; i++) {
        double x; cin >> x;
        p[i] = x/(double)1000000;
        maxProb = max(maxProb, p[i]);
    }
    state currState = state{p[0], 1 - p[0]};
    int low = 0; int high = 0;
    while (high < n - 1) {
        high++;
        double prevProb = currState.prob;
        currState.prob += p[high] * (currState.probN - currState.prob);
        currState.probN *= (1 - p[high]);
        maxProb = max(maxProb, currState.prob);
        if (currState.prob < prevProb) {
            while (low < high) {
                prevProb = currState.prob;
                currState.probN /= (1 - p[low]);
                currState.prob -= currState.probN * p[low];
                currState.prob /= (1 - p[low]);
                maxProb = max(maxProb, currState.prob);
                low++;
                if (currState.prob < prevProb) {
                    break;
                }
            }
        }
    }
    cout << round(floor(maxProb * (double)1000000)) << endl;
}