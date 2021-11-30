int binpow (int a, int n) {
    int result = 1;
    while (n) {
        if (n & 1)
            result *= a;
        a *= a;
        n >>= 1;
    }
    return result;
}
















int binpow(int a, int n) {
    int result = 1;
    for (int i = 0; (1 << i) <= n; ++i, a *= a) {
        if ((n >> i) & 1) {
            result *= a;
        }
    }
    return result;
}





/*
001101011
&
000000001
=
000000001

---------

int binpow(int a, int n) {
    int result = 1;
    
    // (1 << i) это 2^i
    for (int i = 0; (1 << i) <= n; ++i, a *= a) {
        // i-й бит в числе n: (n >> i) % 2 – откинули все биты младше нужного и взяли остаток при делении на 2
        // % 2 это то же самое, что & 1
        if (/*i-я степень двойки есть в числе n*/ (n >> i) & 1) {
            result *= a;
        }
    }
    
    return result;
}

*/