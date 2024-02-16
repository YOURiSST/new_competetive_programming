struct SegTreeMax {
    int n; vi t;
    SegTreeMax(int n_) {
        n = n_;
        t.resize(4 * n, 0);
    }
    int get_max(int lq, int rq) {
        return get_max(1, 0, n, lq, rq);
    }
    int get_max(int v, int l, int r, int lq, int rq) {
        if (rq <= l || r <= lq) {
            return 0;
        }
        if (lq <= l && r <= rq) {
            return t[v];   
        }
        int mid = (l + r) / 2;
        return max(get_max(2 * v, l, mid, lq, rq), get_max(2 * v + 1, mid, r, lq, rq));
    }
    void update(int i, int x) {
        update(1, 0, n, i, x);
    }
    void update(int v, int l, int r, int i, int x) {
        if (l == r - 1) {
            t[v] = x;
            return;
        }
        int mid = (l + r) / 2;
        if (i < mid) {
            update(2 * v, l, mid, i, x);
        } else {
            update(2 * v + 1, mid, r, i, x);
        }
        t[v] = max(t[2 * v], t[2 * v + 1]);
    }
};


int nvp(vi a) {
    int res = 0;
    int n = sz(a);
    vi temp = a;
    sort(all(temp));
    temp.resize(unique(all(temp)) - temp.begin());
    
    for (auto & i : a) {
        i = lower_bound(all(temp), i) - temp.begin() + 1;
    }
    a.insert(a.begin(), 0);
    vi dp(n + 1);
    dp[0] = 0;
    SegTreeMax tree(n + 1);
    dbg("3", a);
    for (int i = 1; i < n + 1; ++i) {
        dp[i] = tree.get_max(0, a[i]) + 1;
        dbg(i, a[i], tree.get_max(0, a[i]));
        tree.update(a[i], dp[i]);
        res = max(res, dp[i]);
    }
    dbg(dp);
    return res;
}