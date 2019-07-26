//
// Created by Eric Chen on 2019-07-21.
//

#include <fstream>
#include "shortestpath/shortest_path_solver.h"
#include "dijkstra.h"
#include "a_star.h"
#include "bidirectional_dijkstra.h"
#include "bidirectional_a_star.h"


ShortestPathSolver::ShortestPathSolver(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Please choose an algorithm!\n";
    } else {
        std::string option {argv[1]};
        if (option[0] == '-') {
            switch (option[1]) {
                case 'a':
                    algorithm = std::make_unique<AStar>();
                    break;
                case 'D':
                    algorithm = std::make_unique<BidirectionalDijkstra>();
                    break;
                case 'A':
                    algorithm = std::make_unique<BidirectionalAStar>();
                    break;
                case 'd':
                default:
                    algorithm = std::make_unique<Dijkstra>();
            }
        }
        print_intro(option[1]);
        if (argc > 2) {
            std::string filename {argv[2]};
            std::ifstream in(filename);
            if (in.is_open()) {
                solve(in);
                in.close();
            } else {
                std::cout << "Failed to open " << filename << "\n";
                return;
            }
        } else {
            solve(std::cin);
        }
    }
}

void ShortestPathSolver::read_graph_and_queries(std::istream& in) {
    algorithm->read_graph_and_queries(in);

}

void ShortestPathSolver::process_queries(bool print_path) {
    algorithm->process_queries(print_path);
}

void ShortestPathSolver::solve(std::istream& in) {
    read_graph_and_queries(in);
    process_queries(true);
}

void ShortestPathSolver::print_intro(char c) {
    std::string title{};
    switch (c) {
        case 'a':
            title = "A*";
            break;
        case 'D':
            title = "Bidirectional Dijkstra's";
            break;
        case 'A':
            title = "Bidirectional A*";
            break;
        case'd':
        default:
            title = "Dijkstra's";
    }
    std::cout << std::string(30, '=') << " Shortest Path Solver " << std::string(30, '=') << "\n";
    std::cout << std::string(20, ' ') << "Using " << title << " algorithm...\n";

}
