//
// Created by Eric Chen on 2019-07-25.
//

#include "a_star.h"


AStar::AStar() : Dijkstra::Dijkstra(), coord_(), potential_() {
}

void AStar::read_graph_and_queries(std::istream& in) {
    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;
    num_vertices_ = num_vertices;
    coord_.resize(num_vertices_);
    for (int i = 0; i < num_vertices_; ++i) {
        Length x, y;
        in >> x >> y;
        coord_[i] = std::make_pair(x, y);
    }
    adj_.resize(num_vertices_);
    weight_.resize(num_vertices_);
    for (int i = 0; i < num_edges; ++i) {
        int u, v, w;
        in >> u >> v >> w;
        adj_[u - 1].push_back(v - 1);
        weight_[u - 1].push_back(w);
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


void AStar::initialize() {
    Dijkstra::initialize();
    potential_.assign(num_vertices_, LLINF);
}


void AStar::clear() {
    for (int u : seen_) {
        distance_[u] = LLINF;
        visited_[u] = false;
        prev_[u] = -1;
        potential_[u] = LLINF;
    }
    seen_.clear();
    path_.clear();
}

AStar::Length AStar::get_potential(int u) {
    if (potential_[u] != LLINF) {
        return potential_[u];
    } else {
        potential_[u] = std::llround(std::sqrt(std::pow(coord_[u].first - coord_[t_].first, 2)
                                                   + std::pow(coord_[u].second - coord_[t_].second, 2)));
        return potential_[u];
    }
}

void AStar::visit(PQueue& q, int u) {
    for (int i = 0; i < adj_[u].size(); ++i) {
        int v = adj_[u][i];
        int w = weight_[u][i];
        Length new_dist = distance_[u] + w - get_potential(u) + get_potential(v);
        if (!visited_[v] && distance_[v] > new_dist) {
            seen_.emplace(v);
            prev_[v] = u;
            distance_[v] = new_dist;
            q.push({distance_[v], v});
        }
    }
}

AStar::Length AStar::find_path(int s, int t) {
    s_ = s;
    t_ = t;
    if (s == t) {
        return 0;
    }
    clear();
    PQueue q{};
    distance_[s] = 0;
    q.push({distance_[s], s});
    seen_.emplace(s);
    while(!q.empty()) {
        int u = q.top().second;
        if (u == t) {
            break;
        }
        q.pop();
        visited_[u] = true;
        visit(q, u);
    }
    int cur = t;
    while (cur != -1) {
        path_.emplace_front(cur);
        cur = prev_[cur];
    }
    return distance_[t] != LLINF ? distance_[t] + potential_[s] : -1;
}
