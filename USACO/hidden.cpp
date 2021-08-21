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
#define maxn 200010
int n;
string T = "";
int RA[maxn], tempRA[maxn];
int SA[maxn], tempSA[maxn];
int c[maxn];
int Phi[maxn];
int PLCP[maxn];
int LCP[maxn];

void countingSort(int k) {
    int i, sum, maxi = max(300, n);
    memset(c, 0, sizeof c);
    for (i = 0; i < n; i++) {
        c[i+k < n ? RA[i+k] : 0]++;
    }
    for (i = sum = 0; i < maxi; i++) {
        int t = c[i]; c[i] = sum; sum += t;
    }
    for (i = 0; i < n; i++) {
        tempSA[c[SA[i]+k  < n ? RA[SA[i]+k] : 0]++] = SA[i];
    }
    for (i = 0; i < n; i++) {
        SA[i] = tempSA[i];
    }
}

void constructSA() {
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = T[i];
    for (i = 0; i < n; i++) SA[i] = i;
    for (k = 1; k < n; k <<= 1) {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for (i = 1; i < n; i++) {
            tempRA[SA[i]] =
            (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1] +k]) ? r : ++r;
 
        }
        for (i = 0; i < n;  i++) {
            RA[i] = tempRA[i];
 
        }
        if (RA[SA[n-1]] == n-1) break;
    }
}

void computeLCP() {
    int i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < n; i++) {
        Phi[SA[i]] = SA[i-1];
 
    }
    for (i = L = 0; i < n; i++) {
        if (Phi[i] == -1) {
            PLCP[i] = 0;
            continue;
        }
        while (T[i+L] == T[Phi[i]+L]) L++;
        PLCP[i] = L;
        L = max(L-1, 0);
    }
    for (i = 0; i < n; i++) {
        LCP[i] = PLCP[SA[i]];
    }
}


int main() {
    //freopen("hayfeast.in", "r", stdin);
    //freopen("hayfeast.out", "w", stdout);
    int l; cin >> l;
    n = 2*l;
    for(int i = 0; i < l; i++) {
        char x; cin >> x;
        T += x;
    }
    T += T;
    //cout << T << endl;
    constructSA();
    computeLCP();
    bool done = true;
    for(int i = 0; i < l; i++) {
        if (SA[i] < l) {
            if (LCP[i] >= l) {
                continue;
            }
            else {
                done = false;
                cout << SA[i] << endl;
                break;
            }
        }
    }
    if (done) {
        cout << 0 << endl;
    }
}