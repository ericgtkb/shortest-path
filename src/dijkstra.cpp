//
// Created by Eric Chen on 2019-07-25.
//

#include "dijkstra.h"

Dijkstra::Dijkstra() : num_vertices_(0), s_(-1), t_(-1), adj_(), weight_(), queries_(),
        distance_(), seen_(), visited_(), prev_(), path_() {
}

void Dijkstra::read_graph_and_queries(std::istream& in) {
    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;
    num_vertices_ = num_vertices;
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

void Dijkstra::process_queries(bool print_path) {
    initialize();
    // TODO: for test case 3 only, remove it later
//    for (auto query : queries_) {
//        std::cout << find_path(query.first, query.second) << "\n";
//    }
    // TODO: uncomment
    for (auto query : queries_) {
        Length dist = find_path(query.first, query.second);
        std::cout << "The length of the shortest path from vertex " << query.first + 1
                  << " to vertex " << query.second + 1 << " is: "
                  << dist << "\n";
        if (print_path) {
            if (dist == -1) {
                std::cout << "There is no path" << "\n";
            } else {
                std::cout << "The path is:" << "\n";
                print_shortest_path();
            }
        }
    }
}

void Dijkstra::initialize() {
    distance_.assign(num_vertices_, LLINF);
    visited_.resize(num_vertices_);
    prev_.assign(num_vertices_, -1);
    seen_.reserve(num_vertices_);
}


void Dijkstra::clear() {
    for (int u : seen_) {
        distance_[u] = LLINF;
        visited_[u] = false;
        prev_[u] = -1;
    }
    seen_.clear();
    path_.clear();
}

void Dijkstra::visit(PQueue& q, int u) {
    for (int i = 0; i < adj_[u].size(); ++i) {
        int v = adj_[u][i];
        int w = weight_[u][i];
        Length new_dist = distance_[u] + w;
        if (!visited_[v] && distance_[v] > new_dist) {
            seen_.emplace(v);
            prev_[v] = u;
            distance_[v] = new_dist;
            q.push({distance_[v], v});
        }
    }
}

Dijkstra::Length Dijkstra::find_path(int s, int t) {
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
    return distance_[t] != LLINF ? distance_[t] : -1;
}

void Dijkstra::print_shortest_path() {
    for (int i = 0; i < path_.size(); ++i) {
        std::cout << path_[i] + 1 << (i != path_.size() - 1 ? " " : "\n");
    }
}
