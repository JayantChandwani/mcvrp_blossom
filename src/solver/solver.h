#pragma once
#include "../graph/graph.h"
#include "../utils/types.h"

namespace mcvrp::solver {
class Solver {
public:
  Solver();

  mcvrp::types::MatchingResult
  get_minimal_weighted_matching(mcvrp::graph::Graph &G);

};

} // namespace mcvrp::solver
