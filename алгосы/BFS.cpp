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
