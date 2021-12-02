vector<int> gentree() {
    vector<int> tree;
    tree.resize(n);
    tree[0] = -1;
    
    for (int i = 1; i < n; ++i) {
        tree[i] = rng() % i;
    }
    
    return tree;
}