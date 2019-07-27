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
    bool verbose;
    bool print_path;
    char algo_type;
    std::string filename;
    std::unique_ptr<ShortestPathAlgorithm> algorithm;
    void solve(std::istream&);
    void print_intro();
    void print_help();

};


#endif //SHORTESTPATH_SHORTEST_PATH_SOLVER_H
