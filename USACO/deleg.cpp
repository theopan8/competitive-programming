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
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define MAXN 1000010
vector<int> graph[MAXN];
int visited[MAXN];
bool good = true;
int dfs(int u, int k) {
    visited[u] = 1;
    vector<int> nums;
    for(int v : graph[u]) {
        if (visited[v] == 0) nums.push_back(dfs(v, k));
    }
    if (nums.size() == 0) return 1;
    if (nums.size() == 1) return nums[0] + 1;
    sort(nums.begin(), nums.end());
    int idx = lower_bound(nums.begin(), nums.end(), k) - nums.begin();
    int low = idx;
    int high = nums.size() - idx;
    if (low < high) return nums[nums.size() - 1] + 1;
    if (nums.size() % 2 == 1) {
        int l = 0;
        int r = nums.size();
        bool work = false;
        while (l < r - 1) {
            int avg = (l + r) / 2;
            int s = 0;
            int e = nums.size() - 1;
            int mini = MAXN;
            while (s < e) {
                if (s == avg) s++;
                if (e == avg) e--;
                if (s < e) mini = min(mini, nums[s] + nums[e]);
                s++; e--;
            }
            if (mini >= k) {
                l = avg;
                work = true;
            }
            else r = avg;
        }
        int avg = (l + r) / 2;
        int s = 0;
        int e = nums.size() - 1;
        int mini = MAXN;
        while (s < e) {
            if (s == avg) s++;
            if (e == avg) e--;
            if (s < e) mini = min(mini, nums[s] + nums[e]);
            s++; e--;
        }
        if (mini >= k) {
            l = avg;
            work = true;
        }
        else r = avg;
        if (work) return nums[l] + 1;
        else good = false;
        return 1;
    }
    else {
        int s = 0;
        int e = nums.size() - 1;
        int mini = MAXN;
        while (s < e) {
            mini = min(mini, nums[s] + nums[e]);
            s++; e--;
        }
        if (mini < k) {
            good = false;
            return 1;
        }
        if (u == 1) return MAXN;
        if (high >= 2) {
            s = high - 2;
            e = low - 1;
            mini = MAXN;
            while (s < e) {
                mini = min(mini, nums[s] + nums[e]);
                s++; e--;
            }
            if (mini >= k) {
                return nums[nums.size() - 1] + 1;
            }
        }
        if (high >= 1) {
            int l = 0;
            int r = low;
            bool work = false;
            while (l < r - 1) {
                int avg = (l + r) / 2;
                s = 0;
                e = nums.size() - 2;
                mini = MAXN;
                while (s < e) {
                    if (s == avg) s++;
                    if (e == avg) e--;
                    if (s < e) mini = min(mini, nums[s] + nums[e]);
                    s++; e--;
                }
                if (mini >= k) {
                    l = avg;
                    work = true;
                }
                else r = avg;
            }
            int avg = (l + r) / 2;
            s = 0;
            e = nums.size() - 2;
            mini = MAXN;
            while (s < e) {
                if (s == avg) s++;
                if (e == avg) e--;
                if (s < e) mini = min(mini, nums[s] + nums[e]);
                s++; e--;
            }
            if (mini >= k) {
                l = avg;
                work = true;
            }
            else r = avg;
            if (work || low == 1) return nums[l] + 1;
        }
        return 1;
    }
}
int main() {
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    int low = 0;
    int high = n;
    while (low < high - 1) {
        int avg = (low + high) / 2;
        int val = dfs(1, avg);
        if (good && val - 1 >= avg) low = avg;
        else high = avg;
        good = true;
        memset(visited, 0, sizeof(visited));
    }
    cout << low << endl;
}