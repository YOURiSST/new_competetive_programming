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
#define max max<int>
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
    int sum;
    int i1, i2, j1, j2;
    Matrix(int sum_, int i1_, int i2_, int j1_, int j2_) {
        sum = sum_;
        i1 = i1_; i2 = i2_; j1 = j1_; j2 = j2_;
    }
    Matrix() = default;
};

bool operator < (Matrix a, Matrix b) {
    return a.sum < b.sum;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    /*
    i really wanted to visit a BringMeTheHorizon show 
    but they've denied their tour in Russia
    :(( 
    this is the reason why i need to drown my pain. in olympiad problems.
    -_-
    */
    int total = 0;
    int n, m, p; cin >> n >> m >> p;
    vvi a(n, vi(m));
    for (auto & i : a) {
        for (auto & o : i) {
            cin >> o;
            total += o;
        }
    }
    set<Matrix> kaif;
    int CanYouFeelMyHeart = 0;

    vvi prefs_n(n, vi(m + 1));
    vvi prefs_m(m, vi(n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            prefs_n[i][j + 1] = prefs_n[i][j] + a[i][j];
        }
    }
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            prefs_m[j][i + 1] = prefs_m[j][i] + a[i][j];
        }
    }
    
    kaif.emplace(Matrix(total, 0, n - 1, 0, m - 1));
    dbg(total);

    
    dbg("do");
    while (!kaif.empty()) {
        Matrix m = *(prev(kaif.end()));
        //dbg(m.sum, m.i1, m.i2, m.j1, m.j2);
        
        if (m.sum < p)
            break;
        if (!(m.sum % p)) {
            dbg(m.sum, m.i1, m.i2, m.j1, m.j2);
            CanYouFeelMyHeart = m.sum;
            break;
        }
        int i1 = m.i1, i2 = m.i2, j1 = m.j1, j2 = m.j2;
        if ((prefs_n[i2][j2 + 1] - prefs_n[i2][j1]) < 0) {
            dbg(i1, j1, i2, j2);
        }
        
        Matrix m1 = {m.sum - (prefs_m[j2][i2 + 1] - prefs_m[j2][i1]), i1, i2, j1, j2 - 1};
        Matrix m2 = {m.sum - (prefs_m[j1][i2 + 1] - prefs_m[j1][i1]), i1, i2, j1 + 1, j2};
        Matrix m3 = {m.sum - (prefs_n[i1][j2 + 1] - prefs_n[i1][j1]), i1 + 1, i2, j1, j2};
        Matrix m4 = {m.sum - (prefs_n[i2][j2 + 1] - prefs_n[i2][j1]), i1, i2 - 1, j1, j2};
        if (m1.sum >= p)
            kaif.emplace(m1);
        if (m2.sum >= p)
            kaif.emplace(m2);
        if (m3.sum >= p)
            kaif.emplace(m3);
        if (m4.sum >= p)
            kaif.emplace(m4);
        kaif.erase(prev(kaif.end()));
    }

    cout << CanYouFeelMyHeart;
    dbg(Time);
    return 0;
}

