#pragma once
#include <vector>
#include <tuple>

namespace mcvrp::types {

struct GraphInput {
  std::vector<int> nodes;
  std::vector<std::tuple<int, int, int>> edges; // (u, v, weight)
};

struct MatchingResult {
    std::vector<std::pair<int, int>> matched_edges;  
    std::vector<int> edge_weights;                    
    int total_weight;                                 
    
    bool is_maximal; 
    int num_matched_nodes;
};

} // namespace mcvrp::types