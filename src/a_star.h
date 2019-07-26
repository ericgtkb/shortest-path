//
// Created by Eric Chen on 2019-07-25.
//

#ifndef SHORTESTPATH_A_STAR_H
#define SHORTESTPATH_A_STAR_H


#include "dijkstra.h"

class AStar : public Dijkstra {
public:
    AStar();

    void read_graph_and_queries(std::istream& in) override;

private:
    std::vector<std::pair<Length, Length>> coord_;
    std::vector<Length> potential_;

    void initialize() override;
    void clear() override;
    Length get_potential(int u);
    void visit(PQueue& q, int u) override;
    Length find_path(int s, int t) override;
};


#endif //SHORTESTPATH_A_STAR_H
