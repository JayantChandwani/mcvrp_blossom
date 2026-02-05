#include "json_parser.h"
#include <fstream>
#include <nlohmann/json.hpp>

using mcvrp::types::GraphInput;  // At the top

namespace mcvrp::parser {

GraphInput parse_graph_json(const std::string &filepath) {
  std::ifstream file(filepath);
  nlohmann::json j;
  file >> j;

  GraphInput input;
  input.nodes = j["nodes"].get<std::vector<int>>();

  for (const auto &edge : j["edges"])
    input.edges.emplace_back(edge["u"].get<int>(), edge["v"].get<int>(),
                             edge["w"].get<int>());

  return input;
}

} // namespace mcvrp::parser