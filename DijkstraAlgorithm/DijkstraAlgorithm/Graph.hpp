#ifndef DIJKSTRAALGORITHM_GRAPH_HPP
#define DIJKSTRAALGORITHM_GRAPH_HPP

#include "Edge.hpp"
#include "Vertex.hpp"
#include <vector>
#include "ShortestWay.hpp"


class Graph final {
public:
    Graph() = default;

    Graph(const std::vector<Edge> &_graph);

    void AddEdge(const Edge &edge);

    const std::vector<Edge>& getEdges() const;

    ShortestWay findShortestWay(const Vertex &Source, const Vertex& Destination) const;

private:
    std::vector<Edge> edges;
};


#endif
