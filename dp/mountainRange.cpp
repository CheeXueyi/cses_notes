#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const int INF = 1e9 + 7;


// let dp[i] = longest valid sequence ending at i
// for sequence to be valid, we need to have come from some previous 
// mountain that is higher than h[i]
// we also need all mountains in between to be shorter than that previous
// dp[i] = max(dp[j]) + 1, where
//      j < i
//      h[j] > h[k] for j < k <= i 
// let dp[i][j] = longest glide path in subarray i...j
// consider the max element in subarray i...j, currMax
// let k_1, k_2, ..., k_l be indices in i...j where h[k] = currMax
// then 
// dp[i][j] = 1 + max(dp[k_p + 1][k_{p + 1} - 1])
// 
// let dp[i] = max trip starting from i
// then let L_i be the largest element < i such that h[L_i] > h[i]
// also let R_i be the largest element > i such that h[R_i] > h[i]
// then, dp[i] = max(dp[L_i + 1], dp[L_i + 2], ... , dp[R_i - 1]) + 1
const int N = 200100;
int L[N];
int R[N];
int h[N];

// the number of additional nodes created can be as high as the next power of two up from N (2^17 = 131,072)
int tree[N * 4];

int nTree; // actual length of underlying array

// query the sum over [qL, qR) (0-based)
// i is the index in the tree, rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
int query(int qL, int qR, int i = 1, int cL = 0, int cR = nTree) {
  // the query range exactly matches this node's range of responsibility
  if (cL == qL && cR == qR)
    return tree[i];
  // we might need to query one or both of the children
  int mid = (cL + cR) / 2;
  int ans = 0;
  // query the part within the left child [cL, mid), if any
  if (qL < mid) ans = query(qL, min(qR, mid), i * 2, cL, mid);
  // query the part within the right child [mid, cR), if any
  if (qR > mid) ans = max(query(max(qL, mid), qR, i * 2 + 1, mid, cR), ans);
  return ans;
}

/*
 * range tree update
 */

// p is the index in the array (0-based)
// v is the value that the p-th element will be updated to
// i is the index in the tree, rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
void update(int p, int v, int i = 1, int cL = 0, int cR = nTree) {
  if (cR - cL == 1) {
    // this node is a leaf, so apply the update
    tree[i] = v;
    return;
  }
  // figure out which child is responsible for the index (p) being updated
  int mid = (cL + cR) / 2;
  if (p < mid)
    update(p, v, i * 2, cL, mid);
  else
    update(p, v, i * 2 + 1, mid, cR);
  // once we have updated the correct child, recalculate our stored value.
  tree[i] = max(tree[i*2], tree[i*2+1]);
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    h[0] = INF;
    h[n + 1] = INF;
    // calculate L
    // (index, h[index])
    vector<pll> s;
    for (int i = 0; i <= n; i++) {
        while (s.size() > 0 && s.back().second < h[i]) {
            s.pop_back();
        }
        if (i > 0) {
            L[i] = s.back().first;
            // cerr << L[i] << " ";
        }
        s.push_back({i, h[i]});
    }
    // cerr << "\n";
    // calculate R
    s.clear();
    for (int i = n + 1; i >= 1; i--) {
        while (s.size() > 0 && s.back().second < h[i]) {
            s.pop_back();
        }
        if (i <= n) {
            R[i] = s.back().first;
        }
        s.push_back({i, h[i]});
    }
    // for (int i = 1; i <= n; i++) {
    //     cerr << R[i] << " ";
    // }
    // cerr << "\n";
    nTree = n + 10;
    // (height, index)
    vector<pll> heights;
    for (int i = 1; i <= n; i++) {
        heights.push_back({h[i], i});
    }
    sort(heights.begin(), heights.end());
    int ans = 0;
    for (pll &curr: heights) {
        int i = curr.second;
        // cerr << i << " " << L[i] << " " << R[i] << "\n\t";
        int currBest = query(L[i] + 1, R[i]) + 1;
        // cerr << currBest << "\n";
        update(i, currBest);
        ans = max(ans, currBest);
    }

    cout << ans << "\n";
}