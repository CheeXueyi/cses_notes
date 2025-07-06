#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int A = 600;
const int B = 600;
const int INF = 1e9 + 7;

int memo[A][B];

int dp(int a, int b) {
    if (a == b) {
        return 0;
    }
    if (a == 0 || b == 0) {
        return INF;
    }

    if (memo[a][b] != 0) {
        return memo[a][b];
    }

    if (memo[b][a] != 0) {
        return memo[b][a];
    }

    int currBest = INF;
    for (int i = 1; i < a; i++) {
        currBest = min(currBest, dp(a-i, b) + dp(i, b) + 1);
    }
    for (int j = 1; j < b; j++) {
        currBest = min(currBest, dp(a, b-j) + dp(a, j) + 1);
    }

    memo[a][b] = currBest;
    return currBest;
}

int main() {
    // for (int i = 0; i < A; i++) {
    //     for (int j = 0; j < B; j++) {
    //         memo[A][B] = INF;
    //     }
    // }
    int a, b;
    cin >> a >> b;

    cout << dp(a, b) << "\n";
}