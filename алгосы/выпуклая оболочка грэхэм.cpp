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

ll dot (Vec a, Vec b) {
    return a.x * b.x + a.y * b.y;
}

ll cross(Vec a, Vec b) {
    return a.x * b.y - a.y * b.x;
}

bool comp (Vec a, Vec b) {
    if (cross(a, b) > 0) {
        return true;
    } else if (cross(a, b) < 0) {
        return false;
    } else {
        return (a.len() < b.len());
    }
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll n; cin >> n;
    vector<Point> p(n);
    pll left_lower = {LINF, LINF};
    ll ind = -1;
    for (ll i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
        ll x = p[i].x;
        ll y = p[i].y;
        if (pll(x, y) < left_lower) {
            left_lower = pll(x, y);
            ind = i;
        }
    }
    dbg(sz(p));
    swap(p[0], p[ind]);
    sort(next(p.begin()), p.end(), [&p](Point a, Point b){
        Vec v1 = a - p[0];
        Vec v2 = b - p[0];
        return comp(v1, v2);
    });
    vector<Point> stack;
    stack.eb(p[0]);
    stack.eb(p[1]);

    for (ll i = 2; i < n; ++i) {
        Point new_p = p[i];
        while (stack.size() >= 2) {
            Point p0 = stack[stack.size() - 2];
            Point p1 = stack[stack.size() - 1];
            Vec v1 = p1 - p0;
            Vec v2 = new_p - p1;
            if (cross(v1, v2) > 0) {
                break;
            } else {
                stack.pop_back();
            }
        }
        stack.eb(new_p);
    }


    ld ans = 0;
    for (int i = 0; i < sz(stack); ++i) {
        Vec temp = stack[(i + 1) % sz(stack)] - stack[i];
        ans += sqrtl(temp.len());
    }

    cout.precision(30);
    cout << ans;
    cout << e << sz(stack);
    return 0;
}