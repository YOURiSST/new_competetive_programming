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

vector<Point> djarvis (vector<Point> p, ll n, pll left_lower, ll ind) {
    swap(p[ind], p[0]);
    Vec v1 = p[1] - p[0];
    Point p1 = p[1];
    for (int i = 2; i < n; ++i) {
        Vec temp = p[i] - p[0];
        if (cross(v1, temp) < 0) {
            v1 = temp;
            p1 = p[i];
        } else if (cross(temp, v1) == 0 && temp.len() > v1.len()) {
            v1 = temp;
            p1 = p[i];
        }
    } 

    /*for (auto & i : res) {
        cout << i.x << " " << i.y << e;
    }
    cout << "=======================\n";
    cout << v1.x << " " << v1.y << e;
    cout << "=======================\n";
    cout << e << e;*/


    vector<Point> res;
    res.eb(p[0]);
    res.eb(p1);
    while (true) {
        ll j = -1;
        Vec global_vec;
        Point last_p = res.back();
        for (int i = 0; i < n; ++i) {
            if (j == -1) {
                global_vec = p[i] - last_p;
                j = i;
            }
            Vec temp = p[i] - last_p;
            if (cross(global_vec, temp) < 0) {
                global_vec = temp;
                j = i;
            } else if (cross(global_vec, temp) == 0 && temp.len() > global_vec.len()) {
                global_vec = temp;
                j = i;
            }
        }
        dbg(global_vec.x, global_vec.y);
        dbg("metro lublino rabotayem");
        if (j > 0) {
            res.eb(p[j]);
        } else {
            break;
        }

    }
    return res;
}
