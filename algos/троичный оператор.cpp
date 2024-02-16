return a == 0 ? b : gcd(b % a, a);

return *условие* ? *первый возврат* : *второй возврат*

можно вызывать функцию от обоих условий

int sqr(int x) { return x * x; }

int binpow(int a, int n) {
    return n % 2 == 0 ? sqr(binpow(a, n / 2)) : binpow(a, n - 1);
}