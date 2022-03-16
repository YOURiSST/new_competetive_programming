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

#define min min<int>
#define Time (double)clock() / CLOCKS_PER_SEC
#define filein(FILE) freopen(FILE, "r", stdin)
#define fileout(FILE) freopen(FILE, "w", stdout)
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
            if (j + 1 != vec[j].size()) {
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
const int MAXN = 4 * 100 * 1001; // 1e5 + 0
//ll const CONST = 9223372036854775807;
long double const PI = 3.14159265358979323846;
//int const MAXN = 101;
const int SQRT = 350;
const int LOG = 21;
const int MOD = 1e9 + 7;


struct Matrix {
    ll sum;
    int i1, i2, j1, j2;
    Matrix(ll t1, int t2, int t3, int t4, int t5) {
        sum = t1;
        i1 = t2;
        i2 = t3;
        j1 = t4;
        j2 = t5;
    }
    Matrix() = default;
};

bool operator < (Matrix a, Matrix b) {
    if (a.sum != b.sum)
        return a.sum < b.sum;
    if (a.i1 == b.i1 && a.i2 == b.i2 && a.j1 == b.j1 && a.j2 == b.j2) {
        return false;
    }
    if (a.i1 != b.i1) {
        return a.i1 < b.i1;
    }
    if (a.i2 != b.i2) {
        return a.i2 < b.i2;
    }
    if (a.j1 != b.j1) {
        return a.j1 < b.j1;
    }
    if (a.j2 != b.j2) {
        return a.j2 < b.j2;
    }
}





signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, p; cin >> n >> m >> p;
    vvi a(n, vi(m));
    ll total = 0;
    for (auto & i : a) {
        for (auto & j : i) {
            cin >> j;
            total += j;
        }
    }
    dbg(total);

    vvl n_prefs(n, vl(m + 1));
    vvl m_prefs(m, vl(n + 1));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            n_prefs[i][j + 1] = n_prefs[i][j] + a[i][j];
        }
    }

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            m_prefs[j][i + 1] = m_prefs[j][i] + a[i][j];
        }
    }

    
    set<Matrix> not_kaif;
    not_kaif.emplace(Matrix(total, 0, n - 1, 0, m - 1));
    ll CanYouFeelMyHeart = 0;
    while (!not_kaif.empty()) {
        auto m = *prev(not_kaif.end());
        
        if (m.sum < p) {
            break;
        }
        if (!(m.sum % p)) {
            dbg("here");
            CanYouFeelMyHeart = max<ll>(CanYouFeelMyHeart, m.sum);
            break;
        }
        
        Matrix m1 = {m.sum - n_prefs[m.i1][m.j2 + 1] + n_prefs[m.i1][m.j1], m.i1 + 1, m.i2, m.j1, m.j2};
        Matrix m2 = {m.sum - n_prefs[m.i2][m.j2 + 1] + n_prefs[m.i2][m.j1], m.i1, m.i2 - 1, m.j1, m.j2};
        Matrix m3 = {m.sum - m_prefs[m.j1][m.i2 + 1] + m_prefs[m.j1][m.i1], m.i1, m.i2, m.j1 + 1, m.j2};
        Matrix m4 = {m.sum - m_prefs[m.j2][m.i2 + 1] + m_prefs[m.j2][m.i1], m.i1, m.i2, m.j1, m.j2 - 1};
        if (m1.sum >= p)
            not_kaif.emplace(m1);
        if (m2.sum >= p)
            not_kaif.emplace(m2);
        if (m3.sum >= p)
            not_kaif.emplace(m3);
        if (m4.sum >= p)
            not_kaif.emplace(m4);
        not_kaif.erase(prev(not_kaif.end()));
    }
    cout << CanYouFeelMyHeart;
    dbg(Time);
    return 0;
}

