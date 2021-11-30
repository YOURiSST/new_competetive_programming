struct Edge {
    int u, v;
    Edge(int u_, int v_) : u(u_), v(v_) {}  
};


struct TreeWithLCA {
    int n, t; 
    vector<vi> g;
    vi tin, tout, h, p;
    vector<vi> bin_p; 
    
    void DFS(int v, int pr) {
        p[v] = pr;
        tin[v] = t++;
        h[v] = (pr == v ? 0 : h[pr] + 1);
        bin_p[v][0] = p[v];
        for (int i = 1; i < LOG; ++i) {
            bin_p[v][i] = bin_p[bin_p[v][i - 1]][i - 1];
        }
        
        for (auto & to : g[v]) {
            if (to != pr) {
                DFS(to, v);
            }
        }
        
        tout[v] = t++;
    }
    
    
    TreeWithLCA(int n_, const vector<Edge>& edges) {
        //ресайзы юра блин
        n = n_;
        g.resize(n);
        tin.resize(n);
        tout.resize(n);
        h.resize(n);
        p.resize(n);
        bin_p.resize(n, vi (LOG));
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
    
    int LCA (int u, int v) {
        if (is_ancestor(u, v)) {
        	return u;
        }
        if (is_ancestor(v, u)) {
        	return v;
        }
        
        for (int l = LOG - 1; l >= 0; --l) {
            if (!is_ancestor(bin_p[u][l], v)) {
                u = bin_p[u][l];
            }
        }
        
        // u – это pre-LCA
        return p[u];
    }
    
};