#ifndef WHOWHEREWAS_PLACEMENTDICTIONARY_HPP
#define WHOWHEREWAS_PLACEMENTDICTIONARY_HPP

#include <unordered_set>
#include "Placement.hpp"
#include "StreamIO.hpp"

#include <vector>
#include <algorithm>

class PlacementDictionary final {
public:
    PlacementDictionary() = default;

    PlacementDictionary(const std::set<Placement> &places);

    void addPlace(const Placement &place);

    const std::vector<Placement> getPlace(const Coordinates &coordinates) const;

private:
    std::set<Placement> PlacesDataBase = {};
};


#endif
