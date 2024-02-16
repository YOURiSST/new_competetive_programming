vvi g, g2;
vi vs;
int used1[MAXN];
int used2[MAXN];


void dfs(int v) {
    used1[v] = 1;
    for (auto & to : g[v]) {
        if (!used1[to]) {
            dfs(to);
        }
    }
    vs.eb(v);
}

void dfs2(int v, int cnt) {
    used2[v] = cnt;
    for (auto & to : g2[v]) {
        dbg(v, to);
        if (used2[to] == -1) {
            dfs2(to, cnt);
        }
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    g.resize(n); g2.resize(n);
    fill(used2, used2 + n, -1);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        g[u - 1].eb(v - 1);
        g2[v - 1].eb(u - 1);
        dbg(v - 1, u - 1);
    }
    for (int i = 0; i < n; ++i) {
        if (!used1[i]) {
            dfs(i);
        }
    }
    reverse(all(vs));

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (used2[vs[i]] == -1) {
            dfs2(vs[i], cnt++);
        }

    }
/*    for (int i = 0; i < n; ++i) {
        cout << used2[i] << " ";
    }*/
    vector<pii> edges;
    for (int i = 0; i < n; ++i) {
        for (auto & to : g[i]) {
            if (used2[to] == used2[i]) {
                continue;
            }
            edges.eb(used2[i], used2[to]);
            dbg(used2[i], used2[to], i, to);
        }
    }
    sort(all(edges));
    edges.resize(unique(all(edges)) - edges.begin());
    cout << sz(edges);
    dbg(Time);
    return 0;
}
