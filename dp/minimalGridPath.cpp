#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

const int INF = 1e9 + 7;

const int N = 3100;
// we could do bfs, but at each level, we only keep track of the branches that give the smallest character

int n;
string S[3100];
// smallest char at each level
char smallestChar[2 * N];
bool seen[N][N];

int main() {
    fill(smallestChar, smallestChar + (2 * N), 'Z' + 1); 
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }
    
    // (i, j)
    int level = 0;
    vector<pll> currCand = {{0, 0}};
    vector<pll> nxtCand;
    for (int lvl = 0; lvl <= 2 * (n-1); lvl++) {
        // get min in char in current level
        for (pll &cand : currCand) {
            int i = cand.first; int j = cand.second;
            assert(level == i + j);
            smallestChar[level] = min(smallestChar[level], S[i][j]);
        }

        for (pll &cand: currCand) {
            int i = cand.first; int j = cand.second;
            if (S[i][j] > smallestChar[level]) {
                continue;
            }
            
            if (i < n - 1 && !seen[i + 1][j]) {
                nxtCand.push_back({i+1, j});
                seen[i+1][j] = true;
            }

            if (j < n-1 && !seen[i][j + 1]) {
                nxtCand.push_back({i, j+1});
                seen[i][j+1] = true;
            }
        }

        currCand = nxtCand;
        nxtCand.clear();
        level++;
    }

    for (int i = 0; i <= 2 * (n-1); i++) {
        cout << smallestChar[i];
    }
    cout << "\n";
}