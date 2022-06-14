#include "Graph.hpp"
#include <algorithm>
#include <unordered_set>
#include <optional>


void Graph::AddEdge(const Edge &edge) {
    edges.push_back(edge);
}

Graph::Graph(const std::vector<Edge> &_graph) : edges(_graph) {}

namespace {
    std::optional<Vertex> getAdjacentVertex(const Vertex &vertex, const Edge &edge) {
        if (edge.getFirst() == vertex) {
            return {edge.getSecond()};
        }
        if (edge.getSecond() == vertex) {
            return {edge.getFirst()};
        }
        return {};
    }
    void initAlgorithm(const std::vector<Edge>& edges, std::unordered_map<Vertex, int, Vertex::HashFunction>& distances,

                       const Vertex& Destination, const Vertex& Source){
        for (auto &edge: edges) {
            for (auto &vertex: {edge.getFirst(), edge.getSecond()}) {
                distances.insert(std::make_pair(vertex, std::numeric_limits<int>::max()));
            }
        }

        if (distances.find(Destination) == distances.end()){
            throw std::invalid_argument("invalid distance vertex");
        }
        if (distances.find(Source) == distances.end()){
            throw std::invalid_argument("invalid source vertex");
        }

        distances[Source] = 0;
    }


}

ShortestWay Graph::findShortestWay(const Vertex &Source, const Vertex &Destination) const {
    std::unordered_set<Vertex, Vertex::HashFunction> pointedVertexes{};
    std::unordered_map<Vertex, int, Vertex::HashFunction> distances{};
    std::unordered_map<Vertex, Vertex, Vertex::HashFunction> previousVertexes{};


    initAlgorithm(edges, distances, Destination, Source);
    if (Destination == Source){
        return {0, {Source}};
    }

    Vertex lastWatchedVertex = Source;
    pointedVertexes.insert(Source);

    for (;;) {
        if (lastWatchedVertex == Destination) {
            break;
        }
        std::optional<Vertex> adjVertex;
        for (auto &edge: edges) {
            adjVertex = getAdjacentVertex(lastWatchedVertex, edge);
            if (!adjVertex.has_value() || pointedVertexes.find(adjVertex.value()) != pointedVertexes.end()) {
                continue;
            }
            const int oldDistance = distances[adjVertex.value()];
            const int newDistance = distances[lastWatchedVertex] + edge.getWeight();
            if (oldDistance > newDistance) {
                distances[adjVertex.value()] = newDistance;
                previousVertexes.insert_or_assign(adjVertex.value(), lastWatchedVertex);
            }

        }
        int currMin = std::numeric_limits<int>::max();
        for (auto&[vertex, length]: distances) {
            if (length < currMin && pointedVertexes.find(vertex) == pointedVertexes.end()) {
                lastWatchedVertex = vertex;
                currMin = length;
            }
        }
        pointedVertexes.insert(lastWatchedVertex);
    }
    ShortestWay shortestWay;
    std::vector<Vertex> cities;
    auto city = Destination;
    do{
        cities.push_back(city);
        city = previousVertexes[city];
    } while (!(city == Source));

    cities.push_back(Source);
    std::reverse(cities.begin(), cities.end());

    return {distances[Destination], cities};
}


const std::vector<Edge> &Graph::getEdges() const {
    return edges;
}



