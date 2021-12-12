int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a) cin >> i;
    vi tmp = a;
    sort(all(tmp));
    // было tmp = [1, 1, 2, 3, 3, 4]
    // unique: стало tmp = [1, 2, 3, 4, 1, 3]
    // unique возвращает итератор на последний уникальный элемент
    tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
    
    for (auto& i : a) {
        i = lower_bound(tmp.begin(), tmp.end(), i) - tmp.begin();
    }
}