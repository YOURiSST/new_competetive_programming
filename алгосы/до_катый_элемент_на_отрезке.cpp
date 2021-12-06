struct SegTree {
    int n;
    vector<vector<int>> t;
  
    SegTree(int n_, const vector<int>& a) {
        n = n_;
        t.resize(4 * n);
        build(1, 0, n, a);
    }
  
    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r - 1) {
            t[v] = {a[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(v * 2, l, mid, a);
        build(v * 2 + 1, mid, r, a);
        t[v].resize(r - l);
        merge(t[2 * v].begin(), t[2 * v].end(), // первый
              t[2 * v + 1].begin(), t[2 * v + 1].end(), // второй
              t[v].begin()); // куда
    }
    
    int num_of_k(int v, int l, int r, int lq, int rq, int k) {
        if (l >= rq || lq >= r) {
            return 0;
        }
        if (lq <= l && rq >= r) {
            return lower_bound(all(t[v]), k) - t[v].begin();
        }
        int mid = (l + r) / 2;
        return (num_of_k(2 * v, l, mid, lq, rq, k) + num_of_k(2 * v + 1, mid, r, lq, rq, k));
    }
    int num_of_k(int l, int r, int k) {
        return num_of_k(1, 0, n, l, r, k);
    }
};

int main() {
    int n; cin >> n;
    vector<int> a(n); 
    for (auto & i : a) cin >> i;
    SegTree tree(n, a);
	int counter; cin >> counter;
    while (counter--) {
        int lq, rq, k; cin >> lq >> rq >> k;
        --k;
        int l = 0, r = 1e9 + 1;
        while (l < r - 1) {
            int mid = (l + r) / 2;
            int count = tree.num_of_k(lq - 1, rq, mid);
            if (count > k) {
                r = mid;
            } else {
                l = mid;
            }
        }
        cout << l << e;
    }
    
    return 0;
}


