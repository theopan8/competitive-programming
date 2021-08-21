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
using namespace std;
#define mod1 1000000007
#define mod2 1000000009
#define base 29
#define inverse 758620695
#define inverse1 517241384
#define ll long long
vector<pair<ll,ll> > par_hash;
vector<ll> powers;
vector<ll> powers1;
pair<ll, ll> hash_t = make_pair(0,0);
int main() {
    //freopen("censor.in", "r", stdin);
    //freopen("censor.out", "w", stdout);
    string s; cin >> s;
    string t; cin >> t;
    ll n = s.length();
    ll n1 = t.length();
    for(int i = 0; i <= n1; i++) {
        if (i == 0) {
            powers.push_back(1);
            powers1.push_back(1);
        }
        else {
            powers.push_back((powers[i-1]*base) % mod1);
            powers1.push_back((powers1[i-1]*base) % mod2);
        }
        //cout << powers[i] << endl;
    }
    for(int i = 0; i < n1; i++) {
        hash_t = make_pair((hash_t.first + (t[i]-'a'+1)*powers[i]) % mod1, (hash_t.second + (t[i]-'a'+1)*powers1[i]) % mod2);
    }
    //cout << hash_t.first << " " << hash_t.second << endl;
    string curr_str = "";
    //cout << ('h'-'a'+1) + 29 + 29*29*('t'-'a'+1) << endl;
    for(int i = 0; i < n; i++) {
        curr_str += s[i];
        //cout << i << " " << curr_str << '\n';
        if (i <= n1 - 1) {
            if (i == 0) {
                par_hash.push_back(make_pair((s[i]-'a'+1)%mod1, (s[i]-'a'+1)%mod2));
            }
            else {
                par_hash.push_back(make_pair((par_hash[i-1].first + (s[i]-'a'+1)*powers[i])% mod1, (par_hash[i-1].second + (s[i]-'a'+1)*powers1[i])%mod2));
            }
            if (i == n1 - 1) {
                if (par_hash[i] == hash_t) {
                    par_hash.erase(par_hash.end() - n1, par_hash.end());
                    curr_str.erase(curr_str.end() - n1, curr_str.end());
                }
            }
        }
        else {
            if (par_hash.size() == 0) {
                par_hash.push_back(make_pair((s[i]-'a'+1)%mod1, (s[i]-'a'+1)%mod2));
                continue;
            }
            if (par_hash.size() < n1) {
                par_hash.push_back(make_pair((par_hash[par_hash.size()-1].first + (s[i]-'a'+1)*powers[par_hash.size()])  % mod1, (par_hash[par_hash.size()-1].second + (s[i]-'a'+1)*powers1[par_hash.size()])  % mod2));
                if (par_hash[par_hash.size()-1] == hash_t) {
                    par_hash.erase(par_hash.end() - n1, par_hash.end());
                    curr_str.erase(curr_str.end() - n1, curr_str.end());
                }
                continue;
            }
            ll value1 = (((par_hash[par_hash.size()-1].first-(curr_str[par_hash.size()-n1]-'a'+1))*inverse)%mod1 + (s[i]-'a'+1)*powers[n1-1] )% mod1;
            if (value1 < 0) {
                value1 += mod1;
            }
            ll value2 = (((par_hash[par_hash.size()-1].second-(curr_str[par_hash.size()-n1]-'a'+1))*inverse1)%mod2 + (s[i]-'a'+1)*powers1[n1-1]) % mod2;
            if (value2 < 0) {
                value2 += mod2;
            }
            pair<ll,ll> value = make_pair(value1, value2);
            par_hash.push_back(value);
            //cout << par_hash[par_hash.size()-1] << '\n';
            if (par_hash[par_hash.size()-1] == hash_t) {
                par_hash.erase(par_hash.end() - n1, par_hash.end());
                curr_str.erase(curr_str.end() - n1, curr_str.end());
            }
        }
    }
    cout << curr_str << endl;
}