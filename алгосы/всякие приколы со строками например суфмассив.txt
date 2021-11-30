int main() {
    ppow[0] = 1;
    
    for (int i = 1; i < MAXN; ++i) {
        ppow[i] = p * ppow[i - 1] % MOD;
    }
    string s; cin >> s;
    int n = s.size();
    s.push_back('#');
    Hash_With_Sparse hash(s);
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    sort(perm.begin(), perm.end(), [&n, &hash, &s](int i, int j) {
        if (s[i] != s[j]) {
            return s[i] < s[j];
        }
        int l = 0, r = min(n - i, n - j);
        while (l < r - 1) {
            int mid = (l + r) / 2;
            if (hash.q(i, i + mid - 1) == hash.q(j, j + mid - 1)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return s[i + r] < s[j + r];
    });
    for (int i = 0; i < n; ++i) {
        cout << perm[i] << " " << s.substr(perm[i]) << e;
    }
    return 0;
}
////////////// 1 пример, просто сортировка строк

int main() {
    int n;
    cin >> n;
    vector<string> a(n);
    for (auto& i : a) cin >> i;
    sort(a.begin(), a.end(), [](const string& x, const string& y) {
        return x > y;
    });
}

///////////// 2 пример, сортировка индексов строк

int main() {
    int n;
    cin >> n;
    vector<string> a(n);
    for (auto& i : a) cin >> i;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    sort(perm.begin(), perm.end(), [&a](int i, int j) {
        return a[i] > a[j];
    });
}
