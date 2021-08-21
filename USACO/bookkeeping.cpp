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
#define maxn 1010
char book[maxn][maxn];
int num_char[27];
int ans[27];
int w, h;
int a,b; 
void update () {
    for(int i = 0; i < 26; i++) {
        if (num_char[i] > ans[i]) {
            ans[i] = num_char[i];
        }
    }
}
void clear () {
    for(int i = 0; i < 26; i++) {
        num_char[i] = 0;
    }
}
int main() {
    //freopen("empty.in", "r", stdin);
    //freopen("empty.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin >> w >> h;
    cin >> a >> b;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            char x; cin >> x;
            book[i][j] = x;
        }
    }
    //book[height][width]
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            num_char[book[j][i]-'a'] += 1;
        }
    }
    update();
    for(int i = 0; i < h-b+1; i++) {
        for(int j = 0; j < w-a+1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (j > 0) {
                for(int k = i; k < i + b; k++) {
                    num_char[book[k][j-1]-'a'] -= 1;
                }
                for(int k = i; k < i+b; k++) {
                    num_char[book[k][j+a-1] - 'a'] += 1;
                }
                update();
            }
            else {
                for(int k = i; k < i+b; k++) {
                    for(int z = j; z < a; z++) {
                        num_char[book[k][z] - 'a'] += 1;
                    }
                }
                update();
            }
            
        }
        for(int j = 0; j < 26; j++) {
            num_char[j] = 0;
        }
    }
    for(int i = 0; i < 26; i++) {
        cout << ans[i] << endl;
    }
}
