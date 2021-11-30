const ll MOD = 1e9 + 7;
const ll p = 97;
ll ppow[MAXN];

struct Hash_With_Sparse {
    int n;
    vector<int> lg;
    vector<vector<ll>> sparse;
    Hash_With_Sparse(const string& s) {
        n = sz(s);
        lg.resize(n + 1, 0);
        for (int i = 2; i < n + 1; ++i) {
            if (i == (2 << lg[i - 1])) {
                lg[i] = lg[i - 1] + 1;
            } else {
                lg [i]= lg[i - 1];
            }
        }
        sparse.resize(lg.back() + 1, vector<ll> (n));
        for (int i = 0; i < n; ++i) {
            sparse[0][i] = s[i] - 'a' + 1;
        }
        for (int k = 1; k < lg.back() + 1; ++k) {
            for (int i = 0; i + (1 << k) < n + 1; ++i) {
                sparse[k][i] = (sparse[k - 1][i] + ppow[k - 1] * sparse[k - 1][i + (1 << k - 1)] % MOD) % MOD;
            }
        }
        dbg("builded");
    }
    pair<ll, ll> q(int l, int r) {
        dbg(r - l + 1);
        int k = lg[r - l + 1];
        return {sparse[k][l], sparse[k][r - (1 << k) + 1]};
    }
};

int main() {

    ppow[0] = 1;
    
    for (int i = 1; i < MAXN; ++i) {
        ppow[i] = p * ppow[i - 1] % MOD;
    }
    string s; cin >> s;
    Hash_With_Sparse hash(s);
    int q; cin >> q;
    while(q--) {
        int l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
        if (hash.q(l1, r1) == hash.q(l2, r2)) {
            cout << "yeap" << e;
        } else {
            cout << "nope" << e;
        }
    }
    
    return 0;
}
