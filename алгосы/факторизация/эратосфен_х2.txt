// 0 если составное, 1 если простое
vector<int> eratosphene(int n) {
    vector<int> res(n + 1, 1); // по умолчанию все простые
    res[1] = 0; // кроме 1
    
    for (int d = 2; d <= n; ++d) {
        if (res[d] == 1) { // если текущее число простое
            for (int k = 2 * d; k <= n; k += d) {
                res[k] = 0; // k – мультипликация d, поэтому k составное
            }
        }
    }
    
    return res;
}

-----------------------------------

// в ячейке с числом записан его минимальный простой делитель
vector<int> eratosphene_smart(int n) {
    vector<int> res(n + 1, 0);
    
    for (int d = 2; d <= n; ++d) {
        if (res[d] == 0) { // если текущее число простое
            for (int k = 2 * d; k <= n; k += d) {
                if (res[k] == 0) {
                    res[k] = d; // k – мультипликация d, поэтому k составное, его минимальный делитель d
                }
            }
        }
    }
    
    return res;
}

vector<pair<int, int>> get_factor_fast(int n, const vector<int>& min_prime) {
    vector<pair<int, int>> res;
    
    while (n != 1) {
        int p = min_prime[n]; // p – минимальный простой делитель n
        
        if (res.empty() || res.back().first != p) { // если появляется новое простое
            res.emplace_back(p, 0); // добавляем его со степенью ноль
        }
        
        ++res.back().second; // а потом безусловно увеличиваем степень на 1
        n /= p; // не забываем n поделить на p
    }
    
    return res;
}

const int MAXN = 1000 * 1000;

int main() {
    // препроцессинг
    vector<int> min_prime = eratosphene_smart(MAXN);
    
    // кол-во запросов
    int q;
    cin >> q;
    
    for (int i = 0; i < q; ++i) {
        // число-запрос
        int n;
        cin >> n;
        auto fact = get_factor_fast(n, min_prime);
    }
}
