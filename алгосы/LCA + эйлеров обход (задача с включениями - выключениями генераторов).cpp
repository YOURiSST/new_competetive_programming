/*\YOURiSST_xD\*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <map>
#include <chrono>
#include <random>
#include <bitset>
#include <unordered_set>
#include <unordered_map>


#define sz(a) ((int)((a).size()))
#define get(_type, _x) \
    _type _x; \
    cin >> _x
#define mp(a, b) make_pair(a, b)
#define e "\n"
#define pb push_back
#define eb emplace_back
#define ft first
#define sc second
#define vi vector<int>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvl vector<vector<long long>>
#define pii pair<int, int>
#define pll pair<long long, long long>
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define Time (double)clock()/CLOCKS_PER_SEC
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng_ll(chrono::steady_clock::now().time_since_epoch().count());

template<typename T1, typename T2>
ostream &operator<<(ostream &out, pair<T1, T2> p) {
    out << '<' << p.first << " | " << p.second << '>';
    return out;
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        out << vec[i];
        if (i + 1 != vec.size()) {
            out << " ";
        }
    }
    return out;
}

template<typename T>
ostream &operator<<(ostream &out, const vector<vector<T>> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            out << vec[i][j];
            if (j + 1 != vec.size()) {
                out << " ";
            }
        }
        if (i != vec.size() - 1)
            out << e;
    }
    return out;
}


template<typename T>
void _dbg(const char *_s, T _h) { cerr << _s << " = " << _h << "\n"; }

template<typename T, typename... Ts>
void _dbg(const char *_s, T _h, Ts... _t) {
    for (int _b = 0; ((_b += *_s == '(') -= *_s == ')') != 0 || *_s != ',';)cerr << *_s++;
    cerr << " = " << _h << ",";
    _dbg(_s + 1, _t...);
}

#ifdef LOCAL
#define dbg(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...)
#endif


int binpow(int a, int n) {
    int result = 1;
    while (n) {
        if (n & 1)
            result *= a;
        a *= a;
        n >>= 1;
    }
    return result;
}

#define int long long
int const INF = 2 * 1e9;
ll const LINF = 1e18;
const int MAXN = 100 * 1000; // 1e5 + 0
//ll const CONST = 9223372036854775807;
long double const PI = 3.14159265358979323846;
//int const MAXN = 101;
const int SQRT = 350;
const int LOG = 21;

struct Q {
    char type; int x, y, timer;
    Q(char t1, int t2, int t3, int t4) {
        type = t1;
        x = t2;
        y = t3;
        timer = t4;
    }  
    Q(char t1, int t2, int t3) {
        type = t1;
        x = t2;
        y = 0;
        timer = t3;
    }
    Q() = default;
};

struct SegTreeSum {
    int n;
    vi t;
    vi upd;
    SegTreeSum() = default;
    SegTreeSum(int n_) {
        n = n_;
        t.resize(4 * n);
        upd.resize(4 * n);
    }  
    void push(int v, int l, int r) {
        upd[2 * v] += upd[v];
        upd[2 * v + 1] += upd[v];
        int mid = (l + r) / 2;
        t[2 * v] += (mid - l) * upd[v];
        t[2 * v + 1] += (r - mid) * upd[v];
        upd[v] = 0;
    }
    void update(int lq, int rq, int x) {
        update(1, 0, n, lq, rq, x);
    }
    void update(int v, int l, int r, int lq, int rq, int x) {
        if (rq <= l || r <= lq) {
            return ;
        }
        if (lq <= l && r <= rq) {
            t[v] += (r - l) * x;
            upd[v] += x;
            return;
        }
        int mid = (l + r) / 2;
        push(v, l, r);
        update(2 * v, l, mid, lq, rq, x);
        update(2 * v + 1, mid, r, lq, rq, x);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    int get_me(int i) {
        return get_me(1, 0, n, i, i + 1);
    }
    int get_me(int v, int l, int r, int lq, int rq) {
        if (rq <= l || r <= lq) {
            return 0;
        }
        if (lq <= l && r <= rq) {
            return t[v];
        }
        int mid = (l + r) / 2;
        push(v, l, r);
        return get_me(2 * v, l, mid, lq, rq) + get_me(2 * v + 1, mid, r, lq, rq);
    }
};


struct TreeWithLCA {
    int n;
    vi h, tin, tout, preds;
    vvi g, up;
    vector<pii> euler;
    // up[v][i] – предок вершины v, находящийся на расстоянии 2^i
    SegTreeSum dead, ages;
    
    TreeWithLCA(int n_) {
        n = n_;
        g.resize(n);
        h.resize(n);
        tin.resize(n);
        tout.resize(n);
        preds.resize(n);
        up.resize(n, vi(LOG));
        
    }
    
    void add_edge(int u, int v) {
        g[u].eb(v);
        g[v].eb(u);
    }
    
    void build() {
        DFS(0, 0);
        dead = SegTreeSum(n);
        ages = SegTreeSum(n);
    }
    
    int timer = 0;
    
    void DFS (int v, int pred) {
        h[v] = h[pred] + 1;
        euler.eb(timer, v);
        tin[v] = timer++;
        preds[v] = pred;
        up[v][0] = pred;
        
        for (int lg = 1; lg < LOG; ++lg) {
            up[v][lg] = up[up[v][lg - 1]][lg - 1];
        }
        for (auto & to : g[v]) {
            if (to == pred) 
                continue;
            DFS(to, v);
        }
        tout[v] = timer++;
    }
    
    bool is_ancestor(int v, int u) {
        return (tin[v] <= tin[u] && tout[u] <= tout[v]);
    }
    
    int LCA(int v, int u) {
        if (is_ancestor(v, u)) {
            return v;
        }
        if (is_ancestor(u, v)) {
            return u;
        }  
        for (int lg = LOG - 1; lg >= 0; --lg) {
            if (!is_ancestor(up[v][lg], u)) {
                v = up[v][lg];
            }
        }
        return preds[v];
    }
    
    pair<int, int> get_range(int v) {
        int l, r;
        l = lower_bound(all(euler), pii(tin[v], -1)) - euler.begin();
        r = upper_bound(all(euler), pii(tout[v], -1)) - euler.begin();
        return {l, r};
    }
    
    void vertex_dies(int v, int old_age) {
        auto [l, r] = get_range(v);
        dead.update(l, r, 1);
        ages.update(l, r, -old_age);
    }   
    
    void vertex_reborns(int v, int new_age, bool first_time) {
        auto [l, r] = get_range(v);
        if (!first_time)
            dead.update(l, r, -1);
        ages.update(l, r, +new_age);
    }
    
    bool is_dead(int v) {
        auto [l, r] = get_range(v);
        dbg(euler, dead.get_me(l));
        return dead.get_me(l);
    }

    int get_ans(int v, int u, int counter) {
        if (is_dead(u) || is_dead(v)) {
            return -1;
        }
        
        return get_ans(v, counter) + get_ans(u, counter) - get_ans(LCA(v, u), counter);
    }
    
    int get_ans(int v, int counter) {
        auto [l, r] = get_range(v);
        return counter * h[v] - ages.get_me(l);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<Q> qs;
    TreeWithLCA tree(n);
    int counter = 1;
    for (int i = 0; i < m; ++i) {
        get(char, t);
        int x, y;
        if (t == '!') {
            cin >> x >> y;
            tree.add_edge(x - 1, y - 1);
            qs.eb('+', y - 1, counter);
        } else if (t == '-') {
            cin >> x;
            qs.eb('-', x - 1, counter);
        } else if (t == '+') {
            cin >> x;
            qs.eb('+', x - 1, counter);
        } else {
            cin >> x >> y;
            qs.eb('?', x - 1, y - 1, counter);
        }
        counter++;
    }
    tree.build();
    vector<int> ages(n, -1);
    dbg(tree.dead.get_me(0));
    ages[0] = 0;
    for (auto & [type, x, y, counter] : qs) {
        if (type == '+') {
            tree.vertex_reborns(x, counter, ages[x] == -1);
            ages[x] = counter;
        } else if (type == '-') {
            tree.vertex_dies(x, ages[x]);
        } else {
            if (ages[x] == -1 || ages[y] == -1) {
                cout << -1 << e;
            } else 
                cout << tree.get_ans(x, y, counter) << e;
        }
    }
    return 0;
}






 