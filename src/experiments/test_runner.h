#pragma once
#include "../utils/types.h"
#include <string>
#include <vector>
#include <filesystem>

namespace mcvrp::experiments {

struct TestResult {
    std::string test_name;
    int total_weight;
    size_t num_edges;
    double runtime_ms;
};

class TestRunner {
public:
    TestResult run_single_test(const types::GraphInput& graph_input, const std::string& test_name);
    void print_results(const std::vector<TestResult>& results);
};

} // namespace mcvrp::experiments
