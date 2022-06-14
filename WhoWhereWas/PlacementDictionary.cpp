#include "PlacementDictionary.hpp"

namespace {
    const Placement undefinded = {"undefinded", {}, {}};
}

PlacementDictionary::PlacementDictionary(const std::set<Placement> &places) {
    PlacesDataBase = places;
}

void PlacementDictionary::addPlace(const Placement &place) {
    PlacesDataBase.insert(place);
}

const std::vector<Placement> PlacementDictionary::getPlace(const Coordinates &coordinates) const {
    std::vector<Placement> places;
    for (auto &place: PlacesDataBase) {
        if (place.contains(coordinates)) {
            places.push_back(place);
        }
    }

    if (places.empty()) {
        return {undefinded};
    }

    return places;
}


