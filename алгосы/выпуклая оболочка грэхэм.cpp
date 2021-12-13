struct Point {
    ll x, y;
    Point() = default;
    Point(ll x_, ll y_) {
        x = x_;
        y = y_;
    }  
};

struct Vector {
    ll x, y;
    Vector(ll x_, ll y_) {
        x = x_;
        y = y_;
    }
    ll len() {
        return x * x + y * y;
    }
};

Vector operator - (Point a, Point b) {
    return Vector(a.x - b.x, a.y - b.y);
}

ll dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

ll cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool comp (Vector a, Vector b) {
    return (cross(a, b) > 0);
    if (cross(a, b) > 0) {
        return true;
    } else if (cross(a, b) < 0) {
        return false;
    } else {
        return (a.len() < b.len());
    }
}

int main() {
    ll n; cin >> n;
    vector<Point> points(n);
    pll left_lower = {LINF, LINF};
    ll ind = -1;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        if (pll(x, y) < left_lower) {
            left_lower = pll(x, y);
            ind = i;
        }
    }
    swap(points[0], points[ind]);
    sort(points.begin() + 1, points.end(), [&points, &comp](Point a, Point b) {
        Vector v1 = a - points[0];
        Vector v2 = b - points[0];
        return comp(v1, v2);
    });
    vector<Point> stack;
    stack.eb(points[0]);
    stack.eb(points[1]);
    for (int i = 2; i < n; ++i) {
        Point p = points[i];
        while (stack.size() >= 2) {
            Point p0 = stack[stack.size() - 2];
            Point p1 = stack[stack.size() - 1];
            Vector v1(p1 - p0);
            Vector v2(p - p1);
            if (cross(v1, v2) > 0) {
                break;
            } else {
                stack.pop_back();
            }
        }
        stack.eb(p);
    }
    //получился правильный обход
    return 0;
}

