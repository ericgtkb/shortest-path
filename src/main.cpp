#include <iostream>
#include <shortestpath/shortest_path_solver.h>


int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    ShortestPathSolver solver{};
    solver.solve();

    return 0;
}
