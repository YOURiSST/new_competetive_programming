struct Question {
    int l, int r, int i;
    Question() = default;
    Question(int l_, int r_, int i_) {
        l = l_;
        r = r_;
        i = i_;
    }
};

const int SQRT = 350;

bool comp(Question q1, Question q2) {
    return pii(q1.l / SQRT, q1.r) < pii(q2.l / SQRT, q2.r);
}

int main() {
    int n; cin >> n;
    vi a(n);
    for (auto & i : a) cin >> i;
    int k; cin >> k;
    vector<Question> q
    for (int i = 0; i < k; ++i) {
        int l, r; cin >> l >> r; l--; r--;
        q.eb(l, r, i);
    }
    
    sort(all(q), comp);
    
    
    vi temp = a;
    sort(all(temp));
    temp.resize(unique(all(temp)) - temp.begin());
    for (auto & i : a) {
        i = lower_bound(all(temp), i) - temp.begin();
    }  
    vi counter(sz(temp));
    
    
    int l = 0, r = 0;
    int sum = 1;
    vi ans(k);
    counter[a[0]] = 1;
    
    for (auto [lq, rq, i] : q) {
        while (r < rq) {
            ++r;
            if (!counter[a[r]]) {
                sum++;
            }
            counter[a[r]]++;
        }
        while (l > lq) {
            l--;
            if (!counter[a[l]]) {
                sum++;
            }
            counter[a[l]]++;
        }
        while (l < lq) {
            if (!(counter[a[l]] - 1)) {
                sum--;
            }
            counter[a[l]]--;
            l++;
        }
        while (r > rq) {
            if (!(counter[a[r]] - 1)) {
                sum--;
            }
            counter[a[r]]--;
            --r;
        }
        ans[i] = sum;
    }
    for (auto & i : ans) {
        cout << i << e;
    }
    return 0;
}












