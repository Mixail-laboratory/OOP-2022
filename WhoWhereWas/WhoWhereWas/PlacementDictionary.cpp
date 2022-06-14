#include "PlacementDictionary.hpp"



PlacementDictionary::PlacementDictionary(const std::set<Placement> &places) {
    PlacesDataBase = places;
}

void PlacementDictionary::addPlace(const Placement &place) {
    PlacesDataBase.insert(place);
}

const std::vector<Placement> PlacementDictionary::getPlace(const Coordinates &coordinates) const {
    const Placement currPlace = {"undefinded", coordinates, coordinates};
    auto first = PlacesDataBase.lower_bound(currPlace);
    auto second = PlacesDataBase.upper_bound(currPlace);
    if (first == PlacesDataBase.end() || second == PlacesDataBase.end()){
        return {{currPlace}};
    }
    if (!(*first < *second)){
        std::swap(first, second);
    }
    std::vector<Placement> places;
    for (auto iterator = first; *iterator < *second; iterator++){
        places.push_back(*iterator);
    }
    return places;
}


