//
// Created by Eric Chen on 2019-07-21.
//

#ifndef SHORTESTPATH_SHORTEST_PATH_SOLVER_H
#define SHORTESTPATH_SHORTEST_PATH_SOLVER_H


#include "shortest_path_algorithm.h"

class ShortestPathSolver {
public:
    ShortestPathSolver(int argc, char* argv[]);

private:
    std::unique_ptr<ShortestPathAlgorithm> algorithm;
    void read_graph_and_queries(std::istream& in);
    void process_queries(bool print_path);
    void solve(std::istream& in);
    void print_intro(char c);

};


#endif //SHORTESTPATH_SHORTEST_PATH_SOLVER_H
