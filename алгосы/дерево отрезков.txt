#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000 * 1000 * 1000 + 7;

struct SegmentTree {
    int n; // длина массива, на котором делаются запросы
    vector<int> T; // значение минимума на отрезке

    SegmentTree(const vector<int>& a) {
        n = a.size();
        T.resize(4 * n); // у нас всегда не более 4n отрезков
        build(a, 1, 0, n); // 1 – корень дерева
    }

    // процедура построения: принимает массив, вершину v и полуинтервал [l, r), который к v относится
    // ВАЖНО: у нас всегда правая граница не включается, чтобы не было неудобств как у емакса с границами
    void build(const vector<int>& a, int v, int l, int r) {
        if (l == r - 1) { // если пришли в лист
            T[v] = a[l]; // то минимум – это само число
        } else {
            int m = (l + r) / 2; // полуинтервал [l, r) распадается на [l, m) и [m, r)
            build(a, 2 * v, l, m); // дети вершины v – это 2 * v и 2 * v + 1
            build(a, 2 * v + 1, m, r); // строим дерево для них
            T[v] = min(T[2 * v], T[2 * v + 1]); // и получаем в результате минимум для [l, r)
        }
    }

    // процедура поиска минимума: принимает [lq, rq) – границы запроса
    int get_min(int lq, int rq) {
        return get_min(lq, rq, 1, 0, n);
    }

    // внутренняя процедура поиска минимума: принимает границы запроса, вершину и полуинтервал вершины
    int get_min(int lq, int rq, int v, int l, int r) {
        if (r <= lq || rq <= l) { // если оказались за пределами запроса
            return INF; // возвращаем бесконечность
        } else if (lq <= l && r <= rq) { // иначе если оказались целиком внутри запроса
            return T[v]; // возвращаем результат
        } else { // иначе если пересекаемся, но не вкладываемся
            int m = (l + r) / 2; // то разбиваемся пополам
            return min(get_min(lq, rq, 2 * v, l, m),
                       get_min(lq, rq, 2 * v + 1, m, r)); // и отдаем задачу детям
        }
    }

    // присвоить вершине i значение x
    void update(int i, int x) {
        update(i, x, 1, 0, n);
    }

    // внутренняя процедура присвоения в точке: принимает i, x, номер вершины и ее полуинтервал
    void update(int i, int x, int v, int l, int r) {
        if (l == r - 1) { // если оказались в нужном листе
            T[v] = x; // меняем минимум
        } else {
            int m = (l + r) / 2;
            // иначе смотрим, где i – в левом или правом сыне
            if (i < m) {
                update(i, x, 2 * v, l, m);
            } else {
                update(i, x, 2 * v + 1, m, r);
            }
            T[v] = min(T[2 * v], T[2 * v + 1]); // не забываем обновить значение в v
        }
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);

    for (auto& i : a) {
        cin >> i;
    }

    SegmentTree tree(a);
    int q;
    cin >> q;

    while (q-- > 0) {
        int t; // тип запроса
        cin >> t;

        if (t == 1) { // получить минимум на отрезке
            int l, r;
            cin >> l >> r;
            cout << tree.get_min(l - 1, r) << endl;
        } else { // запрос изменения в точке
            int i, x;
            cin >> i >> x;
            tree.update(i - 1, x);
        }
    }
}


/////////////////////



struct SegmentTree {
    int n;
    vector<int> T;

    SegmentTree(const vector<int> &a) {
        n = sz(a);
        T.resize(4 * n);
        build(a, 1, 0, n);
    }

    void build(const vector<int> &a, int v, int l, int r) {
        if (l == r - 1) {
            T[v] = a[l];
        } else {
            int m = (l + r) / 2;
            build(a, 2 * v, l, m);
            build(a, 2 * v + 1, m, r);
            T[v] = min(T[2 * v], T[2 * v + 1]);
        }
    }

    int get_min(int lq, int rq) {
        return get_min(lq, rq, 1, 0, n);
    }

    int get_min(int lq, int rq, int v, int l, int r) {
        if (r <= lq || rq <= l) {
            return INF;
        } else if (lq <= l && r <= rq) {
            return T[v];
        } else {
            int m = (l + r) / 2;
            return min(get_min(lq, rq, 2 * v, l, m),
                    get_min(lq, rq, 2 * v + 1, m, r));
        }
    }

    void update(int i, int x) {
        update(i, x, 1, 0, n);
    }

    void update(int i, int x, int v, int l, int r) {
        if (l == r - 1) {
            T[v] = x;
        } else {
            int m = (l + r) / 2;
            if (i < m) {
                update(i, x, 2 * v, l, m);
            } else {
                update(i, x, 2 * v + 1, m, r);
            }
            T[v] = min(T[2 * v], T[2 * v + 1]);
        }
    }
};

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto & i : a) {
	cin >> i;
    }
    SegmentTree tree(a);


}