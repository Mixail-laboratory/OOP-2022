#include "Graph.hpp"
#include <algorithm>
#include <unordered_set>
#include <optional>
#include <set>

void Graph::AddEdge(const Edge &edge) {
    edges.insert(edge);
}

Graph::Graph(const std::multiset<Edge> &_graph) : edges(_graph) {}

namespace {
    Vertex getAdjacentVertex(const Vertex &vertex, const Edge &edge) {
        if (edge.getFirst() == vertex) {
            return {edge.getSecond()};
        }
        return {edge.getFirst()};

    }

    void
    initAlgorithm(const std::multiset<Edge> &edges, std::unordered_map<Vertex, int, Vertex::HashFunction> &distances,

                  const Vertex &Destination, const Vertex &Source) {
        for (auto &edge: edges) {
            for (auto &vertex: {edge.getFirst(), edge.getSecond()}) {
                distances.insert(std::make_pair(vertex, std::numeric_limits<int>::max()));
            }
        }

        distances[Source] = 0;
    }

    std::vector<Vertex>
    buildShortestWay(std::unordered_map<Vertex, Vertex, Vertex::HashFunction> &previousVertexes,
                     const Vertex &Destination, const Vertex &Source) {
        ShortestWay shortestWay;
        std::vector<Vertex> cities;
        auto city = Destination;
        do {
            cities.push_back(city);
            city = previousVertexes[city];
        } while (!(city == Source));

        cities.push_back(Source);
        std::reverse(cities.begin(), cities.end());
        return cities;
    }

    void setDistances(std::unordered_map<Vertex, std::vector<Edge>, Vertex::HashFunction> &vertexAndEdges,
                      std::unordered_map<Vertex, Vertex, Vertex::HashFunction> &previousVertexes,
                      const Vertex &lastWatchedVertex,
                      std::unordered_map<Vertex, int, Vertex::HashFunction> &distances,
                      const std::unordered_set<Vertex, Vertex::HashFunction> &pointedVertexes) {

        Vertex adjVertex;

        for (auto &edge: vertexAndEdges[lastWatchedVertex]) {
            adjVertex = getAdjacentVertex(lastWatchedVertex, edge);
            if (pointedVertexes.find(adjVertex) != pointedVertexes.end()) {
                continue;
            }
            const int oldDistance = distances[adjVertex];
            const int newDistance = distances[lastWatchedVertex] + edge.getWeight();
            if (oldDistance > newDistance) {
                distances[adjVertex] = newDistance;
                previousVertexes.insert_or_assign(adjVertex, lastWatchedVertex);
            }

        }
    }

    bool isWayUpdated(std::unordered_map<Vertex, int, Vertex::HashFunction> &distances,
                      Vertex& lastWatchedVertex, const std::unordered_set<Vertex, Vertex::HashFunction> &pointedVertexes){
        bool isWayUpdated = false;
        int currMin = std::numeric_limits<int>::max();
        for (auto&[vertex, length]: distances) {
            if (length < currMin && pointedVertexes.find(vertex) == pointedVertexes.end()) {
                lastWatchedVertex = vertex;
                currMin = length;
                isWayUpdated = true;
            }
        }
        return isWayUpdated;
    }


}

ShortestWay Graph::findShortestWay(const Vertex &Source, const Vertex &Destination) const {
    std::unordered_set<Vertex, Vertex::HashFunction> pointedVertexes{};
    std::unordered_map<Vertex, int, Vertex::HashFunction> distances{};
    std::unordered_map<Vertex, Vertex, Vertex::HashFunction> previousVertexes{};


    std::unordered_map<Vertex, std::vector<Edge>, Vertex::HashFunction> vertexAndEdges{};
    for (auto& edge: edges) {
        vertexAndEdges[edge.getFirst()].push_back(edge);
        vertexAndEdges[edge.getSecond()].push_back(edge);
    }

    initAlgorithm(edges, distances, Destination, Source);

    if (distances.find(Destination) == distances.end() || distances.find(Source) == distances.end()) {
        return {0, {}};
    }

    if (Destination == Source) {
        return {0, {Source}};
    }

    Vertex lastWatchedVertex = Source;
    pointedVertexes.insert(Source);


    for (;;) {
        if (lastWatchedVertex == Destination) {
            break;
        }
        setDistances(vertexAndEdges, previousVertexes, lastWatchedVertex, distances, pointedVertexes);

        if (!isWayUpdated(distances, lastWatchedVertex, pointedVertexes)) {
            return {0, {}};
        }
        pointedVertexes.insert(lastWatchedVertex);

    }


    return {distances[Destination], buildShortestWay(previousVertexes, Destination, Source)};
}


const std::multiset<Edge> &Graph::getEdges() const {
    return edges;
}



