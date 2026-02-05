#pragma once
#include <lemon/smart_graph.h>
#include "utils/types.h"

namespace mcvrp::graph {

class Graph {
private:
    lemon::SmartGraph G;
    lemon::SmartGraph::EdgeMap<int> edge_weights;
    
    void build_graph(const types::GraphInput& graph_input);
    
public:
    Graph(const types::GraphInput& graph_input);
    
    const lemon::SmartGraph& get_graph() const;
    const lemon::SmartGraph::EdgeMap<int>& get_weights() const;
};

} // namespace mcvrp::graph