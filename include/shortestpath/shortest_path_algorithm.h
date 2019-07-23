//
// Created by Eric Chen on 2019-07-21.
//

#ifndef SHORTESTPATH_SHORTEST_PATH_ALGORITHM_H
#define SHORTESTPATH_SHORTEST_PATH_ALGORITHM_H

#include <iostream>

class ShortestPathAlgorithm {
public:
    virtual ~ShortestPathAlgorithm() = default;
    virtual void read_graph_and_queries(std::istream& in) = 0;
    virtual void process_queries(bool print_path) = 0;
};


#endif //SHORTESTPATH_SHORTEST_PATH_ALGORITHM_H
