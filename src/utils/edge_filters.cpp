#include "utils/edge_filters.h"
#include <algorithm>
#include <map>

namespace mcvrp::filters {
    types::GraphInput apply_weight_constraint(const types::GraphInput& input)
    {
        types::GraphInput result = input;
        result.nodes = input.nodes;
        result.capacity = input.capacity;

        std::map<int, int> node_demand;
        for(const auto& node: input.nodes) {
            node_demand[node.id] = node.demand;
        }

        for (const auto& [u, v, w]: input.edges) {
            // keep depot edges
            if (u == 0 || v == 0) {
                result.edges.emplace_back(u, v, w);
            }
            else if (node_demand[u] + node_demand[v] <= input.capacity) {
                result.edges.emplace_back(u, v, w);
            }
        }

        return result;
    }
} // namespace mcvrp::filters
