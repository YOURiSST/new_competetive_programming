struct Edge {
    int u, v;
    Edge(int u_, int v_) : u(u_), v(v_) {}
};
 
struct TreeWithLCA {
    int n, t;
    vector<vi> g;
    vi p, p_s, tin, tout, h;
    void DFS(int v, int pr) {
        p[v] = pr;
        int u = v;
        for (int i = 0; i < SQRT; ++i) {
            u = p[u];
        }
        p_s[v] = u;
        tin[v] = t++;
        h[v] = (v == pr ? 0 : h[pr] + 1);
        for (auto & to : g[v]) {
            if (to != pr) {
                DFS(to, v);
            }
        }
        tout[v] = t++;
    }
    TreeWithLCA() = default;
    TreeWithLCA(int n_, const vector<Edge>& edges) {
        n = n_;
        g.resize(n);
        tin.resize(n);
        tout.resize(n);
        h.resize(n);
        p.resize(n);
        p_s.resize(n);
        for (auto [u, v] : edges) {
            g[u].eb(v);
            g[v].eb(u);
        }
        t = 0;
        DFS(0, 0);
    }
    
    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }
    
    int LCA(int u, int v) {
        if (is_ancestor(u, v)) {
            return u;
        }
        if (is_ancestor(v, u)) {
            return v;
        }
        if (h[u] > h[v]) {
            swap(u, v);
        }
        
        for (;;u = p_s[u]) {
            if (is_ancestor(p_s[u], v)) {
                for (;!is_ancestor(u, v);u = p[u]) {}
                return u;
            }
        }
    }
    
};