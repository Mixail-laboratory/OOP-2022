#pragma once

#include <utility>
#include <tuple>

struct Coordinates final {
    Coordinates() = default;

    Coordinates(const int lat, const int longit) {
        if (lat < 0 || longit < 0) {
            throw std::invalid_argument("invalid coordinates");
        }
        coordinates = {lat, longit};
    }

    const int getLatitude() const {
        return coordinates.first;
    }


    const int getLongitude() const {
        return coordinates.second;
    }

    bool operator<(const Coordinates &coordinates_) const {
        bool less = std::tie(coordinates.first, coordinates.second) <=
                    std::tie(coordinates_.coordinates.first, coordinates_.coordinates.second);
        return less;
    }


    bool operator!=(const Coordinates &coords) const {
        return std::tie(coordinates.first, coordinates.second) !=
               std::tie(coords.coordinates.first, coords.coordinates.second);
    }


private:
    std::pair<int, int> coordinates;
};
