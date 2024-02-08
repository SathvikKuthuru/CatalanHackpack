// Arithmetic Progression Range Add and Range Sum Query
// Can be modified to Range Max Query

struct ArithTree {
    ll base = 0, diff = 0, val = 0;
    ArithTree *l = nullptr;
    ArithTree *r = nullptr;
    int tl, tr;

    ArithTree(int ll, int rr) : tl(ll), tr(rr) {
        if(tl != tr) {
            int mid = (tl + tr) / 2;
            l = new ArithTree(tl, mid);
            r = new ArithTree(mid + 1, tr);
        }
    }

    inline ll sum(ll x) {
        return x * (x + 1) / 2;
    }

    void apply(ll b, ll d) {
        base += b;
        diff += d;
        val += (tr - tl + 1) * b + sum(tr - tl) * d;
    }

    void push() {
        int mid = (tl + tr) / 2;
        l->apply(base, diff);
        r->apply(base + (mid + 1 - tl) * diff, diff);
        base = 0;
        diff = 0;
    }

    void pull() {
        val = l->val + r->val;
    }

    void update(int ql, int qr, ll& b, ll d) {
        if(tr < ql || tl > qr) return;
        if(ql <= tl && tr <= qr) {
            apply(b, d);
            b += d * (tr - tl + 1);
            return;
        }
        push();
        l->update(ql, qr, b, d);
        r->update(ql, qr, b, d);
        pull();
    }

    ll query(int ql, int qr) {
        if(tr < ql || tl > qr) return 0;
        if(ql <= tl && tr <= qr) return val;
        push();
        ll ret = l->query(ql, qr) + r->query(ql, qr);
        pull();
        return ret;
    }
};
