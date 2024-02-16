    for (int mid = 0; mid < n; ++mid) {
        for (int from = 0; from < n; ++from) {
            for (int to = 0; to < n; ++to) {
                if (g[from][mid] < INF && g[mid][to] < INF)
                    g[from][to] = min(g[from][to], g[from][mid] + g[mid][to]);
            }
        }
    }