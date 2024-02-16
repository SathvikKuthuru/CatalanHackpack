/**
 * Author: Simon Lindholm, Sathvik Kuthuru
 * License: CC0
 * Source: Codeforces
 * Description: Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal)
 * optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
 * Time: O((N + (hi-lo)) \log N)
 * Status: tested on http://codeforces.com/contest/321/problem/E
 */
#pragma once

struct DP { // Modify at will:
	int lo(int ind) { return 0; }
	int hi(int ind) { return ind; }
	ll f(int ind, int k) { return dp[ind][k]; }
	void store(int ind, int k, ll v) { res[ind] = pii(k, v); }

	void rec(int L, int R, int LO, int HI) {
		if (L >= R) return;
		int mid = (L + R) >> 1;
		pair<ll, int> best(LLONG_MAX, LO);
		rep(k, max(LO,lo(mid)), min(HI,hi(mid)))
			best = min(best, make_pair(f(mid, k), k));
		store(mid, best.second, best.first);
		rec(L, mid, LO, best.second+1);
		rec(mid+1, R, best.second, HI);
	}
	void solve(int L, int R) { rec(L, R, INT_MIN, INT_MAX); }
};

// Alternate Implementation Example: Modify at will
const int MAXN = 3000;
 
vl dp_before(MAXN), dp_cur(MAXN);
vl pre(MAXN);
int m, n;
 
ll C(int i, int j) {
    ll ret = pre[j];
    if(i) ret -= pre[i - 1];
    return ret * ret;
}
 
void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;
 
    int mid = (l + r) >> 1;
    pair<long long, int> best = {LLONG_MAX, -1};
 
    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    }
 
    dp_cur[mid] = best.first;
    int opt = best.second;
 
    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
 
void solve() {
    cin >> n >> m;
 
    for(int i = 0; i < n; i++) {
        cin >> pre[i];
        if(i) pre[i] += pre[i - 1];
        dp_before[i] = C(0, i);
    }
 
    for(int i = 1; i < m; i++) {
        compute(0, n - 1, 0, n - 1);
        swap(dp_before, dp_cur);
    }
 
    cout << dp_before[n - 1] << '\n';
}
