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
#define sz(a) ((int)((a).size()))
#define sort(a) sort(a.begin(), a.end())
#define get(_type, _x) \
    _type _x; \
    cin >> _x
#define mp(a, b) make_pair(a, b)
#define e endl
typedef long long ll;
using namespace std;
template <typename T1, typename T2>
ostream& operator << (ostream& out, pair<T1, T2> p) {
    out << p.first << " " << p.second;
    return out;
}
template <typename T>
ostream& operator << (ostream& out, const vector<T>& vec) {
    out << "[";
    for (int i = 0; i < vec.size(); ++i) {
        out << vec[i];
        if (i + 1 != vec.size()) {
            out << ", ";
        }
    }
    out << "]";
    return out;
}
template<typename T> void _dbg(const char*_s,T _h) { cerr<<_s<<" = "<<_h<<"\n"; }
template<typename T, typename... Ts> void _dbg(const char*_s,T _h,Ts... _t) {
    for(int _b=0;((_b+=*_s=='(')-=*_s==')')!=0||*_s!=',';)cerr<<*_s++;
    cerr<<" = "<<_h<<",";_dbg(_s+1,_t...);
}
#ifdef LOCAL
    #define dbg(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
    #define dbg(...)
#endif
int gcd(int a, int b) {
    while (a != 0) {
        b %= a;
        swap(a, b);
    }
    return a + b;
}
int binpow (int a, int n) {
    int result = 1;
    while (n) {
        if (n & 1)
            result *= a;
        a *= a;
        n >>= 1;
    }
    return result;
}
int const INF = 1e9;
const int MAXN = 100 * 1000;
ll const CONST = 9223372036854775807;
long double const PI = 3.14159265358979323846;
const long long MOD = 1000 * 1000 * 1000 + 7; //1e9 + 7

