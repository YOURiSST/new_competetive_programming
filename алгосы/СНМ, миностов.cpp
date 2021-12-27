struct DSU {
    int n;
    vector<int> sizes, pred;
    
    DSU(int n_) {
		n = n_;
        sizes.resize(n, 1);
        pred.resize(n);
        iota(all(pred), 0);
    }
    
    int find_leader(int v) {
        while (pred[v] != v) {
            v = pred[v];
        }
        return v;
    }
    
	/*
    int find_leader(int v) {
        return v == pred[v] ? v : (pred[v] = find_leader(pred[v]));
    }
	*/
    
    bool join(int u, int v) {
        if ((u = find_leader(u)) == (v = find_leader(v))) {
            return false;
        }
        if (sizes[u] < sizes[v]) {
            swap(u, v);
        }
        pred[v] = u;
        sizes[u] += sizes[v];
        return true;
    }
};

struct Edge {
    int u, v, w;
    
    Edge(int u_, int v_, int w_) : u(u_), v(v_), w(w_) { }
};

bool comp(Edge a, Edge b) {
    return a.w < b.w;
}

int main() {
    int n, m; cin >> n >> m;
    vector<Edge> edges(m);
    for (auto & [u, v, w] : edges) {
        cin >> u >> v >> w;
    }
    sort(all(edges), comp);
    DSU d(n);
    vector<Edge> min_ostov;
    int weight = 0;
    for (auto & [u, v, w] : edges) {
        if (d.join(u, v)) {
            min_ostov.eb(u, v, w);
            weight += w;
        }
    }
    cout << weight;
    return 0;
}