/**
 * Author: Sathvik Kuthuru
 * Description: Given a list of query nodes, it will construct
 * the virtual tree with the query nodes and pairwise lca's.
 * Need to compute euler tour beforehand (not shown) 
 */

bool cmp(int u, int v) { return st[u] < st[v]; }

int virtual_tree(vi vert) {
    sort(all(vert), cmp);

    int k = sz(vert);
    for(int i = 0; i < k - 1; i++) {
        int new_vertex = lca(vert[i], vert[i + 1]);
        vert.pb(new_vertex);
    }

    sort(all(vert), cmp);
    vert.erase(unique(all(vert)), vert.end());

    for(int v : vert) {
        adj_vt[v].clear();
        dp[v] = -1;
    }

    vi stk;
    stk.pb(vert[0]);
    for(int i = 1; i < sz(vert); i++) {
        int u = vert[i];
        while(sz(stk) >= 2 && !upper(stk.back(), u)) {
            adj_vt[stk[sz(stk) - 2]].pb(stk.back());
            stk.pop_back();
        }

        stk.pb(u);
    }

    while(sz(stk) >= 2) {
        adj_vt[stk[sz(stk) - 2]].pb(stk.back());
        stk.pop_back();
    }

    return stk[0];
}
