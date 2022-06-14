#pragma once

#include <string>
#include <cmath>
#include "Coordinates.hpp"

struct Placement final {
    Placement() = default;

    Placement(const std::string &name, const Coordinates &startRect,
              const Coordinates &endRect) : Name(name), StartRectangle(startRect), EndRectangle(endRect) {}


    bool operator<(const Placement &place) const {
        if (StartRectangle != place.StartRectangle) {
            return (StartRectangle < place.StartRectangle && EndRectangle < place.EndRectangle) ||
                   (EndRectangle < place.EndRectangle);
        } else {
            return EndRectangle < place.EndRectangle;
        }
        //return std::tie(StartRectangle, EndRectangle) < std::tie(place.StartRectangle, place.EndRectangle);
    }

    const std::string &getName() const {
        return Name;
    }

    const Coordinates &getStartRectangle() const {
        return StartRectangle;
    }

    const Coordinates &getEndRectangle() const {
        return EndRectangle;
    }

private:
    std::string Name{};
    Coordinates StartRectangle{};
    Coordinates EndRectangle{};

};
