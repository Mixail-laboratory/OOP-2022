#include "StreamIO.hpp"
#include <istream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>


namespace {


    Edge CreateEdge(const std::vector<std::string> &temp) {
        if (temp.size() != 3) {
            throw std::invalid_argument("invalid string format");
        }

        int weight;
        weight = stoi(temp[2]);

        return {temp[0], temp[1], weight};
    }

    std::vector<Edge> readGraph(std::istream &input) {
        std::string buffer;
        std::vector<Edge> graph;
        while (std::getline(input, buffer)) {
            std::vector<std::string> temp;
            std::istringstream ist(buffer);
            std::copy(std::istream_iterator<std::string>(ist), {}, std::back_inserter(temp));

            graph.push_back(CreateEdge(temp));
        }
        return graph;
    }
}

Data StreamIO::readCityGraph(std::istream &input) {
    std::string buffer;
    std::vector<std::string> temp;
    std::getline(input, buffer);
    if (buffer[0] != 'S') {
        throw std::invalid_argument("invalid Source string");
    }

    std::istringstream ist(buffer);
    std::string source;
    char sign;
    ist >> sign >> source;

    if (source.empty()) {
        throw std::invalid_argument("invalid source name");
    }
    return {source, readGraph(input)};
}

void StreamIO::writeShortestWay(std::ostream &os,
                                const ShortestWay &shortest_way) {


    os << shortest_way.getCities()[(shortest_way.getCities().size() - 1)].getName();
    os << " - " << '{';
    std::copy(shortest_way.getCities().begin(), shortest_way.getCities().end() - 1, std::ostream_iterator<Vertex>(os, ", "));
    os << shortest_way.getCities()[shortest_way.getCities().size() - 1].getName();
    os << '}' << " - " << shortest_way.getLength() << std::endl;

}

std::ostream &operator<<(std::ostream &ostream, const Vertex &vertex) {
    ostream << vertex.getName();
    return ostream;
}
