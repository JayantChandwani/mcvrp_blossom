#include "parser/json_parser.h"
#include "graph/graph.h"
#include "solver/solver.h"
#include <lemon/connectivity.h>
#include <iostream>

int main() {
  // Test the JSON parser
  auto graph_input = mcvrp::parser::parse_graph_json("../data/test_data/test_1.json");

  std::cout << "Parsed graph with " << graph_input.nodes.size() << " nodes\n";
  std::cout << "Nodes: ";
  for (int node : graph_input.nodes) {
    std::cout << node << " ";
  }
  std::cout << "\n\nEdges:\n";

  for (const auto &[u, v, w] : graph_input.edges) {
    std::cout << "  " << u << " -- " << v << " (weight: " << w << ")\n";
  }

  // Test Graph class
  std::cout << "\n--- Testing Graph Class ---\n";
  mcvrp::graph::Graph graph(graph_input);
  
  const auto& G = graph.get_graph();
  const auto& weights = graph.get_weights();
  
  std::cout << "Graph has " << lemon::countNodes(G) << " nodes and "
            << lemon::countEdges(G) << " edges\n";
  
  std::cout << "Edge weights:\n";
  for (lemon::SmartGraph::EdgeIt e(G); e != lemon::INVALID; ++e) {
    std::cout << "  Edge weight: " << weights[e] << "\n";
  }

  // Testing Solver
  std::cout << "\n--- Testing Solver ---\n";
  mcvrp::solver::Solver solver;
  auto matching_result = solver.get_minimal_weighted_matching(graph);

  std::cout << "Total weight of minimal weighted matching: " << matching_result.total_weight << "\n";
  std::cout << "Matched edges:\n";
  for (size_t i = 0; i < matching_result.matched_edges.size(); ++i) {
    const auto& edge = matching_result.matched_edges[i];
    int weight = matching_result.edge_weights[i];
    std::cout << "  " << edge.first << " -- " << edge.second << " (weight: " << weight << ")\n";
  }

  return 0;
}
