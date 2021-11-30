vector<pair<int, int>> get_factor(int n) {
    vector<pair<int, int>> fact;
    
    for (int d = 2; d * d <= n; ++d) {
        int cnt = 0;
        
        while (n % d == 0) {
            ++cnt;
            n /= d;
        }
        
        if (cnt != 0) {
            fact.emplace_back(d, cnt);
        }
    }
    
    if (n != 1) {
        fact.emplace_back(n, 1);
    }
    
    return fact;
}