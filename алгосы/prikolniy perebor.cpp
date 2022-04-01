struct Kok {
    int c, w;
    Kok (int t1, int t2) {
        c = t1;
        w = t2;
    }
    Kok() = default;
};

int n, W;
vector<Kok> koks;
int ans = -INF;

bool cmp(Kok a, Kok b) {
    return a.c * b.w > a.w * b.c;
}

int max_blin(int ind, int we) {
    vector<Kok> temp;
    for (int i = ind; i < n; ++i) {
        auto [c, w] = koks[i]
        if (w > we) {
            continue;
        }
        temp.eb(c, w);
    }
    
    sort(all(temp), cmp);
    int cur = 0;
    int i = 0;
    while (we > 0 && i < n) {
        if (temp[i].w <= we) {
            we -= temp[i].w;
            cur += temp[i].c;
        } else {
            cur += temp[i].c * we / temp[i].w;
            we = 0;   
        }
        i++;
    }
    return cur;
}


void foo (int i, int cost, int we) {
    if (we > W) {
        return;
    }
    if (i == n) {
        ans = max(ans, cost);
        return;
    }
    
    if (cost + max_blin(i, W - we) < ans) {
        return;
    }
    if (rng() % 2 == 0) {
        foo(i + 1, cost + koks[i].c, we + koks[i].w);
        foo(i + 1, cost, we);
    } else {
        foo(i + 1, cost, we);
        foo(i + 1, cost + koks[i].c, we + koks[i].w);
    }
}

signed main() {
    cin >> n >> W;
    koks.resize(n);
    
    for (auto & [c, w] : koks) {
        cin >> c >> w;    
    }
    
    foo(0, 0, 0);
    
    cout << ans;
    return 0;
}





