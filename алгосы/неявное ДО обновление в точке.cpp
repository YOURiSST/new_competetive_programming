struct Node {
    int l, r, sum;
    Node* left;
    Node* right;
    Node(int l_, int r_) {
        l = l_;
        r = r_;
        sum = 0;
        left = right = nullptr;
    }
};

struct ImplicitSegTreeSum {
    Node* root;
    
    ImplicitSegTreeSum(int n) {
        root = new Node(0, n);
    }
    
    int get_sum(int lq, int rq) {
        return get_sum(lq, rq, root);
    }
    
    int get_sum(int lq, int rq, Node* vertex) {
        if (!vertex || rq <= vertex->l || vertex->r <= lq) {
            return 0;
        }
        if (lq <= vertex->l && vertex->r <= rq) {
            return vertex->sum;
        }
        return get_sum(lq, rq, vertex->left) + get_sum(lq, rq, vertex->right);
    } 
    
    void update(int i, int x) {
        update(i, x, root);
    }
    
    void update(int i, int x, Node* vertex) {
        if (vertex->l == vertex->r - 1) {
            vertex->sum = x;
            return;
        }
        int mid = (vertex->l + vertex->r) / 2;
        if (i < mid) {
            if (!vertex->left)
                vertex->left = new Node(vertex->l, mid);
            update(i, x, vertex->left);    
        } else {
            if (!vertex->right)
                vertex->right = new Node(mid, vertex->r);
            update(i, x, vertex->right);
        }
        vertex->sum = (vertex->left ? vertex->left->sum : 0) + (vertex->right ? vertex->right->sum : 0);
    }
};