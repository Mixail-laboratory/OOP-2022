#pragma once

#include <ctime>
#include <vector>
#include <map>
#include "Coordinates.hpp"

struct TimeOrderedCoordinates final{
    TimeOrderedCoordinates() = default;

    TimeOrderedCoordinates(const std::map<std::time_t, Coordinates> &coord) : coordinates(coord) {}

    void addPlace(const Coordinates &coord, const std::time_t &time) {
        coordinates.insert(std::make_pair(time, coord));
    }

   const auto begin() const {
       return coordinates.cbegin();
    }

   const auto end() const{
       return coordinates.cend();
    }


private:
    std::map<std::time_t, Coordinates> coordinates{};
};