#pragma once

#include "Vertex.hpp"
#include <vector>

struct ShortestWay final{
    ShortestWay() = default;

    ShortestWay(const int len, const std::vector<Vertex> &vertexes) : length(len), cities(vertexes) {}

    const int getLength() const{
        return length;
    }

    const std::vector<Vertex>& getCities() const{
        return cities;
    };

private:
    int length{};
    std::vector<Vertex> cities{};
};
