
struct Edge {
    int from, to;
    Edge(int from_, int to_) {
        from = from_;
        to = to_;
    }  
};

vector<int> g[MAXN];
int h[MAXN];
int hup[MAXN];
bool used[MAXN];
vector<Edge> bridges;

void dfs(int v, int p) {
    h[v] = h[p] + 1;
    hup[v] = h[v];
	used[v] = true;	
    for (auto & to : g[v]) {
        if (to == p) {
            continue;
        } else if (!used[to]) {
            dfs(to, v);
            hup[v] = min(hup[v], hup[to]);
            if (hup[to] > h[v]) {
                bridges.eb(v, to);
            } 
        } else {
            hup[v] = min(hup[v], h[to]);
        }
    }
}


int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int from, to; cin >> from >> to; from--; to--;
        g[from].eb(to);
        g[to].eb(from);
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, i);
        }
    }
    return 0;
}

























