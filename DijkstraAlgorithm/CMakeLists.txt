cmake_minimum_required(VERSION 3.21)
project(DijkstraAlgorithm)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Test/lib)
add_executable(DijkstraAlgorithm main.cpp StreamIO.cpp StreamIO.hpp
            Graph.cpp Graph.hpp Vertex.hpp Edge.hpp ShortestWay.hpp)
