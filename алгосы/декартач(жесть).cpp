struct Node {
    ll x, y, cnt;
    Node* l;
    Node* r;

    Node (ll x_) {
        x = x_;
        y = rng();
        l = NULL;
        r = NULL;
    }
};

int cnt (Node* t) {
    return t ? t->cnt : 0;
}
void upd_cnt (Node* t) {
    if (t) { t->cnt = 1 + cnt(t->l) + cnt (t->r); }
}


void split(Node* t, Node*& l, Node*& r, ll x) {
    if (!t) {
        l = NULL;
        r = NULL;
        upd_cnt(t);
        return;
    }

    if (t->x < x) {
        split(t->r, t->r, r, x);
        l = t;
    } else {    
        split(t->l, l, t->l, x);
        r = t;
    }
    upd_cnt(t);
};

void merge(Node*& t, Node* l, Node* r) {
    if (!r) { t = l; upd_cnt(t); return; }
    if (!l) { t = r; upd_cnt(t); return; }
    if (l->y > r->y) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
    upd_cnt(t);
}

void insert(Node*& t, Node* v) {
    if (!t) {
        t = v;
        upd_cnt(t);
        return;
    }
    if (t->y > v->y) {
        if (v->x < t->x) {
            insert(t->l, v);
        }
        else {
            insert(t->r, v);
        }
        upd_cnt(t);
        return;
    }

    split(t, v->l, v->r, v->x);
    t = v;
    upd_cnt(t);
}

void remove(Node*& t, ll x) {
    if (!t) {
        upd_cnt(t);
        return;
    }
    if (x < t->x) {
        remove(t->l, x);
    } else if (x > t->x) {
        remove(t->r, x);
    } else {
        merge(t, t->l, t->r);
    }
    upd_cnt(t);
}


bool exists(Node*& t, ll x) {
    if (!t) return false;
    if (t->x == x) return true;
    if (x < t->x) {
        return exists(t->l, x);
    } else {
        return exists(t->r, x);
    }
}

Node* prev(Node*& t, ll x) {
    Node* cur = t;
    Node* res = NULL;

    while (cur) {
        if (cur->x < x) {
            res = cur;
            cur = cur->r;
        } else {
            cur = cur->l;
        }
    }

    return res;
}

Node* next(Node*& t, ll x) {
    Node* cur = t;
    Node* res = NULL;

    while (cur) {
        if (cur->x > x) {
            res = cur;
            cur = cur->l;
        } else {
            cur = cur->r;
        }
        
    }

    return res;
}


int kth(Node* v, ll k) {
    //assert(v != nullptr);
    ll root_number = cnt(v->l);
    if (root_number == k)
        return v->x;
    if (k < root_number)
        return kth(v->l, k);
    else
        return kth(v->r, k - root_number - 1);
}

