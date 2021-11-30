const int N = 1000 * 1000 + 1;
const long long MOD = 1000 * 1000 * 1000 + 7;

long long factorial[N];

/*
 * binpow и factorize уже есть
 */

long long phi(int n) {
    vector<pair<int, int>> fact = factorize(n);
    long long result = n;
    
    for (auto [p, _] : fact) { // переменная с именем _ показывает, что она нам не нужна
        result /= p;
    }
    
    for (auto [p, _] : fact) {
        result *= p - 1;
    }
    
    return result;
}

long long rev(int n) {
    // для простого MOD:
    return binpow(n, MOD - 2);
    // для составного MOD:
    return binpow(n, phi_MOD - 1); // phi_MOD – предподсчитанное phi(MOD)
}

long long C(int n, int k) {
    return factorial[n] * rev(factorial[k]) % MOD * rev(factorial[n - k]) % MOD;
}

int main() {
    factorial[0] = 1;
    
    for (int i = 1; i < N; ++i) {
        factorial[i] = factorial[i - 1] * i % MOD;
    }
    
    long long phi_MOD = phi(MOD);
    // precalc: O(N + sqrt(MOD))
}



























