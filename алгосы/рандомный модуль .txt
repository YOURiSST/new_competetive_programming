bool prime(ll x) {
    for (ll i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

ll generate() {
    // завели mt19937 rng
    ll m = 1e9 + rng() % 200000; // не факт что простое
    while (!prime(m)) {
        m++;
    }
    return m;
}

int main() {
    MOD = generate();
}