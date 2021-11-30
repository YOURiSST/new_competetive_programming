
struct Edge{
    int to, w;
    Edge (int _to, int _w) {
        to = _to, w = _w;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> g(n);
    for (int i = 0; i < m; ++i) {
        int from, to, w; cin >> from >> to >> w;
        --from; --to;
        g[from].eb(to, w);
    }
    int start, finish; cin >> start >> finish; 
    --start; --finish;
    vector<int> cost(n, INF);
    set<pair<int, int>> q;
    cost[start] = 0;
    q.emplace(0, start);

    while (!q.empty()) {
        int v = q.begin() -> sc;
        q.erase(q.begin());
        for (auto & [to, w] : g[v]) {
            if (cost[to] > cost[v] + w) {
                q.erase({cost[to], to});
                cost[to] = cost[v] + w;
                q.emplace(cost[to], to);
            }
        }
    }
    
    cout << cost[finish];
    return 0;
}