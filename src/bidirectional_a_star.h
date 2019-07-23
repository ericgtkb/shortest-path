//
// Created by Eric Chen on 2019-07-21.
//

#ifndef SHORTESTPATH_BIDIRECTIONAL_A_STAR_H
#define SHORTESTPATH_BIDIRECTIONAL_A_STAR_H

#include "bidirectional_dijkstra.h"




class BidirectionalAStar : public BidirectionalDijkstra {
public:
    BidirectionalAStar();

    void read_graph_and_queries(std::istream& in) override;

private:
    std::vector<std::pair<Length, Length>> coord_;
    std::vector<std::vector<Length>> potential_;

    void initialize() override;
    void clear() override;
    Length get_potential(int u, int side);
    void visit(PQueue& q, int side, int u) override;
    Length get_distance() override;
};



#endif //SHORTESTPATH_BIDIRECTIONAL_A_STAR_H
