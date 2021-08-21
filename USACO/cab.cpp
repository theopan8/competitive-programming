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
#include <stack>
using namespace std;
vector<int> graph[29];
vector<string> words;
string let = "abcdefghijklmnopqrstuvwxyzzzzzz";
int visited[29];
vector<int> topsort;
set<int> counter;
int indexe[29];
char last;
string ans;
void topological (int start) {
    visited[start] = 1;
    for(int i = 0; i < graph[start].size(); i++) {
        if (visited[graph[start][i]] == 0) {
            topological(graph[start][i]);
        }
    }
    topsort.push_back(start);
}
void dfs (int start, string curr) {
    string now = curr + let[start-1];
    for(int i = 0; i < graph[start].size(); i++) {
        dfs(graph[start][i], now);
    }
    if (graph[start].size() == 0) {
        if (now.length() == last - 'a' + 1) {
            ans = now;
        }
    }
}
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin >> last;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        string x; cin >> x;
        words.push_back(x);
    }
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < min(words[i].length(), words[i+1].length()); j++) {
            if (words[i][j] != words[i+1][j]) {
                graph[words[i+1][j]-'a'+1].push_back(words[i][j]-'a'+1);
                counter.insert(words[i][j]-'a'+1);
                break;
            }
            if (j == min(words[i].length(), words[i+1].length()) - 1) {
                if (max(words[i].length(), words[i+1].length()) == words[i].length() && words[i].length() != words[i+1].length()) {
                    cout << 1 << endl;
                    return 0;
                }
            }
        }
    }
    //checks if it is complete
    if (counter.size() < last - 'a') {
        cout << 0 << endl;
        return 0;
    }
    for(int i = 1; i <= last-'a'+1; i++) {
        if (visited[i] == 0) {
            topological(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    for(int i = 1; i <= last-'a'+1; i++) {
        indexe[topsort[i]] = i;
    }
    bool bad = false;
    for(int i = 1; i <= last-'a'+1; i++) {
        for(int j = 0; j < graph[i].size(); j++) {
            if (indexe[i] >= indexe[graph[i][j]]) {
                bad = true;
                break;
            }
        }
    }
    if (bad) {
        cout << 1 << endl;
        return 0;
    }
    for(int i = 1; i <= last-'a'+1; i++) {
        if (counter.count(i) == 0) {
            dfs(i, "");
            break;
        }
    }
    string answer = "";
    for(int i = ans.length() - 1; i >= 0; i--) {
        answer += ans[i];
    }
    cout << answer << endl;
}
