struct SegTreeMin {
    int n;
    vi t, upd;
    SegTreeMin(const vi& a) {
        n = sz(a);
        t.resize(4 * n);
        upd.resize(4 * n);
        build(1, 0, n, a);
    }
    
    void build(int v, int l, int r, const vi& a) {
        if (l == r - 1) {
            t[v] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * v, l, mid, a);
        build(2 * v + 1, mid, r, a);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
    
    void update(int lq, int rq, int x) {
        update(1, 0, n, lq, rq, x);
    }
    
    void update(int v, int l, int r, int lq, int rq, int x) {
        if (r <= lq || rq <= l) {
            return;
        }
        if (lq <= l && r <= rq) {
            t[v] += x;
            upd[v] += x;
            return;
        }
        push(v);
        int mid = (l + r) / 2;
        update(2 * v, l, mid, lq, rq, x);
        update(2 * v + 1, mid, r, lq, rq, x);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
    
    void push(int v) {
        t[2 * v] += upd[v];
        t[2 * v + 1] += upd[v];
        upd[2 * v] += upd[v];
        upd[2 * v + 1] += upd[v];
        upd[v] = 0;
    }
    
    int get_min(int lq, int rq) {
        return get_min(1, 0, n, lq, rq);
    }
    
    int get_min(int v, int l, int r, int lq, int rq) {
        if (r <= lq || rq <= l) {
            return INF;
        }
        if (lq <= l && r <= rq) {
            return t[v];
        }
        push(v);
        int mid = (l + r) / 2;
        return min(get_min(2 * v, l, mid, lq, rq), get_min(2 * v + 1, mid, r, lq, rq));
    }
};









