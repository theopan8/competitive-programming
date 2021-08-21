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
#include <stack>
#include <cstring>
#include <math.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

vector<int> zvalues(string s) {
    int n = s.length();
    vector<int> z(n); z[0] = n;
    int L = 0; int R = 0;
    vector<int> left(n); vector<int> right(n);
    for(int i = 1; i < n; ++i) {
        if(i > R) {
            L = R = i;
            while(R < n && s[R-L] == s[R]) R++;
            z[i] = R - L; R--;
        }
        int k = i-L;
        if(z[k] < R-i+1) z[i] = z[k];
        else {
            L = i;
            while(R < n && s[R-L] == s[R]) R++;
            z[i] = R - L; R--;
        }
        left[i] = L;  right[i] = R;
    }
    return z;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    string s; cin >> s;
    vector<int> z = zvalues(s);
    
}