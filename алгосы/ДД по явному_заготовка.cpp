struct Node {
    int x, y;
    Node* left;
    Node* right;
    Node(int x_) {
        x = x_;
        y = rng();
        left = nullptr;
        right = nullptr;
    }
};

Node* merge(Node* a, Node* b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (a->y < b->y) {
        a->right = merge(a->right, b);
        return a;
    } else {
        b->left = merge(a, b->left);
    }
}

pair<Node*, Node*> split(Node* v, int key) {
    if (v == nullptr) {
        return {nullptr, nullptr};
    }
    if (v->x > key) {
        pair<Node*, Node*> p = split(v->left, key);
        v->left = p.sc;
        return {p.ft, v};
    } else {
        pair<Node*, Node*> p = split(v->right, key);
        v->right = p.ft;
        return {v, p.sc};
    }
}

