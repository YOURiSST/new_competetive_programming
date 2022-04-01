int n, m;
vvi g;

int h[MAXN]
int hup[MAXN];
int used[MAXN];
set<int> articulations;
int roots[MAXN];
void dfs(int v, int p) {

    h[v] = h[p] + 1;
    hup[v] = h[v];
    used[v] = 1;
    for (auto & to : g[v]) {
        if (to == p) {
            continue;
        }
        if (used[to]) {
            hup[v] = min(hup[v], h[to]);
        } else {
            if (roots[v]) {
                roots[v]++;
            }
            dfs(to, v);
            hup[v] = min(hup[v], hup[to]);
            if (hup[to] >= h[v]) {
                dbg(v);
                if (roots[v]) {
                    continue;
                }
                articulations.emplace(v);
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    g.resize(n);
    while (m--) {
        int u, v; cin >> u >> v;
        g[u - 1].eb(v - 1);
        g[v - 1].eb(u - 1);
    }
    for (int i = 0; i < n; ++i) {
        dbg(i);
        if (!used[i]) {
            roots[i] = 1;
            dfs(i, i);
        }
    }
    

    for (int i = 0; i < n; ++i) {
        if (roots[i] > 2) {
            articulations.emplace(i);
        }
    }


    cout << sz(articulations) << e;
    for (auto & i : articulations) {
        cout << i + 1 << e;
    }
    dbg(Time);
    return 0;
}
