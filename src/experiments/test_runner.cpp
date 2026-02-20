#include "test_runner.h"
#include "../parser/json_parser.h"
#include "../graph/graph.h"
#include "../solver/solver.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <numeric>

namespace mcvrp::experiments {

TestResult TestRunner::run_single_test(const types::GraphInput& graph_input, const std::string& test_name) {
    TestResult result;
    result.test_name = test_name;
    result.num_edges = graph_input.edges.size();
    
    graph::Graph G(graph_input);
    
    auto start = std::chrono::high_resolution_clock::now();
    solver::Solver solver;
    auto matching = solver.get_minimal_weighted_matching(G);
    auto end = std::chrono::high_resolution_clock::now();
    
    result.total_weight = matching.total_weight;

    
    result.runtime_ms = std::chrono::duration<double, std::milli>(end - start).count();
    
    return result;
}

void TestRunner::print_results(const std::vector<TestResult>& results) {
    std::cout << "\n" << std::string(85, '=') << "\n";
    std::cout << "                           TEST RESULTS\n";
    std::cout << std::string(85, '=') << "\n";
    
    // Header
    std::cout << std::left << std::setw(25) << "Test Name"
              << std::right << std::setw(12) << "Total Distance"
              << std::setw(12) << "Edges"
              << std::setw(15) << "Time (ms)" << "\n";
    std::cout << std::string(85, '-') << "\n";
    
    // Data rows
    for (const auto& r : results) {
        std::cout << std::left << std::setw(25) << r.test_name
                  << std::right << std::setw(12) << r.total_weight
                  << std::setw(12) << r.num_edges
                  << std::fixed << std::setprecision(3) 
                  << std::setw(15) << r.runtime_ms << "\n";
    }
    
    std::cout << std::string(85, '=') << "\n\n";
}

} // namespace mcvrp::experiments