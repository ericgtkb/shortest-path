//
// Created by Eric Chen on 2019-07-21.
//

#ifndef SHORTESTPATH_SHORTEST_PATH_SOLVER_H
#define SHORTESTPATH_SHORTEST_PATH_SOLVER_H


#include "shortest_path_algorithm.h"

class ShortestPathSolver {
public:
    ShortestPathSolver();
    void read_graph_and_queries(std::istream& in);
    void process_queries(bool print_path);
    void solve();

private:
    std::unique_ptr<ShortestPathAlgorithm> algorithm;

};


#endif //SHORTESTPATH_SHORTEST_PATH_SOLVER_H
