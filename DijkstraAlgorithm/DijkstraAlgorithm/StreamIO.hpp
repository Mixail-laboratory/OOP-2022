#ifndef DIJKSTRAALGORITHM_STREAMIO_HPP
#define DIJKSTRAALGORITHM_STREAMIO_HPP

#include <vector>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "ShortestWay.hpp"

struct Data {
    Vertex Source;
    std::vector<Edge> edges;
};

class StreamIO final {
public:
    StreamIO() = delete;

    static Data readCityGraph(std::istream &input);

    static void
    writeShortestWay(std::ostream &os, const ShortestWay &shortest_way);
};


#endif
