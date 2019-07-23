//
// Created by Eric Chen on 2019-07-21.
//

#include "shortestpath/shortest_path_solver.h"
#include "bidirectional_a_star.h"

ShortestPathSolver::ShortestPathSolver() {
    algorithm = std::make_unique<BidirectionalAStar>();
}

void ShortestPathSolver::read_graph_and_queries(std::istream& in) {
    algorithm->read_graph_and_queries(in);

}

void ShortestPathSolver::process_queries(bool print_path) {
    algorithm->process_queries(print_path);
}

void ShortestPathSolver::solve() {
    read_graph_and_queries(std::cin);
    process_queries(true);
}
