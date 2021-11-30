int main() {
	
    int n; cin >> n;
    
    vi a(n); for (auto & i : a) cin >> i;
    vi lg(n + 1, 0);
    for (int i = 2; i < n + 1; ++i) {
        if (i == (2 << lg[i - 1])) {
            lg[i] = lg[i - 1] + 1;
        } else {
            lg[i] = lg[i - 1];
        }
    }
    //vector<vi> sparse(n, vi(lg.back() + 1));
    vector<vi> sparse(lg.back() + 1, vi(n));
    for (int i = 0; i < n; ++i) {
        sparse[0][i] = a[i];
    }
    
    for (int k = 1; k < lg.back() + 1; ++k) {
        for (int i = 0; i + (1 << k) < n + 1; ++i) {
            sparse[k][i] = min(sparse[k - 1][i], sparse[k - 1][i + (1 << k - 1)]);
        }
    }
    
    cout << 1.0 * clock() / CLOCKS_PER_SEC << endl; // время с момента запуска
    
    int q; cin >> q;
    while (q--) {
        //отрезки
        int l, r; cin >> l >> r;
        int k = lg[r - l + 1];
        int ans = min(sparse[l][k], sparse[r - (1 << k) + 1][k]);
        cout << ans;
    }

    return 0;
}
