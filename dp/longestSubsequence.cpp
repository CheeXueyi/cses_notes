#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i, n, m) for (int i = n; i <= m; i++)
#define rep(n) for (int _ = 0; _ < n; _++)
typedef pair<long long, long long> pll;

const int INF = 1e9 + 7;
int n, m;
const int N = 1100;
const int M = 1100;
int A[N];
int B[M];

ll dp[N][M];
ll matchVal[N][M];
pll previ[N][M];
// let dp[i][j] = longest subsequence of prefix of length i of A and prefix of length j of B
int main() {
    cin >> n >> m;
    f(i, 1, n) {
        cin >> A[i];
    }
    f(i, 1, m) {
        cin >> B[i];
    }

    f(i, 1, n) {
        f(j, 1, m) {
            dp[i][j] = dp[i-1][j];
            matchVal[i][j] = -1;
            previ[i][j] = {i-1, j};

            if (dp[i][j-1] > dp[i][j]) {
                dp[i][j] = dp[i][j-1];
                matchVal[i][j] = -1;
                previ[i][j] = {i, j-1};
            }
            if (A[i] == B[j] && dp[i-1][j-1] + 1 > dp[i][j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                matchVal[i][j] = A[i];
                previ[i][j] = {i-1, j-1};
            }
        }
    }
    cout << dp[n][m] << "\n";
    int i = n; int j = m;
    vector<int> subsequence;
    while (i > 0 && j > 0) {
        if (matchVal[i][j] != -1) {
            subsequence.push_back(matchVal[i][j]);
        }

        pll p = previ[i][j];
        i = p.first; j = p.second;
    }
    for (int i = subsequence.size() - 1; i >= 0; i--) {
        cout << subsequence[i] << " ";
    }
    cout << "\n";
}