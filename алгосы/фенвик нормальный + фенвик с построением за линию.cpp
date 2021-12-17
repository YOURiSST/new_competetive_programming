struct Fenwick {
    int n;
    vi t;
    Fenwick(const vi& a) {
        n = sz(a);
        t.resize(n); // t[i] = sum[i & (i + 1), i]
        for (int i = 0; i < n; ++i) {
            update(i, a[i]);
        }
    }
    void update(int i, int x) {
        for (int r = i; r < n; r |= (r + 1)) {
            t[r] += x;
        }
    }
    int get_sum(int rq) {
        int res = 0;
        for (int r = rq; r >= 0; (r &= (r + 1)) -= 1) {
            res += t[r];
        }
        return res;
    }
    
    int get_sum(int l, int r) {
        return get_sum(r) - get_sum(l - 1);
    }
};



//////////
struct Fenwick {
    int n;
    vi t;
    Fenwick(const vi& a) {
        n = sz(a);
        vi pref(n + 1);
        t.resize(n); // t[i] = sum[i & (i + 1), i]
        pref[0] = 0;
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + a[i];
        }
        for (int i = 0; i < n; ++i) {
            t[i] = pref[i + 1] - pref[i & (i + 1)];
        }
        
    }
    void update(int i, int x) {
        for (int r = i; r < n; r |= (r + 1)) {
            t[r] += x;
        }
    }
    int get_sum(int rq) {
        int res = 0;
        for (int r = rq; r >= 0; (r &= (r + 1)) -= 1) {
            res += t[r];
        }
        return res;
    }
    
    int get_sum(int l, int r) {
        return get_sum(r) - get_sum(l - 1);
    }
};
