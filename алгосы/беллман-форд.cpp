/////  ‘*’ если нет пути ‘-’ если не существует кратчайшего пути (цикл отрицательного веса)




struct Edge {
    ll from, to, cost;
};
ll max(ll a, ll b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    ll n, m, start;
    cin >> n >> m >> start;
    --start;
    vector<Edge> edges(m);
    for (auto & i : edges) {
        ll from, to, cost;
        cin >> from >> to >> cost;
        --from; --to;
        i = {from, to, cost};
    }

    vector<ll> dp(n, LINF);
    dp[start] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (auto & edge : edges) {
            if (dp[edge.from] < LINF) {
                dp[edge.to] = max(-LINF, min(dp[edge.to], dp[edge.from] + edge.cost));
            }
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        for (auto & edge : edges) {
            if (dp[edge.from] < LINF && dp[edge.to] > dp[edge.from] + edge.cost) {
                dp[edge.to] = -LINF;
            }
        }
    }

    for (auto & i : dp) {
        if (i == LINF) {
            cout << '*' << endl;
        } else if (i == -LINF) {
            cout << '-' << endl;
        } else {
            cout << i << endl;
        }
    }



    return 0;
}