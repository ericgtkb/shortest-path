//
// Created by Eric Chen on 2019-07-21.
//

#include <fstream>
#include "shortestpath/shortest_path_solver.h"
#include "dijkstra.h"
#include "a_star.h"
#include "bidirectional_dijkstra.h"
#include "bidirectional_a_star.h"


ShortestPathSolver::ShortestPathSolver(int argc, char* argv[]) : verbose{false}, print_path{false},
        algo_type{'d'}, algorithm{nullptr}, filename{} {
    if (argc > 1) {
        std::string first_arg{argv[1]};
        if (first_arg[0] == '-') {
            for (int i = 1; i < first_arg.size(); ++i) {
                char c = first_arg[i];
                switch (c) {
                    case 'a':
                        algo_type = 'a';
                        break;
                    case 'A':
                        algo_type = 'A';
                        break;
                    case 'd':
                        algo_type = 'd';
                        break;
                    case 'D':
                        algo_type = 'D';
                        break;
                    case 'h':
                        print_help();
                        return;
                    case 'p':
                        print_path = true;
                        break;
                    case 'v':
                        verbose = true;
                        break;
                    default:
                        std::cout << "Unknown option: -" << c << "!\n";
                        exit(1);
                }
            }
        } else {
            filename = first_arg;
        }
        if (argc > 2 && filename.empty()) {
            filename = argv[2];
        }
    }
    print_intro();
    if (!filename.empty()) {
        std::ifstream in{filename};
        if (in.is_open()) {
            solve(in);
            in.close();
        } else {
            std::cout << "Failed to open " << filename << "\n";
            exit(2);
        }
    } else {
        solve(std::cin);
    }
}

void ShortestPathSolver::solve(std::istream& in) {
    algorithm->read_graph_and_queries(in);
    algorithm->process_queries(print_path, verbose);
}

void ShortestPathSolver::print_intro() {
    std::string title{};
    switch (algo_type) {
        case 'a':
            title = "A*";
            algorithm = std::make_unique<AStar>();
            break;
        case 'A':
            title = "Bidirectional A*";
            algorithm = std::make_unique<BidirectionalAStar>();
            break;
        case 'D':
            title = "Bidirectional Dijkstra's";
            algorithm = std::make_unique<BidirectionalDijkstra>();
            break;
        case'd':
        default:
            title = "Dijkstra's";
            algorithm = std::make_unique<Dijkstra>();
    }
    std::cout << std::string(30, '=') << " Shortest Path Solver " << std::string(30, '=') << "\n";
    std::cout << std::string(20, ' ') << "Using " << title << " algorithm...\n";
}


void ShortestPathSolver::print_help() {
    std::cout << "Usage:\tshotrestpah [option] [file]\n";
    std::cout << "Options:\n"
                 "-a     : use A* algorithm\n"
                 "-A     : use bidirectional A* algorithm\n"
                 "-d     : use Dijkstra's algorithm (default)\n"
                 "-D     : use bidirectional Dijkstra's algorithm\n"
                 "-h     : print this help message and exit\n"
                 "-p     : print vertices in the shortest path\n"
                 "-v     : verbose\n";
    std::cout << "\nInput format (vertices should be labeled using one-based indexing):\n"
                 "\tFirst line: n (number of vertices) m (number of edges)\n"
                 "\tNext n lines (for A* and bidirectional A* only): x (x coordinate of the vertex) y (x coordinate of the vertex)\n"
                 "\tNext m lines: u (start of the edge) v (end of the edge) w (weight of the edge)\n"
                 "\tNext line: q (number of queries)\n"
                 "\tNext q lines: s (source node) t (target node)\n";
    std::cout << "\nOutput format:\n"
                 "For each query, the program prints the shortest distance and the vertices on the path in the next line (if -p)\n";
    std::cout << "\nIf no input file is specified, enter the graph manually.\n"
                 "For A* and bidirectional A* algorithms to get the correct paths, the weight of each edge should "
                 "be greater than its Euclidean distance.\n";
}

