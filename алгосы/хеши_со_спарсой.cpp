#define int long long
int const INF = 2 * 1e9;
ll const LINF = 1e18;
const int MAXN = 100 * 1000; // 1e5 + 0
//ll const CONST = 9223372036854775807;
long double const PI = 3.14159265358979323846;
//int const MAXN = 101;
const int SQRT = 350;
const int LOG = 21;

const int MOD = 1e9 + 7;
const int p = 97;
int pows[MAXN];

struct SparseHashGGUcraine {
    int n;
    vi lg;
    vvi sparse;
    SparseHashGGUcraine(const string& s) {
        n = sz(s);
        lg.resize(n + 1);
        for (int i = 2; i < n + 1; ++i) {
            lg[i] = lg[i - 1] + (i == (2 << lg[i - 1]));
        }
        sparse.resize(lg.back() + 1, vi(n));

        for (int i = 0; i < n; ++i) {
            sparse[0][i] = s[i] - 'a' + 1;
        }

        for (int k = 1; k < lg.back() + 1; ++k) {
            for (int i = 0; i + (1 << k) < n + 1; ++i) {
                sparse[k][i] = (sparse[k - 1][i] + sparse[k - 1][i + (1 << (k - 1))] * pows[(1 << (k - 1))]) % MOD;
            }
        }
    }

    pii is_here(int l, int r) {
        int len = (r - l);
        int now_pow = lg[len];
        pii ans;
        ans.ft = sparse[now_pow][l];
        ans.sc = sparse[now_pow][r - (1 << now_pow)];
        return ans;
    }
};



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string baza; cin >> baza;
    SparseHashGGUcraine sparse(baza);
    pows[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        pows[i] = pows[i - 1] * p;
    }
    int t; cin >> t;
    while (t--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if (sparse.is_here(l1 - 1, r1) == sparse.is_here(l2 - 1, r2))
            cout << "yes\n";
        else
            cout << "nope\n";
    }
    dbg(Time);
    return 0;
}

////////////////////////////////////////



const int MOD = 1e9 + 7;
const int p = 97;
int pows[MAXN];

struct SparseHashGGUcraine {
    int n;
    vi lg;
    vvi sparse;
    SparseHashGGUcraine(const string& s) {
        n = sz(s);
        lg.resize(n + 1);
        for (int i = 2; i < n + 1; ++i) {
            lg[i] = lg[i - 1] + (i == (2 << lg[i - 1]));
        }
        sparse.resize(lg.back() + 1, vi(n));

        for (int i = 0; i < n; ++i) {
            sparse[0][i] = s[i] - 'a' + 1;
        }

        for (int k = 1; k < lg.back() + 1; ++k) {
            for (int i = 0; i + (1 << k) < n + 1; ++i) {
                sparse[k][i] = (sparse[k - 1][i] + sparse[k - 1][i + (1 << (k - 1))] * pows[(1 << (k - 1))]) % MOD;
            }
        }
    }

    pii is_here(int l, int r) {
        int len = (r - l);
        int now_pow = lg[len];
        pii ans;
        ans.ft = sparse[now_pow][l];
        ans.sc = sparse[now_pow][r - (1 << now_pow)];
        return ans;
    }
};

bool is_equal(int l1, int r1, int l2, int r2, SparseHashGGUcraine& sparse) { 
    return sparse.is_here(l1, r1 + 1) == sparse.is_here(l2, r2 + 1);
}

vi zfunc(const string& s, SparseHashGGUcraine& sparse) {
    int n = sz(s);
    vi z(n);
    for (int i = 1; i < n; ++i) {
        if (s[i] != s[0]) {
            continue;
        }
        int l = i, r = n;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (is_equal(0, mid - i, i, mid, sparse)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        z[i] = l - i + 1;

    }
    dbg(sparse.is_here(0, 2), sparse.is_here(2, 4));
    return z;   
}





signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    pows[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        pows[i] = p * pows[i - 1];
    }
    string s = "abacaba";
    SparseHashGGUcraine sparse(s);
    cout << zfunc(s, sparse);
    return 0;
}
