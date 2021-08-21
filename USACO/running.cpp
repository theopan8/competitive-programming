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
#define ll long long
#define MaxVal 200010
int tree[MaxVal];

int read(int idx){
    int sum = 0;
    while (idx > 0){
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int idx ,int val){
    while (idx <= MaxVal){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}
int main() {
    //freopen("runaway.in", "r", stdin);
    //freopen("runaway.out", "w", stdout);
    //calculate # of laps for cows (f(i))
    //number of crossings is floor(f(i)-f(j)) (take all sum)
    //sort the f(i)
    //then f(i)*(i-1) - prefix[i] will give us answer
    //now we have to deal with the floor
    //if decimal part of f(i) is greater than decimal part of f(j)
    //we have floor(f(i)-f(j)) = floor(f(i)) - floor(f(j))
    //else subtract 1
    //now at f(i), we have to count number of stuff with smaller decimal part using BIT
}
