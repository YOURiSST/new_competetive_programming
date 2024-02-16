class TreeWithLCA {
 private:
  static const int LOG = 21;

  int num_vert;
  int timer;
  int root;

  std::vector<std::vector<int>> adj_list;
  std::vector<int> time_in;
  std::vector<int> time_out;
  std::vector<int> height;
  std::vector<int> pred;
  std::vector<std::vector<int>> bin_pred;

  void DFS(int vert, int cur_pred) {
    pred[vert] = cur_pred;
    time_in[vert] = timer++;
    height[vert] = (pred[vert] == vert ? 0 : height[cur_pred] + 1);
    bin_pred[vert][0] = pred[vert];
    for (int power = 1; power < LOG; ++power) {
      bin_pred[vert][power] = bin_pred[bin_pred[vert][power - 1]][power - 1];
    }

    for (auto& to : adj_list[vert]) {
      if (to != cur_pred) {
        DFS(to, vert);
      }
    }

    time_out[vert] = timer++;
  }

 public:
  TreeWithLCA(int num_vert, const std::vector<Edge>& edges, int root = 0)
      : num_vert(num_vert), root(root) {
    adj_list.resize(num_vert);
    time_in.resize(num_vert);
    time_out.resize(num_vert);
    height.resize(num_vert);
    pred.resize(num_vert);
    bin_pred.resize(num_vert, std::vector<int>(LOG));

    for (auto& [from, to] : edges) {
      adj_list[from].emplace_back(to);
      adj_list[to].emplace_back(from);
    }

    timer = 0;
    DFS(root, root);
  }
  int GetHeight(int vertex) {
    return height[vertex];
  }

  bool IsAncestor(int ft_vert, int sc_vert) {
    return time_in[ft_vert] <= time_in[sc_vert] && time_out[ft_vert] >= time_out[sc_vert];
  }

  int LCA(int ft_vert, int sc_vert) {
    if (IsAncestor(ft_vert, sc_vert)) {
      return ft_vert;
    }
    if (IsAncestor(sc_vert, ft_vert)) {
      return sc_vert;
    }
    for (int power = LOG - 1; power >= 0; --power) {
      if (!IsAncestor(bin_pred[ft_vert][power], sc_vert)) {
        ft_vert = bin_pred[ft_vert][power];
      }
    }
    return pred[ft_vert];
  }
};