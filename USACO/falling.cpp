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
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<int, pair<ll, ll> > pip;
typedef pair<int, pair<int, pair<ll, ll> > > ppp;
#define MAXN 3010
ll a[MAXN];
int b[MAXN];
vector<pip> graph[MAXN];
int n;
ll gcd(int i, int j) {
    if (i % j == 0) return j;
    return gcd(j, i % j);
}
pii dist[MAXN];
void dijsktra(int u) {
    priority_queue<pip> pq;
    pq.push(ppp(u, ));
}
int main() {
    //freopen("falling.in", "r", stdin);
    //freopen("falling.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if (a[j] - a[i] < 0) continue;
            else {
                ll x = gcd(max(a[j] - a[i], (ll)j - i), min(a[j] - a[i], (ll)j - i));
                graph[i].push_back(pip(j, pii((a[j] - a[i])/x, (j - i)/x)));
                graph[j].push_back(pip(i, pii((a[j] - a[i])/x, (j - i)/x)));
            }
        }
    }
    /*for(int i = 1; i <= n; i++) {
        cout << i << endl;
        for(pip j : graph[i]) {
            cout << j.first << " " << j.second.first << "/" << j.second.second << endl;
        }
    }*/
    for(int i = 1; i <= n; i++) {
        /*for(int j = 1; j <= n; j++) {
            cout << dist[j].first << "/" << dist[j].second << " ";
        }
        cout << endl;*/
        for(int j = 1; j <= n; j++) {
            dist[j] = pii(-1, 0);
        }
        if (dist[b[i]].first == -1) cout << -1 << endl;
        else cout << dist[b[i]].first << "/" << dist[b[i]].second << endl;
        for(int j = 1; j <= n; j++) {
            dist[j] = pii(0, 0);
        }
    }
}