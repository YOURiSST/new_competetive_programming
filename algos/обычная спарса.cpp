struct Sparse {
    vi logs;
    vvi s;
    Sparse(const vi& a) {
        logs.resize(sz(a) + 1);
        logs[0] = 0;
        logs[1] = 0;
        for (int i = 2; i < sz(a) + 1; ++i) {
            if ((2 << logs[i - 1]) == i) {
                logs[i] = logs[i - 1] + 1;
            } else {
                logs[i] = logs[i - 1];
            }
        }
        s.resize(logs[sz(a)] + 1, vi(sz(a)));
        for (int i = 0; i < sz(a); ++i) {
            s[0][i] = a[i];
        }
        for (int l = 1; l < logs[sz(a)] + 1; ++l) {
            for (int i = 0; i + (1 << l) < sz(a) + 1; ++i) {
                s[l][i] = min(s[l - 1][i], s[l - 1][i + (1 << (l - 1))]);
            }
        } 
    }  
    
    
    int get_min(int lq, int rq) {
        dbg(lq, rq, logs[rq - lq]);
        return min(s[logs[rq - lq]][lq], s[logs[rq - lq]][rq - (1 << (logs[rq - lq]))]);
    }
    
};