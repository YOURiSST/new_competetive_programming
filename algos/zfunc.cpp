std::vector<int> zfunc(std::string& s) {
    int n = s.size();
    vi z(n);
    int l = 0, r = 1; // [l, r) , r = l + z[l]
    for (int i = 1; i < n; ++i) {
        if (i < r) {
            z[i] = min(z[i - l], r - i);
        }
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int num_different(std::string s) {
    int n = s.size();
    int ans = 1;
    string cur = "";
    cur += s.back();
    int i = s.size() - 2;
    while (i >= 0) {
        cur = s[i--] + cur;
        vi z = zfunc(cur);
        int zmax = *max_element(all(z));
        ans += sz(cur) - zmax;
    }
    return ans;    
//    int i = s
}