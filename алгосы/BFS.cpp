vi cost, pred, used;
int BFS (const vvi& g, int start, int finish) {
	int size = sz(g);
	cost.resize(size, INF);
	pred.resize(size);
	used.resize(size);

	queue<int> q;
	q.push(start);
	pred[start] = start;
	cost[start] = 0;
	used[start] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto & to : g[v]) {
			if (used[to] != 1) {
				used[to] = 1;
				cost[to] = cost[v] + 1;
				pred[to] = v;
				q.push(to);
			}
		}
	}
	return cost[finish]; 
}




int BFS() {
    vector<vector<int>> dist(r, vector<int>(c, INF));
    queue<Point> Q;
    for (auto [x, y] : ps) {
        dbg("ajsdnlasd");
        Q.push(Point(x, y));
        dist[x][y] = 0;
    }
    int ans = 0;
    while (!Q.empty()) {
        dbg("ahh");
        auto [x, y] = Q.front();
        ans = max(ans, dist[x][y]);
        Q.pop();
        for (auto [dx, dy] : dif) {
            if (is_valid(x + dx, y + dy) && dist[x + dx][y + dy] == INF) {
                dist[x + dx][y + dy] = dist[x][y] + 1;
                Q.push(Point(x + dx, y + dy));
            }
        }
    }
    return ans;
}