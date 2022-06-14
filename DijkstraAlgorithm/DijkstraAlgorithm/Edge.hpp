#pragma once

#include "Vertex.hpp"
#include <stdexcept>

struct Edge final {
    Edge(const Vertex &firstCity, const Vertex &secondCity, const int _weight) {
        if (firstCity.getName().empty() || secondCity.getName().empty() || _weight <= 0) {
            throw std::invalid_argument("invalid data for edge");
        }
        if (firstCity == secondCity){
            throw std::invalid_argument("invalid data for edge");
        }
        first = firstCity;
        second = secondCity;
        weight = _weight;
    };

    int getWeight() const {
        return weight;
    }

    const Vertex &getFirst() const {
        return first;
    }


    const Vertex &getSecond() const {
        return second;
    }

private:
    Vertex first{};
    Vertex second{};
    int weight{};
};