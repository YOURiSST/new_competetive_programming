//YOURiSST_xD\\

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
typedef long long ll;
typedef long double ld;
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

int const INF = 2 * 1e9;
ll const LINF = 1e18;
const int MAXN = 100 * 1000; // 1e5
//ll const CONST = 9223372036854775807;
long double const PI = 3.14159265358979323846;
//int const MAXN = 101;
const int SQRT = 350;
const int LOG = 21;

void solve() {
    
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    return 0;
}