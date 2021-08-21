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
#define maxn 200020
#define pii pair<int,int>
#define ll long long
int n;
string T = "";
int RA[maxn], tempRA[maxn];
int SA[maxn], tempSA[maxn];
int c[maxn];
int Phi[maxn];
int PLCP[maxn];
int LCP[maxn]; //from 1 (second one of the pair) to n-1
int str_pos[maxn];
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
vector<int> dif_str;
vector<pii> str_intervals;
vector<pii> mapper;
ll ans[200020];
ll st[maxn << 2];
ll lengths[maxn];
ll temp_string[maxn];
vector<ll> previous_str;
int left (int p) {
    return (p << 1);
}
int right (int p) {
    return (p << 1) + 1;
}
void build (int p, int L, int R) {
    if (L == R) {
        st[p] = LCP[L];
    }
    else {
        build(left(p), L, (L+R)/2);
        build(right(p), (L+R)/2 + 1, R);
        st[p] = min(st[left(p)], st[right(p)]);
    }
}
ll rmq (int p, int L, int R, int i, int j) {
    if (i > R || j < L) {
        return -1;
    }
    if (L >= i && R <= j) {
        return st[p];
    }
    ll p1 = rmq(left(p), L, (L+R)/2, i , j);
    ll p2 = rmq(right(p), (L+R)/2 + 1, R, i, j);
    if (p1 == -1) {
        return p2;
    }
    if (p2 == -1) {
        return p1;
    }
    return min(p1, p2);
}
int main() {
    freopen("standingout.in", "r", stdin);
    freopen("standingout.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    int num; cin >> num;
    int curr_pos = 0;
    for(int i = 0; i < num; i++) {
        string cow; cin >> cow;
        T += cow;
        int counterr = 0;
        for(int j = 0; j < cow.size(); j++) {
            str_pos[curr_pos] = i+1;
            lengths[curr_pos] = cow.size() - counterr;
            counterr += 1;
            curr_pos += 1;
        }
        T += '$';
        curr_pos += 1;
    }
    n = T.size();
    constructSA();
    computeLCP();
    for(int i = num; i < n; i++) {
        dif_str.push_back(str_pos[SA[i]]);
    }
    int prev_str = 0;
    int curr_ind = 0;
    for(int i = 0; i < dif_str.size(); i++) {
        if (i == 0) {
            prev_str = dif_str[i];
            curr_ind = num;
            continue;
        }
        if (i == dif_str.size() - 1) {
            if (dif_str[i] == prev_str) {
                str_intervals.push_back(pii(curr_ind, i+num));
            }
            else {
                str_intervals.push_back(pii(curr_ind, i+num-1));
                str_intervals.push_back(pii(i+num, i+num));
            }
            continue;
        }
        if (dif_str[i] == prev_str) {
            continue;
        }
        else {
            str_intervals.push_back(pii(curr_ind, i+num-1));
            prev_str = dif_str[i];
            curr_ind = i+num;
        }
    }
    int phat_ind = 0;
    for(int i = num; i < n; i++) {
        if (i > str_intervals[phat_ind].second) {
            phat_ind += 1;
            mapper.push_back(pii(str_intervals[phat_ind].first, str_intervals[phat_ind].second + 1));
            continue;
        }
        mapper.push_back(pii(str_intervals[phat_ind].first, str_intervals[phat_ind].second + 1));
    }
    /*for(int i = 0; i < mapper.size(); i++) {
        cout << mapper[i].first << " " << mapper[i].second << endl;
    }*/
    for(int i = 0; i < dif_str.size(); i++) {
        if (temp_string[dif_str[i]] == 0) {
            temp_string[dif_str[i]] = num+i;
            previous_str.push_back(-1);
        }
        else {
            previous_str.push_back(temp_string[dif_str[i]]);
            temp_string[dif_str[i]] = num+i;
        }
    }
    build(1, num+1, n-1);
    for(int i = num; i < n; i++) {
        int same = previous_str[i-num];
        int phat_prev = mapper[i-num].first;
        int phat_for = mapper[i-num].second;
        if (i == num) {
            if (phat_for >= n) {
                ans[dif_str[i-num]] += lengths[SA[i]];
            }
            else {
                int minus = rmq(1, num+1, n-1, i+1, phat_for);
                ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
            }
            //cout << ans[dif_str[i-num]] << endl;
            continue;
        }
        if (i == n-1) {
            if (same != -1 && phat_prev > num) {
                int minus = max(rmq(1, num+1, n-1, same+1, i), rmq(1, num+1, n-1, phat_prev, i));
                ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
                //cout << lengths[SA[i]] - minus << endl;
            }
            else if (same != -1) {
                int minus = rmq(1, num+1, n-1, same+1, i);
                ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
                //cout << lengths[SA[i]] - minus << endl;
            }
            else if (phat_prev > num) {
                int minus = rmq(1, num+1, n-1, phat_prev, i);
                ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
                //cout << lengths[SA[i]] - minus << endl;
            }
            else {
                ans[dif_str[i-num]] += lengths[SA[i]];
                //cout << lengths[SA[i]] << endl;
            }
            continue;
        }
        if (same != -1 && phat_prev > num && phat_for < n) {
            int minus = max(rmq(1, num+1, n-1, same+1, i), max(rmq(1, num+1, n-1, phat_prev, i), rmq(1, num+1, n-1, i+1, phat_for)));
            ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
            //cout << lengths[SA[i]] - minus << endl;
        }
        else if (same != -1 && phat_prev > num) {
            int minus = max(rmq(1, num+1, n-1, same+1, i), rmq(1, num+1, n-1, phat_prev, i));
            ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
            //cout << lengths[SA[i]] - minus << endl;
        }
        else if (same != -1 && phat_for < n) {
            int minus = max(rmq(1, num+1, n-1, same+1, i), rmq(1, num+1, n-1, i+1, phat_for));
            ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
            //cout << lengths[SA[i]] - minus << endl;
        }
        else if (phat_prev > num && phat_for < n) {
            int minus = max(rmq(1, num+1, n-1, phat_prev, i), rmq(1, num+1, n-1, i+1, phat_for));
            ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
            //cout << lengths[SA[i]] - minus << endl;
        }
        else if (same != -1) {
            int minus = rmq(1, num+1, n-1, same+1, i);
            ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
            //cout << lengths[SA[i]] - minus << endl;
        }
        else if (phat_prev > num) {
            int minus = rmq(1, num+1, n-1, phat_prev, i);
            ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
            //cout << lengths[SA[i]] - minus << endl;
        }
        else if (phat_for < n) {
            int minus = rmq(1, num+1, n-1, i+1, phat_for);
            ans[dif_str[i-num]] += max(lengths[SA[i]] - minus, (ll)0);
            //cout << lengths[SA[i]] - minus << endl;
        }
        else {
            ans[dif_str[i-num]] += lengths[SA[i]];
            //cout << lengths[SA[i]] << endl;
        }
    }
    for(int i = 1; i <= num; i++) {
        cout << ans[i] << endl;
    }
}