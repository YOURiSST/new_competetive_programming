namespace AhoCorasick {

static constexpr u_int32_t kAlphabet = 26;
static constexpr char kFirstSymbol = 'a';

struct Node {
  std::array<Node*, kAlphabet> corasick_destination{};

  Node* suffix_link = nullptr;
  Node* compressed_suffix_link = nullptr;

  bool is_term = false;
  u_int32_t terminals_under_this = 0;

  Node* pred = nullptr;
  u_int32_t pred_symbol = -1;

  std::vector<u_int32_t> str_nums;

  Node() {}

  Node(Node* pred, ssize_t pred_symbol)
      : pred(pred), pred_symbol(pred_symbol) {}
};

struct Corasick {
  std::vector<Node*> nodes;  // ! first node is **always** the root
  Corasick() { nodes.emplace_back(new Node(nullptr, -1)); }

  Corasick(const std::vector<std::string>& templates) {
    nodes.emplace_back(new Node(nullptr, -1));
    for (u_int32_t i = 0; i < templates.size(); ++i) {
      AddString(templates[i], i);
    }
  }

  void AddString(const std::string& str, ssize_t num = -1) {
    Node* cur_node = GetRoot();
    for (auto ch : str) {
      if (cur_node->corasick_destination[ch - kFirstSymbol] == nullptr) {
        cur_node->corasick_destination[ch - kFirstSymbol] =
            nodes.emplace_back(new Node(cur_node, ch - kFirstSymbol));
      }
      ++cur_node->terminals_under_this;
      cur_node = cur_node->corasick_destination[ch - kFirstSymbol];
    }
    ++cur_node->terminals_under_this;
    cur_node->is_term = true;
    if (num != -1) {
      cur_node->str_nums.emplace_back(num);
    }
  }

  void SetLink(Node* to_set) {
    if (to_set == GetRoot() || to_set->pred == GetRoot()) {
      to_set->suffix_link = GetRoot();
      return;
    }
    to_set->suffix_link =
        to_set->pred->suffix_link->corasick_destination[to_set->pred_symbol];
  }

  void FillCorasickDestinations(Node* to_fill) {
    for (u_int32_t i = 0; i < kAlphabet; ++i) {
      to_fill->corasick_destination[i] = to_fill->corasick_destination[i];
      if (to_fill->corasick_destination[i] == nullptr) {
        if (to_fill == GetRoot()) {
          to_fill->corasick_destination[i] = GetRoot();
          continue;
        }
        to_fill->corasick_destination[i] =
            to_fill->suffix_link->corasick_destination[i];
      }
    }
  }

  void SetCompressedLink(Node* to_set) {
    if (to_set == GetRoot() || to_set->suffix_link == GetRoot()) {
      to_set->compressed_suffix_link = GetRoot();
      return;
    }
    if (to_set->suffix_link->is_term) {
      to_set->compressed_suffix_link = to_set->suffix_link;
      return;
    }
    to_set->compressed_suffix_link =
        to_set->suffix_link->compressed_suffix_link;
  }

  void MakeAutomata() {
    std::queue<Node*> node_queue;
    node_queue.push(GetRoot());

    while (!node_queue.empty()) {
      Node* cur = node_queue.front();

      for (u_int32_t i = 0; i < kAlphabet; ++i) {
        Node* next = cur->corasick_destination[i];
        if (next == nullptr) {
          continue;
        }
        node_queue.push(next);
      }

      SetLink(cur);
      FillCorasickDestinations(cur);
      SetCompressedLink(cur);

      node_queue.pop();
    }
  };

  Node* GetRoot() {
    try {
      return nodes.front();
    } catch (...) {
      throw std::out_of_range("we don't have a root!");
    }
  }

  ~Corasick() {
    for (auto& node : nodes) {
      delete node;
    }
  }
};

}  // namespace AhoCorasick
