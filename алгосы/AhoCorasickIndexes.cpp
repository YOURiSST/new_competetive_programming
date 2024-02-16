namespace AhoCorasick {

static constexpr int kAlphabet = 26;
static constexpr char kFirstSymbol = 'a';

struct Node {
  std::vector<int> trie_destination;
  std::vector<int> corasick_destination;

  int suffix_link = -1;
  int compressed_suffix_link = -1;

  bool is_term = false;
  int terminals_under_this = 0;

  int pred = -1;
  int pred_symbol = -1;

  std::vector<std::pair<int, int>> str_nums;

  Node() : corasick_destination(kAlphabet, -1) {}

  Node(int pred, int pred_symbol)
      : corasick_destination(kAlphabet, -1),
        pred(pred),
        pred_symbol(pred_symbol) {}
};

struct Corasick {
  // std::vector<Node*> nodes;  // ! first node is **always** the root
  std::vector<Node> nodes;
  Corasick() { nodes.emplace_back(-1, -1); }

  Corasick(const std::vector<std::string>& templates) {
    nodes.emplace_back(-1, -1);
    for (int i = 0; i < static_cast<int>(templates.size()); ++i) {
      AddString(templates[i], i, templates[i].size());
    }
  }

  int& SuffLink(int node) { return nodes[node].suffix_link; }

  int& Pred(int node) { return nodes[node].pred; }

  int& Terminals(int node) { return nodes[node].terminals_under_this; }

  int& Compressed(int node) { return nodes[node].compressed_suffix_link; }

  int& PredSym(int node) { return nodes[node].pred_symbol; }

  bool& IsTerminal(int node) { return nodes[node].is_term; }

  int& TriDest(int node, int sym) {  // ! todo: check it!
    return nodes[node].trie_destination[sym];
  }

  int& CorDest(int node, int sym) {
    return nodes[node].corasick_destination[sym];
  }

  std::vector<std::pair<int, int>>& StrNums(int cur_node) {
    return nodes[cur_node].str_nums;
  }

  void AddString(const std::string& str, int num = -1, int size = 0) {
    int cur_node = GetRoot();
    for (auto ch : str) {
      if (CorDest(cur_node, ch - kFirstSymbol) == -1) {
        nodes.emplace_back(cur_node, ch - kFirstSymbol);
        CorDest(cur_node, ch - kFirstSymbol) = nodes.size() - 1;
      }
      ++Terminals(cur_node);
      cur_node = CorDest(cur_node, ch - kFirstSymbol);
    }
    ++Terminals(cur_node);
    IsTerminal(cur_node) = true;
    if (num != -1) {
      StrNums(cur_node).emplace_back(num, size);
    }
  }

  void SetLink(int to_set) {
    if (to_set == GetRoot() || Pred(to_set) == GetRoot()) {
      SuffLink(to_set) = GetRoot();
      return;
    }
    SuffLink(to_set) = CorDest(SuffLink(Pred(to_set)), PredSym(to_set));
  }

  void FillCorasickDestinations(int to_fill) {
    for (int i = 0; i < kAlphabet; ++i) {
      CorDest(to_fill, i) = CorDest(to_fill, i);
      if (CorDest(to_fill, i) == -1) {
        if (to_fill == GetRoot()) {
          CorDest(to_fill, i) = GetRoot();
          continue;
        }
        CorDest(to_fill, i) = CorDest(SuffLink(to_fill), i);
      }
    }
  }

  void SetCompressedLink(int to_set) {
    if (to_set == GetRoot() || SuffLink(to_set) == GetRoot()) {
      Compressed(to_set) = GetRoot();
      return;
    }
    if (IsTerminal(SuffLink(to_set))) {
      Compressed(to_set) = SuffLink(to_set);
      return;
    }
    Compressed(to_set) = Compressed(SuffLink(to_set));
  }

  void MakeAutomata() {
    std::queue<int> node_queue;
    node_queue.push(GetRoot());
    //    SetLink(GetRoot());
    //    FillCorasickDestinations(GetRoot());
    //    SetCompressedLink(GetRoot());
    while (!node_queue.empty()) {
      int cur = node_queue.front();

      for (int i = 0; i < kAlphabet; ++i) {
        int next = CorDest(cur, i);
        if (next == -1) {
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

  int GetRoot() const {
    assert(!nodes.empty());
    return 0;
  }

  ~Corasick() {}
};

}  // namespace AhoCorasick

