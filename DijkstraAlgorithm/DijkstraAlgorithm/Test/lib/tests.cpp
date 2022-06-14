#include "gtest/gtest.h"
#include "../../StreamIO.hpp"
#include "../../Graph.hpp"

TEST(DijkstraAlgorithmTest, LazyTest) {
    std::stringstream str;
    str.str("S Moscow\nMoscow Novosibirsk 7\nMoscow Toronto 9\nMoscow Krasnoyarsk 14\nNovosibirsk Toronto 10\nNovosibirsk Omsk 15\nOmsk Toronto  11\nToronto Krasnoyarsk 2\nKrasnoyarsk Kiev 9\nKiev Omsk  6");
    Data cityGraph;
    Vertex dest("Toronto");
    std::vector<Vertex> cities;
    cities.emplace_back("Novosibirsk");
    cities.emplace_back("Toronto");
    cities.emplace_back("Krasnoyarsk");
    cities.emplace_back("Omsk");
    cities.emplace_back("Kiev");

    std::stringstream ostr;
    cityGraph = StreamIO::readCityGraph(str);
    Graph graph(cityGraph.edges);
    for (auto &item: cities) {
        ShortestWay shortWay = graph.findShortestWay(cityGraph.Source, item);
        StreamIO::writeShortestWay(ostr, shortWay);
    }
    EXPECT_EQ(ostr.str(),
              "Novosibirsk - {Moscow, Novosibirsk} - 7\nToronto - {Moscow, Toronto} - 9\nKrasnoyarsk - {Moscow, Toronto, Krasnoyarsk} - 11\nOmsk - {Moscow, Toronto, Omsk} - 20\nKiev - {Moscow, Toronto, Krasnoyarsk, Kiev} - 20\n");

}

TEST(DijkstraAlgorithmException, InvalidSource) {
    std::stringstream str;
    str.str("S Hahaha\nMoscow Novosibirsk 7\nMoscow Toronto 9\nMoscow Krasnoyarsk 14\nNovosibirsk Toronto 10\nNovosibirsk Omsk 15\nOmsk Toronto  11\nToronto Krasnoyarsk 2\nKrasnoyarsk Kiev 9\nKiev Omsk  6");
    Data cityGraph;
    cityGraph = StreamIO::readCityGraph(str);
    Graph graph(cityGraph.edges);
    Vertex item("Novosibirsk");


}

TEST(DijkstraAlgorithmException, InvalidDestinition) {
    std::stringstream str;
    str.str("S Toronto\nMoscow Novosibirsk 7\nMoscow Toronto 9\nMoscow Krasnoyarsk 14\nNovosibirsk Toronto 10\nNovosibirsk Omsk 15\nOmsk Toronto  11\nToronto Krasnoyarsk 2\nKrasnoyarsk Kiev 9\nKiev Omsk  6");
    Data cityGraph;
    cityGraph = StreamIO::readCityGraph(str);
    Graph graph(cityGraph.edges);
    Vertex item("Novosibirs");

}

TEST(DijkstraAlgorithmException, TrashInput) {
    std::stringstream str;
    str.str("a Toronto\nMoscow Novosibirsk 7\nMoscow Toronto 9\nMoscow Krasnoyarsk 14\nNovosibirsk Toronto 10\nNovosibirsk Omsk 15\nOmsk Toronto  11\nToronto Krasnoyarsk 2\nKrasnoyarsk Kiev 9\nKiev Omsk  6");
    Data cityGraph;
    EXPECT_ANY_THROW(StreamIO::readCityGraph(str));

}

TEST(DijkstraAlgorithmException, TrashInput_2) {
    std::stringstream str;
    str.str("S Toronto\nMoscow fasfasfa Novosibirsk 7\nMoscow Toronto 9\nMoscow Krasnoyarsk 14\nNovosibirsk Toronto 10\nNovosibirsk Omsk 15\nOmsk Toronto  11\nToronto Krasnoyarsk 2\nKrasnoyarsk Kiev 9\nKiev Omsk  6");
    Data cityGraph;
    EXPECT_ANY_THROW(StreamIO::readCityGraph(str));

}

TEST(DijkstraAlgorithmException, TrashInput_3) {
    std::stringstream str;
    str.str("S Toronto\nMoscow fasfasfa Novosibirsk -600\nMoscow Toronto &\nMoscow Krasnoyarsk 14\nNovosibirsk Toronto 10\nNovosibirsk Omsk 15\nOmsk Toronto  11\nToronto Krasnoyarsk 2\nKrasnoyarsk Kiev 9\nKiev Omsk  6");
    Data cityGraph;
    EXPECT_ANY_THROW(StreamIO::readCityGraph(str));

}

TEST(DijkstraAlgorithmTest, SimpleGraph) {
    std::multiset<Edge> edges;
    Vertex a("a");
    Vertex b("b");
    Vertex c("c");
    Vertex d("d");
    Vertex e("e");
    edges.emplace(a, b, 1);
    edges.emplace(a, d, 3);
    edges.emplace(b, d, 1);
    edges.emplace(b, c, 3);
    edges.emplace(b, e, 2);
    edges.emplace(d, c, 3);
    edges.emplace(d, e, 1);
    edges.emplace(a, b, 1);
    edges.emplace(e, c, 2);
    Graph graph(edges);
    ShortestWay shortestWay = graph.findShortestWay(a, e);
    EXPECT_EQ(shortestWay.getLength(), 3);
    shortestWay = graph.findShortestWay(a, b);
    EXPECT_EQ(shortestWay.getLength(), 1);
}

TEST(DijkstraAlgorithmException, EqualityOfDestAndSource){
    std::stringstream str;
    str.str("S Moscow\nMoscow Novosibirsk 7\nMoscow Toronto 9\nMoscow Krasnoyarsk 14\nNovosibirsk Toronto 10\nNovosibirsk Omsk 15\nOmsk Toronto  11\nToronto Krasnoyarsk 2\nKrasnoyarsk Kiev 9\nKiev Omsk  6");
    Data cityGraph;
    cityGraph = StreamIO::readCityGraph(str);
    Graph graph(cityGraph.edges);
    Vertex item("Moscow");
    EXPECT_NO_THROW(graph.findShortestWay(item, item));
}