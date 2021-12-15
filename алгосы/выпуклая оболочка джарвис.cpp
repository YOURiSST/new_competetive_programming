struct Point {
    ll x, y;
    Point() = default;
    Point(ll x_, ll y_) {
        x = x_;
        y = y_;
    }
};

struct Vec {
    ll x, y;
    Vec() = default;
    Vec(ll x_, ll y_) {
        x = x_;
        y = y_;
    }
    ll len() {
        return x * x + y * y;
    }
};

Vec operator - (Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

ll dot(Vec a, Vec b) {
    return a.x * b.y + a.y * b.y;
}

ll cross(Vec a, Vec b) {
    return a.x * b.y - a.y * b.x;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n, ind = -1; cin >> n;
    pll left_lower = {INF, INF};
    vector<Point> points(n);
    ll counter = 0;
    for (auto & [x, y] : points) {
        cin >> x >> y;
        if (pll(x, y) < left_lower) {
            left_lower = pll(x, y);
            ind = counter;
        }
        counter++;
    }

    swap(points[0], points[ind]);
    Vec v1 = points[1] - points[0];
    Point p1 = points[1];
    for (int i = 2; i < n; ++i) {
        Vec v2 = points[i] - points[0];
        if (cross(v1, v2) <= 0) {
            v1 = v2;
            p1 = points[i];
        }
    }
    vector<Point> stack;
    stack.eb(points[0]);
    stack.eb(p1);
    /*for (auto & i : stack) {
        cout << i.x << " " << i.y << e;
    }
    cout << "=======================\n";
    cout << v1.x << " " << v1.y << e;
    cout << "=======================\n";
    cout << e << e;
    */

    while (true) {
        int j = -1;
        Point last_p = stack.back();
        Vec global_vec;
        for (int i = 0; i < n; ++i) {
            if (j == -1) {
                global_vec = points[i] - last_p;
                j = i;
                
            }
            Vec temp = points[i] - last_p;
            if (cross(temp, global_vec) > 0) {
                
                global_vec = temp;      
                j = i;
            }

        }

        if (j > 0) {
            stack.eb(points[j]);
        } else {
            break;
        }

    }

    /*for (auto & i : stack) {
            cout << i.x << " " << i.y << e;
        }
*/

    ld ans = 0;
    for (int i = 0; i < sz(stack); ++i) {
        Vec v = stack[(i + 1) % sz(stack)] - stack[i];
        ans += sqrtl(v.len());
    }

    cout.precision(30);
    cout << ans;

    return 0;
}