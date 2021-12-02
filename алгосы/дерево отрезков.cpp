struct SegTree {
    int n;
    vector<pair<int, int>> tree;
    
    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r - 1) {
            tree[v] = {a[l], l};
        } else {
            int mid = (l + r) / 2;
            build(2 * v, l, mid, a);
            build(2 * v + 1, mid, r, a);
            tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        }
    }
    
    SegTree(int n_, const vector<int>& a) {
        n = n_;
        tree.resize(4 * n);
        build(1, 0, n, a);
    }
	
	
    
    pair<int, int> get_min(int lq, int rq, int v, int l, int r) {
        if (r <= lq || rq <= l) {
            return {INF, INF};
        }
        
        if (lq <= l && r <= rq) {
            return tree[v];
        }
        
        int mid = (l + r) / 2;
        return min(
            get_min(lq, rq, 2 * v, l, mid),
            get_min(lq, rq, 2 * v + 1, mid, r)
        );
    }
    
    pair<int, int> get_min(int lq, int rq) {
        return get_min(lq, rq, 1, 0, n);
    }
    
    void update(int x, int i, int v, int l, int r) {
        if (r - l == 1 && l == i) {
            tree[v] = {x, i};   
            return;
        }
        
        int mid = (l + r) / 2;
        
        if (i < mid) {
            update(x, i, 2 * v, l, mid);
        } else {
            update(x, i, 2 * v + 1, mid, r);
        }
        
        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
    }
    
    void update(int x, int i) {
        update(x, i, 1, 0, n);
    }
};



