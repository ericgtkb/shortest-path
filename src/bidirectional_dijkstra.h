//
// Created by Eric Chen on 2019-07-22.
//

#ifndef SHORTESTPATH_BIDIRECTIONAL_DIJKSTRA_H
#define SHORTESTPATH_BIDIRECTIONAL_DIJKSTRA_H

#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <queue>
#include <limits>
#include "shortestpath/shortest_path_algorithm.h"


class BidirectionalDijkstra : public ShortestPathAlgorithm {
public:
    BidirectionalDijkstra();

    virtual void read_graph_and_queries(std::istream& in) override;
    virtual void process_queries(bool print_path) override;

protected:
    // Divided by 4 to prevent overflow from LLINF + LLINF in the get_distance() method
    constexpr static long long LLINF = std::numeric_limits<long long>::max() / 4;
    using Length = long long;
    using PQueue = std::vector<std::priority_queue<std::pair<Length, int>, std::vector<std::pair<Length, int>>,
            std::greater<>>>;
    int num_vertices_;
    int s_, t_;
    std::vector<std::vector<std::vector<int>>> adj_;
    std::vector<std::vector<std::vector<int>>> weight_;
    std::vector<std::pair<int, int>> queries_;
    std::vector<std::vector<Length>> distance_;
    std::unordered_set<int> seen_;
    std::vector<std::vector<bool>> visited_;
    std::vector<std::vector<int>> prev_;
    std::deque<int> path_;

    virtual void initialize();
    virtual void clear();
    virtual void visit(PQueue& q, int side, int u);
    virtual Length get_distance();
    virtual Length find_path(int s, int t);
    void print_shortest_path();
};




#endif //SHORTESTPATH_BIDIRECTIONAL_DIJKSTRA_H
