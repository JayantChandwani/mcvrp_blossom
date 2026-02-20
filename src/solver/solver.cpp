#include "solver.h"
#include <lemon/matching.h>
#include <iostream>
#include <algorithm>

using mcvrp::types::MatchingResult;
using mcvrp::graph::Graph;

namespace mcvrp::solver {

Solver::Solver() {
    // Empty constructor - no state to initialize
}

MatchingResult Solver::get_minimal_weighted_matching(Graph& G) {
    MatchingResult result;
    
    const auto& graph = G.get_graph();
    const auto& weights = G.get_weights();
    
    int max_weight = 0;
    for (lemon::SmartGraph::EdgeIt e(graph); e != lemon::INVALID; ++e) {
        max_weight = std::max(max_weight, weights[e]);
    }
    
    lemon::SmartGraph::EdgeMap<int> shifted_weights(graph);
    for (lemon::SmartGraph::EdgeIt e(graph); e != lemon::INVALID; ++e) {
        shifted_weights[e] = (max_weight + 1) - weights[e];
    }
    
    lemon::MaxWeightedMatching<lemon::SmartGraph> mwm(graph, shifted_weights);
    mwm.run();
    
    result.total_weight = 0;
    for (lemon::SmartGraph::EdgeIt e(graph); e != lemon::INVALID; ++e) {
        if (mwm.matching(e)) {  
            int u = graph.id(graph.u(e));
            int v = graph.id(graph.v(e));
            int w = weights[e];

            std::cout << "Matched edge: (" << u << ", " << v << ") with weight " << w << std::endl;
            
            result.matched_edges.push_back({u, v});
            result.edge_weights.push_back(w);
            result.total_weight += w;
        }
    }
    
    return result;
}

} // namespace mcvrp::solver
