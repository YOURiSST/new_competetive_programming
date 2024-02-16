void dfs(int v) {
    used[v] = 1;
    for (auto & to : g[v]) {
	if (!used[to])
	    dfs(to);
    }
}