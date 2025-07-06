#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int INF = 1e9 + 7;
int n, m;
string s1, s2;
const int N = 5100;
const int M = 5100;
ll dp[N][M];

int main() {
    cin >> s1 >> s2;
    n = s1.length();
    m = s2.length();
    // dp[i][j] = edit distance between prefix i or s1, prefix j of s2
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 && j == 0) {
                // cout << dp[i][j] << " ";
                continue;
            }
            dp[i][j] = INF;

            // deleting s1[i]
            if (i > 0) {
                dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
            }

            // deleting s2[j]
            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
            }
 
            if (i > 0 && j > 0) {
                int matchCost = 0;
                if (s1[i-1] != s2[j-1]) {
                    matchCost = 1;
                }
                // cout << i << " " << j << " " << matchCost << "\n";
                dp[i][j] = min(dp[i][j], dp[i-1][j-1] + matchCost);
            }
            
            // cout << dp[i][j] << " ";
        }
        // cout << "\n";
    }
    cout << dp[n][m] << "\n";
}