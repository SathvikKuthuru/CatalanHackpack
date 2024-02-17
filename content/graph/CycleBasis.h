/**
 * Source: UCF Catalan
 * Description: Xor basis of cycles on an undirected
 * weighted graph. The example below finds the maximum
 * xor of some subset of cycles
 */

struct edge {
	ll u, v, w;
};

int n, m;
vector<edge> edges;
vector<vector<ll>> treeAdjList, treeAdjWeights;
vector<ll> parents, depths, xors;

void dfs(ll at, ll par, ll depth, ll prefixXor) {
	parents[at] = par;
	depths[at] = depth;
	xors[at] = prefixXor;
	auto &curr = treeAdjList[at];
	for(ll i = 0; i < curr.size(); ++i) {
        ll neigh = curr[i];
		if (neigh == par) continue;
		dfs(neigh, at, depth + 1, prefixXor ^ treeAdjWeights[at][i]);
	}
}

bool addToBasis(vector<ll> &basis, ll x) {
	for(ll i = 62; i >= 0; --i)
		if (x & 1LL << i) x ^= basis[i];
	if (x == 0) return false;
	basis[63 - __builtin_clzll(x)] = x;
	return true;
}

ll solve() {
	cin >> n >> m;
    edges = vector<edge>();
    for (ll i = 0; i < m; ++i) {
        edge e; cin >> e.u >> e.v >> e.w;
        e.u--, e.v--;
        edges.push_back(e);
    }

    treeAdjList = vector<vector<ll>>(n);
    treeAdjWeights = vector<vector<ll>>(n);
    DSU dsu(n);
    vector<edge> leftovers;
    for (edge &e : edges) {
        if (dsu.join(e.u, e.v)) {
            treeAdjList[e.u].push_back(e.v);
            treeAdjWeights[e.u].push_back(e.w);
            treeAdjList[e.v].push_back(e.u);
            treeAdjWeights[e.v].push_back(e.w);
        }
        else {
            leftovers.push_back(e);
        }
    }

    parents = vector<ll>(n);
    depths = vector<ll>(n);
    xors = vector<ll>(n);
    dfs(0, -1, 0, 0);

    vector<ll> basis(64);
    for (edge &e : leftovers) {
        ll xr = xors[e.u] ^ xors[e.v] ^ e.w;
        addToBasis(basis, xr);
    }

    ll ans = 0;
    for (ll i = 62; i >= 0; --i)
        ans = max(ans, ans ^ basis[i]);
}
