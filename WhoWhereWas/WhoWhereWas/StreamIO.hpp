#ifndef WHOWHEREWAS_STREAMIO_HPP
#define WHOWHEREWAS_STREAMIO_HPP

#include <string>
#include <istream>
#include "TimeOrderedCoordinates.hpp"
#include "Placement.hpp"
#include <unordered_map>
#include <set>

class StreamIO final {
public:
    StreamIO() = delete;

    static std::set<Placement> readPlaces(std::istream &input);

    static std::unordered_map<unsigned int, TimeOrderedCoordinates> readLogFile(std::istream &input);

    static void writeUserMovement(std::ostream &ostream, const unsigned int id, const std::vector<std::vector<Placement>> &places);
};


#endif
