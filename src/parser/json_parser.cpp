#include "json_parser.h"
#include <fstream>
#include <nlohmann/json.hpp>

using mcvrp::types::GraphInput;

namespace mcvrp::parser {

GraphInput parse_graph_json(const std::string &filepath) {
  std::ifstream file(filepath);
  nlohmann::json j;
  file >> j;

  GraphInput input;

  for (const auto& node_json : j["nodes"]) {
    types::Node node;
    node.id = node_json["id"];
    node.demand = node_json["demand"];
    input.nodes.push_back(node);
  }

  for (const auto &edge : j["edges"])
    input.edges.emplace_back(edge["u"].get<int>(), edge["v"].get<int>(),
                             edge["w"].get<int>());

  return input;
}

} // namespace mcvrp::parser