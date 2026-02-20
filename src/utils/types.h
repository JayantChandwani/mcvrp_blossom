#pragma once
#include <tuple>
#include <vector>

namespace mcvrp::types {

struct Node {
  int id;
  int demand;
};

struct GraphInput {
  std::vector<Node> nodes;
  std::vector<std::tuple<int, int, int>> edges; // (u, v, weight)
  int capacity;
};

struct MatchingResult {
  std::vector<std::pair<int, int>> matched_edges;
  std::vector<int> edge_weights;
  int total_weight;

  bool is_maximal;
  int num_matched_nodes;
};

} // namespace mcvrp::types