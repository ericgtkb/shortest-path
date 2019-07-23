//
// Created by Eric Chen on 2019-07-22.
//

#include "bidirectional_dijkstra.h"

BidirectionalDijkstra::BidirectionalDijkstra() : num_vertices_(0), s_(-1), t_(-1), adj_(2), weight_(2), queries_(),
        distance_(2), seen_(), visited_(2), prev_(2), path_() {
}

void BidirectionalDijkstra::read_graph_and_queries(std::istream& in) {
    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;
    num_vertices_ = num_vertices;
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

void BidirectionalDijkstra::process_queries(bool print_path) {
    initialize();
    // TODO: for test case 3 only, remove it later
    for (auto query : queries_) {
        std::cout << find_path(query.first, query.second) << "\n";
    }
    // TODO: uncomment
//    for (auto query : queries_) {
//        std::cout << "The length of the shortest path from vertex " << query.first + 1
//                  << " to vertex " << query.second + 1 << " is: "
//                  << find_path(query.first, query.second) << "\n";
//    }
//    if (print_path) {
//        std::cout << "The path is:" << "\n";
//        print_shortest_path();
//    }
}

void BidirectionalDijkstra::initialize() {
    distance_[0].assign(num_vertices_, LLINF);
    distance_[1].assign(num_vertices_, LLINF);
    visited_[0].resize(num_vertices_);
    visited_[1].resize(num_vertices_);
    prev_[0].assign(num_vertices_, -1);
    prev_[1].assign(num_vertices_, -1);
    seen_.reserve(num_vertices_);
    path_.reserve(num_vertices_);
}


void BidirectionalDijkstra::clear() {
    for (int u : seen_) {
        distance_[0][u] = distance_[1][u] = LLINF;
        visited_[0][u] = visited_[1][u] = false;
        prev_[0][u] = prev_[1][u] = -1;
    }
    seen_.clear();
    path_.clear();
}

void BidirectionalDijkstra::visit(PQueue& q, int side, int u) {
    for (int i = 0; i < adj_[side][u].size(); ++i) {
        int v = adj_[side][u][i];
        int w = weight_[side][u][i];
        Length new_dist = distance_[side][u] + w;
        if (!visited_[side][v] && distance_[side][v] > new_dist) {
            seen_.emplace(v);
            distance_[side][v] = new_dist;
            q[side].push({distance_[side][v], v});
        }
    }
}

BidirectionalDijkstra::Length BidirectionalDijkstra::get_distance() {
    Length shortest_dist = LLINF;
    for (int u : seen_) {
        Length cur_dist = distance_[0][u] + distance_[1][u];
        if (shortest_dist > cur_dist) {
            shortest_dist = cur_dist;
        }
    }
    return shortest_dist;
}

BidirectionalDijkstra::Length BidirectionalDijkstra::find_path(int s, int t) {
    s_ = s;
    t_ = t;
    if (s == t) {
        return 0;
    }
    clear();
    PQueue q(2);
    distance_[0][s] = 0;
    distance_[1][t] = 0;
    q[0].push({distance_[0][s], s});
    q[1].push({distance_[1][t], t});
    seen_.emplace(s);
    seen_.emplace(t);
    unsigned side = 0;
    while(!q[side].empty()) {
        int u = q[side].top().second;
        q[side].pop();
        visited_[side][u] = true;
        visit(q, side, u);

        if (visited_[side][u] && visited_[side^1][u]) {
            return get_distance();
        }

        side ^= 1;
    }

    return -1;
}

void BidirectionalDijkstra::print_shortest_path() {
    for (int i = 0; i < path_.size(); ++i) {
        std::cout << path_[i] << (i != path_.size() - 1 ? " " : "\n");
    }
}
