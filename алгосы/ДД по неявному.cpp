struct Node {
    int val; //- значение эл-та массива
    ll sum;
    int size;
    int y;
    Node* left;
    Node* right;
    Node(int val_) {
        val = val_;
        sum = val_;
        size = 1;
        y = rng();
        left = nullptr;
        right = nullptr;
    }
};

int getSize(Node* v) {
    return (v == nullptr ? 0 : v->size);    
}

ll getSum(Node* v) {
    return (v == nullptr ? 0 : v->sum);
}

void update(Node* v) {
    v->size = 1 + getSize(v->left) + getSize(v->right);
    v->sum = v->val + getSum(v->left) + getSum(v->right);
}

Node* merge(Node* a, Node* b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (a->y < b->y) { //a - корень
        a->right = merge(a->right, b);
        update(a);
        return a;
    } else {
        b->left = merge(a, b->left);
        update(b);
        return b;
    }
}

pair<Node*, Node*> splitBySize(Node* v, int k) { //первые к вершин - влево 
    if (v == nullptr) {
        return {nullptr, nullptr};
    }
    if (getSize(v->left) >= k) { // сплитим в левом
        pair<Node*, Node*> p = splitBySize(v->left, k);
        v->left = p.sc;
        update(v);
        return {p.ft, v};
    } else {
        pair<Node*, Node*> p = splitBySize(v->right, k - getSize(v->left) - 1);
        v->right = p.ft;
        update(v);
        return {v, p.sc};
    }

}

Node* insert(Node* v, int i, int val) {
    pair<Node*, Node*> p = splitBySize(v, i);
    Node* u = new Node(val);
    return merge(p.ft, merge(u, p.sc));
}

Node* erase(Node* v, int i) {
    pair<Node*, Node*> p = splitBySize(v, i + 1);
    pair<Node*, Node*> q = splitBySize(p.ft, i);
    return merge(q.ft, p.sc);
}

ll sum(Node* v, int lq, int rq) {
    pair<Node*, Node*> p = splitBySize(v, rq + 1);
    pair<Node*, Node*> q = splitBySize(p.ft, lq);
    ll ans = getSum(q.sc);
    v = merge(q.ft, merge(q.sc, p.sc));
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //делаем корень
    //Node* root = nullptr;
    //вставить val на позицию
    //root = insert(root, i, val);
    //удалить i ый
    //root = erase(root, i);
    //найти сумму
    //cout << sum(root, l, r);
    //
    dbg(Time);
    return 0;
}