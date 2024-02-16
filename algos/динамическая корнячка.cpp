
struct DynamicSQRT {
    int n;
    vector<vector<int>> blocks;
    vector<int> blocks_sum;
    void build(const vector<int>& a) {
        blocks.clear();
        blocks_sum.clear();
        blocks.resize(n / SQRT + 1);
        blocks_sum.resize(n / SQRT + 1);
        for (int i = 0; i < n; ++i) {
            blocks[i / SQRT].pb(a[i]);
            blocks_sum[i / SQRT] += a[i];
        }
    }
    
    DynamicSQRT(const vector<int>& a) {
        n = a.size();
        build(a);
    }
    
    void insert(int x, int i) {
        int l = 0, block_num = 0, r = blocks[0].size(); 
        while (true) {
            if (r > i) {
                break;
            }
            l += blocks[block_num].size();
            block_num++;
            r += blocks[block_num].size();
        }
        ++n;
        blocks[block_num].insert(blocks[block_num].begin() + (i - l), x);
        blocks_sum[block_num] += x;
        if (blocks[block_num].size() == 2 * SQRT) {
            vector<int> a;
            for (auto& block : blocks) {
                for (auto i : block) {
                    a.pb(i);
                }
            }
            build(a);
        }
    }
    void erase(int i) {
        int l = 0, block_num = 0, r = blocks[0].size();
        while (true) {
            if (r > i) {
                break;
            }
            l += blocks[block_num].size();
            block_num++;
            r += blocks[block_num].size();
        }
        --n;
        auto it = blocks[block_num].begin() + (i - l);
        blocks_sum[block_num] -= *it;
        blocks[block_num].erase(it);
        
        if (blocks[block_num].size() == 0) {
            vector<int> a;
            for (auto & block : blocks) {
                for (auto & i : block) {
                    a.pb(i);
                }
            }
            build(a);
        }    
    }
    
  
    int get_sum(int lq, int rq) {
        int block_num = 0;
        int i = 0;
        int sum = 0;
        while (i + blocks[block_num].size() - 1 < lq) {
            i += blocks[block_num].size();
            ++block_num;
        }
        
        for (int j = 0; j < blocks[block_num].size(); ++j) {
            if (lq <= i + j && i + j <= rq) {
                sum += blocks[block_num][j];
            }
        }
        
        i += blocks[block_num].size();
        block_num++;
        
        while (block_num < blocks.size() && lq <= i && i + blocks[block_num].size() - 1 <= rq) {
            sum += blocks_sum[block_num];
            i += blocks[block_num].size();
            ++block_num;
        }
        
        for (int j = 0; i + j <= rq && j < blocks[block_num].size(); ++j) {
            sum += blocks[block_num][j];
        }
        
        return sum;
    }
};


