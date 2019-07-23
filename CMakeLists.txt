cmake_minimum_required(VERSION 3.14)
project(shortestpath)

set(CMAKE_CXX_STANDARD 17)

set(shortestpath_include_dirs ${PROJECT_SOURCE_DIR}/include)

file(GLOB shortestpath_source_files "${PROJECT_SOURCE_DIR}/src/*.cpp")

include_directories(${shortestpath_include_dirs})


add_executable(shortestpath ${shortestpath_source_files} src/bidirectional_dijkstra.cpp src/bidirectional_dijkstra.h)