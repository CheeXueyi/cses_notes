#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;
const int maxX = 1000100;
int n, x;
// dp[i] = min number of coins to get value i from starting coins
// dp[i] = min(dp[i-j] for all coin values j)
// dp[c_j] = 1 for all base coin values
int dp[maxX];
vector<int> coinValues;

int main() {
    fill(dp, dp + maxX, INF);
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        coinValues.push_back(c);
        // base cases
        dp[c] = 1;
    }

    for (int i = 1; i <= x; i++) {
        if (dp[i] != INF) {
            continue;
        }

        for (int c : coinValues) {
            if (i - c <= 0 || dp[i - c] == INF) {
                continue;
            }

            dp[i] = min(dp[i], dp[i-c] + 1);
        }
    }

    int ans = (dp[x] == INF) ? -1 : dp[x];
    cout << ans << "\n";     
}