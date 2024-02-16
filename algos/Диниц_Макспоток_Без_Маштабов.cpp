struct Destination {
  int to;
  int64_t capacity;
  Destination() = default;
  Destination(int to, int64_t capacity) : to(to), capacity(capacity) {}
};

struct DinicDestination {
  int to;
  int64_t flow;
  int64_t capacity;
  int reverse_index;
  DinicDestination() = default;
  DinicDestination(int to, int64_t flow, int64_t capacity, int reverse_index) :
      to(to), flow(flow), capacity(capacity), reverse_index(reverse_index) {}
};

class DinicGraph {
 private:
  constexpr static int64_t MAX_FLOW = 1000ll * 1000 * 1000 * 1000 * 1000;
  int num_vert;
  std::vector<int> levels; // current s-v distances
  std::vector<std::vector<DinicDestination>> adj_list;
 public:
  explicit DinicGraph(int num_vert) : num_vert(num_vert) {
    adj_list.resize(num_vert);
    levels.resize(num_vert, -1);
  }

  DinicGraph(int num_vert, const std::vector<std::vector<Destination>>& default_adj_list) : num_vert(num_vert) {
    adj_list.resize(num_vert);
    levels.resize(num_vert, -1);
    for (int from = 0; from < num_vert; ++from) {
      for (auto& [to, capacity] : default_adj_list[from]) {
        AddEdge(from, to, capacity);
      }
    }
  }

  void AddEdge(int from, int to, int64_t capacity) {
    DinicDestination destination_to(to, 0, capacity, static_cast<int>(adj_list[to].size()));
    DinicDestination destination_from(from, 0, 0, static_cast<int>(adj_list[from].size())); // reverse_dest
    adj_list[from].emplace_back(destination_to);
    adj_list[to].emplace_back(destination_from);
  }

  bool BFS(int source, int sink) {
    levels.assign(num_vert, -1);
    levels[source] = 0;
    std::queue<int> bfs_q;
    bfs_q.push(source);
    while (!bfs_q.empty()) {
      int from = bfs_q.front();
      bfs_q.pop();
      for (auto& [to, edge_flow, capacity, reverse_index] : adj_list[from]) {

        if (levels[to] < 0 && edge_flow < capacity) {
          levels[to] = levels[from] + 1;
          bfs_q.push(to);
        }
      }
    }
    return levels[sink] != -1; // levels[sink] is achievable
  }

  int64_t PushFlow(int vertex, int64_t flow, int sink, std::vector<int>& first_unused) {
    if (vertex == sink) {
      return flow;
    }
    for (; first_unused[vertex] < adj_list[vertex].size(); ++first_unused[vertex]) {
      auto& [to, edge_flow, capacity, reverse_index] =
          adj_list[vertex][first_unused[vertex]]; // TODO: check if & is true
      if (levels[to] == levels[vertex] + 1 && edge_flow < capacity) {
        int64_t current_flow = std::min(flow, capacity - edge_flow);
        int64_t added_flow = PushFlow(to, current_flow, sink, first_unused);
        if (added_flow > 0) {
          if (vertex == 0) {
          }
          edge_flow += added_flow;
          adj_list[to][reverse_index].flow -= added_flow;
          if (vertex == 0) {
          }
          return added_flow;
        }
      }
    }
    return 0;
  }

  int64_t GetMaxFlow(int source, int sink) {
    int64_t answer = 0;
    std::vector<int> first_unused(num_vert + 1, 0);
    while (BFS(source, sink)) {
      first_unused.assign(num_vert + 1, 0);
      int64_t added_flow;
      do {
        added_flow = PushFlow(source, MAX_FLOW, sink, first_unused);
        answer += added_flow;
      } while (added_flow > 0);
    }
    return answer;
  }
};