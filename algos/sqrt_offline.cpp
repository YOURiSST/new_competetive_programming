struct UpdQ {
    int l, r, x;
};

struct OfflineSQRT {
    int n;
    vector<int> a;
    vector<int> ps; // префиксные суммы
    vector<UpdQ> upds;
    
    OfflineSQRT(const vector<int>& a_) : a(a_) {
        n = a.size();
        ps.resize(n + 1);
        
        for (int i = 0; i < n; ++i) {
            ps[i + 1] = ps[i] + a[i];
        }
    }
    
    int get_sum(int lq, int rq) {
        int res = ps[rq + 1] - ps[lq];
        
        for (auto [l, r, x] : upds) {
            int cur_l = max(lq, l);
            int cur_r = min(rq, r);
            res += x * max(0, cur_r - cur_l + 1);
        }
        
        return res;
    }
    
    void update(int lq, int rq, int x) {
        upds.push_back({lq, rq, x});
        
        if (upds.size() > BLOCK) {
            vector<int> deltas(n + 1);
            
            while (!upds.empty()) {
                deltas[upds.back().l] += upds.back().x;
                deltas[upds.back().r + 1] -= upds.back().x;
                upds.pop_back();
            }
            
            int delta = 0;
            
            for (int i = 0; i < n; ++i) {
                delta += deltas[i];
                a[i] += delta;
                ps[i + 1] = ps[i] + a[i];
            }
        }
    }
};