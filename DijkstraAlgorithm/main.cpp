#include <iostream>
#include <fstream>
#include <ostream>
#include "StreamIO.hpp"
#include "Graph.hpp"
#include <array>

int main() {
    std::ifstream ifstream("input.txt");
    Data cityGraph;
    std::vector<Vertex> cities;
    cities.emplace_back("Novosibirsk");
    cities.emplace_back("Toronto");
    cities.emplace_back("Krasnoyarsk");
    cities.emplace_back("Omsk");
    cities.emplace_back("Kiev");

    try {
        cityGraph = StreamIO::readCityGraph(ifstream);
        Graph graph(cityGraph.edges);
        for (auto& item: cities) {
            ShortestWay shortWay = graph.findShortestWay(cityGraph.Source, item);
            std::ofstream ostream("output.txt");
            StreamIO::writeShortestWay(std::cout, shortWay);
        }

    }
    catch (std::invalid_argument exception) {
        std::cout << exception.what();
    }



    return 0;
}
