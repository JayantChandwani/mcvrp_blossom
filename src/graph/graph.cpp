#include "graph/graph.h"
#include <map>

using mcvrp::types::GraphInput;

namespace mcvrp::graph {

void Graph::build_graph(const GraphInput& graph_input) {
    std::map<int, lemon::SmartGraph::Node> node_map;
    for (const auto& node : graph_input.nodes) {
        node_map[node.id] = G.addNode();
    }

    for (const auto& [u, v, w] : graph_input.edges) {
        auto edge = G.addEdge(node_map[u], node_map[v]);
        edge_weights[edge] = w;
    }
}

Graph::Graph(const GraphInput& graph_input) 
    : edge_weights(G) {
    build_graph(graph_input);
}

const lemon::SmartGraph& Graph::get_graph() const { 
    return G; 
}

const lemon::SmartGraph::EdgeMap<int>& Graph::get_weights() const { 
    return edge_weights; 
}

} // namespace mcvrp::graph