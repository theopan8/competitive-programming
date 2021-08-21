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
vector<int> num;
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    priority_queue<int> q;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        num.push_back(x);
        q.push(-x);
    }
    sort(num.begin(), num.end());
    if (n == 1) {
        cout << 0 << endl;
    }
    else if (n == 2) {
        cout << num[0] + num[1] << endl;
    }
    else {
        int time = num[0] + num[1];
        q.pop(); q.pop(); q.push(-(num[0] + num[1]));
        for(int i = 2; i < n; i++) {
            int x = q.top();
            q.pop();
            int y = q.top();
            q.pop();
            time -= x+y;
            q.push(x+y);
        }
        cout << time << endl;
    }
}
