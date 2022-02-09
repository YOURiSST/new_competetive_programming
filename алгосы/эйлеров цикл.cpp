struct Edge {
    int to;
    bool* used;
};

void dfs(int v, int p) {
    for (auto e : g[v]) {
        if (e.to == p) continue;
        if (!*e.used) {
            *e.used = true;
            dfs(...)
        }
    }
}

for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    bool* flag = new bool(false);
    g[u - 1].eb(v - 1, flag);
    g[v - 1].eb(u - 1, flag);
}