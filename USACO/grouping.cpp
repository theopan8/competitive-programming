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
#define maxm 110
#define pii pair<int,int>
int breeds[maxm];
int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    //create a table: to[k][i] = index of ith cow of breed k (i is 0 indexed)
    //then go through all k and just check using the table
    //basically start at index 0, then check the index of the kth cow of
    //all the breeds. Then choose the smallest index and move to that index
    //keep an accumulative array of the number of previous cows we have seen
}
