#include "test_runner.h"
#include "../utils/edge_filters.h"
#include "../parser/json_parser.h"
#include "../graph/graph.h"
#include "../solver/solver.h"
#include <climits>


namespace {
    int calculate_capacity(const mcvrp::types::GraphInput& input) {
        int max_demand = 0, min_demand = INT_MAX;
        for (const auto& node : input.nodes) {
            if (node.id != 0) {
                max_demand = std::max(max_demand, node.demand);
                min_demand = std::min(min_demand, node.demand);
            }
        }
        return (min_demand + max_demand) / 2;
    }
} 


int main() {
    using namespace mcvrp;
    using namespace mcvrp::experiments;

    std::cout << "=== Scenario 3: demand[i] <= C/2 and K = 2 ===\n\n";

    TestRunner runner;
    std::vector<TestResult> results;

    std::string test_dir = "../data/test_data";

    for (const auto& entry: std::filesystem::directory_iterator(test_dir)) {
        if (entry.path().extension() == ".json") {
            auto filepath = entry.path().string();

            auto input = parser::parse_graph_json(filepath);
            input.capacity = calculate_capacity(input);
            
            auto filtered = filters::apply_weight_constraint(input);

            std::cout << "Testing: " << entry.path().filename() << " (C = " << input.capacity << ")\n";
            results.push_back(runner.run_single_test(filtered, entry.path().filename().string()));
        }
    }
    runner.print_results(results);
    return 0;
}
