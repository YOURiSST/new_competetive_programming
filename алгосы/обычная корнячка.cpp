struct SQRT {
    int n;
    vector<int> a;
    vector<int> sum_block;
    vector<int> upd_block;
    
    SQRT(const vector<int>& a_) : a(a_) {
        n = a.size();
        sum_block.resize(n / BLOCK + 1);
        upd_block.resize(n / BLOCK + 1);
        
        for (int i = 0; i < n; ++i) {
            sum_block[i / BLOCK] += a[i];
        }
    }
    
    int get_sum(int l, int r) {
        int res = 0;
        for (int i = l; i <= r;) {
            if (i % BLOCK == 0 && i + BLOCK - 1 <= r) {
                res += sum_block[i / BLOCK];
                i += BLOCK;
                continue;
            } 
            res += upd_block[i / BLOCK];
            res += a[i];
            ++i;
        }
        return res;
    }
    
    // прибавить x ко всем элементам с l по r
    void update(int l, int r, int x) {
        for (int i = l; i <= r;) {
            if (i % BLOCK == 0 && i + BLOCK - 1 <= r) {
                sum_block[i / BLOCK] += x * BLOCK;
                upd_block[i / BLOCK] += x;
                i += BLOCK;
                continue;
            }
            sum_block[i / BLOCK] += x;
            a[i] += x;
            ++i;
        }
    }
};
