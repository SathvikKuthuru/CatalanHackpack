/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: When doing DP on intervals: $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$,
 *  one can solve intervals in increasing order of length, and search $k = p[i][j]$ for $a[i][j]$ only between $p[i][j-1]$ and $p[i+1][j]$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 *  Example of a Knuth Division code is given
 *  Consider also: LineContainer (ch. Data structures), monotone queues, ternary search.
 * Time: O(N^2)
 */

const int MAXN = 5005;
const ll INF = (ll) (1e15);
 
int n;
ll cost[MAXN], pref[MAXN];
ll dp[MAXN][MAXN];
int opt[MAXN][MAXN];
 
void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> cost[i];
    for(int i = 1; i <= n; i++) {
        pref[i] = cost[i] + pref[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            dp[i][j] = INF;
        }
    }
    for(int i = 1; i <= n; i++) {
        opt[i][i] = i;
        dp[i][i] = 0;
    }
 
    for(int j = 1; j <= n; j++) {
        for(int i = j - 1; i >= 1; i--) {
            for(int k = opt[i][j - 1]; k <= opt[i + 1][j] && k < j; k++) {
                ll curr = dp[i][k] + dp[k + 1][j] + pref[j] - pref[i - 1];
                if(curr < dp[i][j]) {
                    dp[i][j] = curr;
                    opt[i][j] = k;
                }
            }
        }
    }
 
    cout << dp[1][n] << '\n';
}
