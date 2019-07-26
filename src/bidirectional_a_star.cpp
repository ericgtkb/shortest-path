//
// Created by Eric Chen on 2019-07-21.
//

#include "bidirectional_a_star.h"


BidirectionalAStar::BidirectionalAStar() : BidirectionalDijkstra::BidirectionalDijkstra(),
        coord_(), potential_(2) {
}

void BidirectionalAStar::read_graph_and_queries(std::istream& in) {
    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;
    num_vertices_ = num_vertices;
    coord_.resize(num_vertices_);
    for (int i = 0; i < num_vertices_; ++i) {
        Length x, y;
        in >> x >> y;
        coord_[i] = std::make_pair(x, y);
    }
    adj_[0].resize(num_vertices_);
    adj_[1].resize(num_vertices_);
    weight_[0].resize(num_vertices_);
    weight_[1].resize(num_vertices_);
    for (int i = 0; i < num_edges; ++i) {
        int u, v, w;
        in >> u >> v >> w;
        adj_[0][u - 1].push_back(v - 1);
        weight_[0][u - 1].push_back(w);
        adj_[1][v - 1].push_back(u - 1);
        weight_[1][v - 1].push_back(w);
    }
    int num_queries;
    in >> num_queries;
    queries_.resize(num_queries);
    for (int i = 0; i < num_queries; ++i) {
        int s, t;
        in >> s >> t;
        queries_[i] = std::make_pair(s - 1, t - 1);
    }
}


void BidirectionalAStar::initialize() {
    BidirectionalDijkstra::initialize();
    potential_[0].assign(num_vertices_, LLINF);
    potential_[1].assign(num_vertices_, LLINF);
}


void BidirectionalAStar::clear() {
    for (int u : seen_) {
        distance_[0][u] = distance_[1][u] = LLINF;
        visited_[0][u] = visited_[1][u] = false;
        prev_[0][u] = prev_[1][u] = -1;
        potential_[0][u] = potential_[1][u] = LLINF;
    }
    seen_.clear();
    path_.clear();
}

BidirectionalAStar::Length BidirectionalAStar::get_potential(int u, int side) {
    if (potential_[side][u] != LLINF) {
        return potential_[side][u];
    } else {
        potential_[0][u] = std::llround((std::sqrt(std::pow(coord_[u].first - coord_[t_].first, 2)
                                      + std::pow(coord_[u].second - coord_[t_].second, 2))
                            - std::sqrt(std::pow(coord_[u].first - coord_[s_].first, 2)
                                        + std::pow(coord_[u].second - coord_[s_].second, 2))) / 2);
        potential_[1][u] = -potential_[0][u];
        return potential_[side][u];
    }
}

void BidirectionalAStar::visit(PQueue& q, int side, int u) {
    for (int i = 0; i < adj_[side][u].size(); ++i) {
        int v = adj_[side][u][i];
        int w = weight_[side][u][i];
        Length new_dist = distance_[side][u] + w - get_potential(u, side) + get_potential(v, side);
        if (!visited_[side][v] && distance_[side][v] > new_dist) {
            seen_.emplace(v);
            prev_[side][v] = u;
            distance_[side][v] = new_dist;
            q[side].push({distance_[side][v], v});
        }
    }
}

BidirectionalAStar::Length BidirectionalAStar::get_distance() {
    Length shortest_dist = LLINF;
    int m = -1;
    for (int u : seen_) {
        Length cur_dist = distance_[0][u] + distance_[1][u] + potential_[0][s_] + potential_[1][t_];
        if (shortest_dist > cur_dist) {
            m = u;
            shortest_dist = cur_dist;
        }
    }
    int cur = m;
    while (cur != -1) {
        path_.emplace_front(cur);
        cur = prev_[0][cur];
    }
    cur = m;
    if (cur != -1) {
        cur = prev_[1][cur];
    }
    while (cur != -1) {
        path_.emplace_back(cur);
        cur = prev_[1][cur];
    }
    return shortest_dist;
}



