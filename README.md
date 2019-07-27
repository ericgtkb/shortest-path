# Shortest path algorithms
An implementation of some shortest path algorithms, including Dijkstra's algorithm, bidirectional Dijkstra's algorithm, A* algorithm, and bidirectional A* algorithm.

The A* algorithm implemented here is a special case that uses Euclidean distance from a vertex to the target vertex as the potential function. To guarantee that this is a valid potential function, the weight of each edge should be greater than the Euclidean distance from the start vertex to the end vertex.

## Installation
Build with CMake:
```
cmake .
cmake --build .
```

## Options:
Usage:	shotrestpah \[option\] \[file\]

Options:
+ -a     : use A* algorithm
+ -A     : use bidirectional A* algorithm
+ -d     : use Dijkstra's algorithm (default)
+ -D     : use bidirectional Dijkstra's algorithm
+ -h     : print this help message and exit
+ -p     : print vertices in the shortest path
+ -v     : verbose

## Input format
All vertices should be labeled using one-based indexing.
+ First line: n (number of vertices) m (number of edges)
+ Next n lines (for A* and bidirectional A* only): x (x coordinate of the vertex) y (x coordinate of the vertex)
+ Next m lines: u (start of the edge) v (end of the edge) w (weight of the edge)
+ Next line: q (number of queries)
+ Next q lines: s (source node) t (target node)

## Output format
For each query, the program prints the shortest distance and the vertices on the path in the next line (if -p).
