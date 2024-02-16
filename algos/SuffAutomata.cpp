#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <typename Cont>
int Size(const Cont& cont) {
  return static_cast<int>(cont.size());
}

void FastIOS() {
#ifdef LOCAL
  freopen("inputf.in", "r", stdin);
  freopen("outputf.out", "w", stdout);
#endif
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

namespace SufAutSpace {

/// const int kMaxL = 100'000;
const int kAlphabet = 26;
constexpr char kFirstSymbol = 'a';

struct SufNode {
  int len;
  int pred;
  int link;
  std::vector<int> trans;
  bool is_term = false;
  int cnt_ft;
  int cnt_sc;
  SufNode() : len(0), link(-1), pred(-1), trans(kAlphabet, -1) {}
  SufNode(int len, int pred = -1, int link = -1)
      : len(len), pred(pred), link(link), trans(kAlphabet, -1) {}
  SufNode(int len, int pred, const SufNode& destination)
      : len(len),
        pred(pred),  /// ? correct ?
        link(destination.link),
        trans(destination.trans) {}
};
/// !implement field to save parent of each SufNode!
/// ? done ?
class SufAutomaton {
 private:
  int last_ = 0;

 public:
  std::vector<SufNode> nodes;
  SufAutomaton(const std::string& to_build) {
    nodes.reserve(2 * to_build.size());
    nodes.emplace_back();
    for (auto cur_ch : to_build) {
      Extend(cur_ch - kFirstSymbol);
    }
    MakeTerms();
  }

  void Extend(int to_add) {
    int current = Size(nodes);
    nodes.emplace_back(nodes[last_].len + 1, to_add);
    int parent = last_;
    while (parent != -1 && nodes[parent].trans[to_add] == -1) {
      nodes[parent].trans[to_add] = current;
      parent = nodes[parent].link;
    }
    if (parent == -1) {
      nodes[current].link = 0;
      last_ = current;
      return;
    }
    int destination = nodes[parent].trans[to_add];
    if (nodes[parent].len + 1 == nodes[destination].len) {
      nodes[current].link = destination;
      last_ = current;
      return;
    }
    int clone = Size(nodes);
    nodes.emplace_back(nodes[parent].len + 1, to_add, nodes[destination]);

    assert(nodes.back().pred == to_add);
    while (parent != -1 && nodes[parent].trans[to_add] == destination) {
      nodes[parent].trans[to_add] = clone;
      parent = nodes[parent].link;
    }
    nodes[destination].link = clone;
    nodes[current].link = clone;
    last_ = current;
  }

  void MakeTerms() {
    int current = last_;
    while (current != -1) {
      nodes[current].is_term = true;
      current = nodes[current].link;
    }
  }
};

}  // namespace SufAutSpace
using namespace SufAutSpace;

signed main() {
  FastIOS();
  std::string kek = "ababsdjdkasdjask";
  SufAutomaton suf_automaton(kek);



  return 0;
}

//////////////////////////////////////////////////////


/// automata where first and last vhojdeniye in each vertex counted:

namespace SufAutSpace {

/// const int kMaxL = 100'000;
const int kAlphabet = 26;
constexpr char kFirstSymbol = 'a';

struct SufNode {
  int len;
  int pred;
  int link;
  std::vector<int> trans;
  bool is_term = false;
  int cnt_ft = 0;
  int cnt_sc = -1;
  SufNode() : len(0), link(-1), pred(-1), trans(kAlphabet, -1) {}
  SufNode(int len, int pred = -1, int link = -1)
      : len(len), pred(pred), link(link), trans(kAlphabet, -1), cnt_ft(len) {}
  SufNode(int len, int pred, const SufNode& destination)
      : len(len),
        pred(pred),  /// ? correct ?
        link(destination.link),
        trans(destination.trans),
        cnt_ft(destination.cnt_ft) {}
};

class SufAutomaton {
 private:
  int last_ = 0;

 public:
  std::vector<SufNode> nodes;
  std::vector<std::vector<int>> suff_tree;
  SufAutomaton(const std::string& to_build) {
    nodes.reserve(2 * to_build.size());
    nodes.emplace_back();
    for (auto cur_ch : to_build) {
      Extend(cur_ch - kFirstSymbol);
    }
    MakeTerms();
  }

  void Extend(int to_add) {
    int current = Size(nodes);
    nodes.emplace_back(nodes[last_].len + 1, to_add);
    int parent = last_;
    while (parent != -1 && nodes[parent].trans[to_add] == -1) {
      nodes[parent].trans[to_add] = current;
      parent = nodes[parent].link;
    }
    if (parent == -1) {
      nodes[current].link = 0;
      last_ = current;
      return;
    }
    int destination = nodes[parent].trans[to_add];
    if (nodes[parent].len + 1 == nodes[destination].len) {
      nodes[current].link = destination;
      last_ = current;
      return;
    }
    int clone = Size(nodes);
    nodes.emplace_back(nodes[parent].len + 1, to_add, nodes[destination]);

    while (parent != -1 && nodes[parent].trans[to_add] == destination) {
      nodes[parent].trans[to_add] = clone;
      parent = nodes[parent].link;
    }
    nodes[destination].link = clone;
    nodes[current].link = clone;
    last_ = current;
  }

  void MakeTerms() {
    int current = last_;
    while (current != -1) {
      nodes[current].is_term = true;
      current = nodes[current].link;
    }
  }

  void DFS(int vertex) {
    nodes[vertex].cnt_sc = nodes[vertex].cnt_ft;
    for (auto& to : suff_tree[vertex]) {
      DFS(to);
      nodes[vertex].cnt_sc = std::max(nodes[vertex].cnt_sc, nodes[to].cnt_sc);
    }
  }

  void MakeTree() {
    suff_tree.resize(nodes.size());
    for (int i = 1; i < Size(nodes); ++i) {
      suff_tree[nodes[i].link].emplace_back(i);
    }
    DFS(0);
  };
};

}  // namespace SufAutSpace
