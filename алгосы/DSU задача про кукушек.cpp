struct DSUShka {
    int n, comp_0, comp_1;
    vi preds, sizes, comp_types;
    DSUShka(int n) {
        preds.resize(n);
        iota(all(preds), 0);
        sizes.resize(n, 1);
        comp_types.resize(n, 0);
        comp_0 = n;
        comp_1 = 0;
    }
    
    int find_leader(int v) {
        if (v == preds[v]) {
            return v;
        } else {
            preds[v] = find_leader(preds[v]);
            return preds[v];
        }
    }
    
    void join(int x, int y) {
        x = find_leader(x);
        y = find_leader(y);
        if (x == y) {
            comp_types[x] = 1;
            comp_0 -= sizes[x];
            comp_1 += sizes[x];
        } else {
            if (comp_types[x] == comp_types[y] && comp_types[x] == 0) {
                if (sizes[x] >= sizes[y]) swap(x, y);
                preds[x] = y;
                sizes[y] += sizes[x];
            } else if (comp_types[x] == 1 && comp_types[y] == 0) {
                comp_1 += sizes[y];
                comp_0 -= sizes[y];
                
                if (sizes[x] >= sizes[y]) swap(x, y);
                preds[x] = y;
                sizes[y] += sizes[x];
                comp_types[y] = 1;
            } else {
                comp_1 += sizes[x];
                comp_0 -= sizes[x];
                
                if (sizes[x] >= sizes[y]) swap(x, y);
                preds[x] = y;
                sizes[y] += sizes[x];
                comp_types[y] = 1;
            }
        }
    }
    int get_num(int x) {
        x = find_leader(x);
        return comp_types[x];
    }
};
 