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
struct haybale {
	int size, pos;
	bool operator < (const haybale &other) const {
		return this->size > other.size || (this->size == other.size && this->pos > other.pos);
	};
};
vector<haybale> haybales;
map<int, int> currHaybales;
map<int, map<int, int> > interval; //0 is right, 1 is left
int main() {
    ios_base::sync_with_stdio(0);
    //freopen("trapped.in", "r", stdin);
    //freopen("trapped.out", "w", stdout);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
    	int s, p; cin >> s >> p;
    	haybales.push_back(haybale{s, p});
    }
    sort(haybales.begin(), haybales.end());
    /*for(int i = 0; i < n; i++) {
    	cout << i << ": " << haybales[i].size << " " << haybales[i].pos << endl;
    }*/
    currHaybales[haybales[0].pos] = 0;
    for(int i = 1; i < n; i++) {
    	currHaybales[haybales[i].pos] = i;
    	auto low = currHaybales.find(haybales[i].pos);
    	//cout << "curr_pos: " << low->first << endl;
    	auto low_copy = low;
    	if (low == currHaybales.begin()) {
    		auto low_up = low;
    		++low_up;
    		//cout << "next: " << low_up->first << endl;
    		//cout << "dist: " << low_up->first - low->first << endl;
    		if (interval[1][low_up->first] == 0 && low_up->first - low->first <= haybales[i].size) {
    			//cout << "next: " << low_up->first - low->first << endl;
    			interval[1][low_up->first] = low_up->first - low->first;
    			interval[0][low->first] = low_up->first - low->first;
    		}
    	}
    	else if (++low_copy == currHaybales.end()) {
    		auto low_down = low;
    		--low_down;
    		//cout << "prev: " << low_down->first << endl;
    		//cout << "dist: " << low->first - low_down->first << endl;
    		if (interval[0][low_down->first] == 0 && low->first - low_down->first <= haybales[i].size) {
    			//cout << "prev: " << low->first - low_down->first << endl;
    			interval[0][low_down->first] = low->first - low_down->first;
    			interval[1][low->first] = low->first - low_down->first;
    		}
    	}
    	else {
    		auto low_up = low;
    		++low_up;
    		auto low_down = low;
    		--low_down;
    		//cout << "next: " << low_up->first << endl;
    		//cout << "prev: " << low_down->first << endl;
    		if (interval[1][low_up->first] == 0 && low_up->first - low->first <= haybales[i].size) {
    			//cout << "next: " << low_up->first - low->first << endl;
    			interval[1][low_up->first] = low_up->first - low->first;
    			interval[0][low->first] = low_up->first - low->first;
    		}
    		if (interval[0][low_down->first] == 0 && low->first - low_down->first <= haybales[i].size) {
    			//cout << "prev: " << low->first - low_down->first << endl;
    			interval[0][low_down->first] = low->first - low_down->first;
    			interval[1][low->first] = low->first - low_down->first;
    		}
    	}
    }
    int total = 0;
    for(int i = 0; i < haybales.size(); i++) {
    	total += interval[0][haybales[i].pos];
    	total += interval[1][haybales[i].pos];
    }
    cout << total / 2 << endl;
}