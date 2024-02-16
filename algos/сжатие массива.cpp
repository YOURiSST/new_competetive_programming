int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a) cin >> i;
    vi tmp = a;
    sort(all(tmp));
    tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
    for (auto& i : a) {
        i = lower_bound(tmp.begin(), tmp.end(), i) - tmp.begin();
    }
}


////

questions.reserve(20 * 1000 * 1000 + 1);