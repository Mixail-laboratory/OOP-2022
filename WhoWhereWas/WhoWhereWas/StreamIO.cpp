#include "StreamIO.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "Placement.hpp"

namespace {
    std::time_t createTime(const std::string &str) {
        std::tm time = {};
        std::istringstream ss(str);
        ss >> std::get_time(&time, "%Y-%b-%d %H:%M:%S");
        if (ss.fail()) {
            throw std::invalid_argument("Parser err: invalid time");
        }
        return std::mktime(&time);
    }
}


std::set<Placement> StreamIO::readPlaces(std::istream &input) {
    std::set<Placement> places;

    std::string buffer;
    std::string name{};
    int longA{}, longB{}, latA{}, latB{};
    while (getline(input, buffer)) {
        std::vector<std::string> cur_str;
        std::istringstream ist(buffer);
        if (buffer.empty()) {
            continue;
        }
        ist >> name >> latA >> longA >> latB >> longB;
        if (name.empty() || latA < 0 || latB < 0 || longA < 0 || longB < 0) {
            throw std::invalid_argument("Parser err: invalid places string");
        }
        const Coordinates coordinatesA = {latA, longA};
        const Coordinates coordinatesB = {latB, longB};
        const Placement place = {name, coordinatesA, coordinatesB};
        places.insert(place);
    }

    return places;
}

std::unordered_map<unsigned int, TimeOrderedCoordinates> StreamIO::readLogFile(std::istream &input) {
    std::string buffer;
    std::unordered_map<unsigned int, TimeOrderedCoordinates> currUsers;
    int latitude{}, longitude{};
    unsigned int id;
    std::string yymmdd, hhmmss;
    while (getline(input, buffer)) {
        std::istringstream ist(buffer);
        if (buffer.empty()) {
            continue;
        }
        ist >> yymmdd >> hhmmss >> id >> latitude >> longitude;
        if (latitude < 0 || longitude < 0) {
            throw std::invalid_argument("Parser err: invalid user string");
        }
        std::string timeStr = yymmdd + " " + hhmmss;
        TimeOrderedCoordinates timeCoordinates = {{{createTime(timeStr), {latitude, longitude}}}};
        auto isInsertHappend = currUsers.insert(std::make_pair(id, timeCoordinates));

        if (!isInsertHappend.second) {
            currUsers[id].addPlace({latitude, longitude}, createTime(timeStr));
        }
    }
    return currUsers;

}

void StreamIO::writeUserMovement(std::ostream &ostream, const unsigned int id,
                                 const std::vector<std::vector<Placement>> &places) {
    ostream << "User id: " << id << std::endl;
    int count = 0;
    for (const auto &vectorPlaces: places) {
        ostream << "{";
        for (auto &place: vectorPlaces) {
            ostream << place.getName();
            if (place.getName() == (vectorPlaces[vectorPlaces.size() - 1].getName())) {
                break;
            }
            ostream << " - ";
        }
        if (count == places.size() - 1) {
            ostream << "}";
        } else {
            ostream << "}" << " - ";
        }
        count++;
    }
    ostream << std::endl;
}

std::ostream &operator<<(std::ostream &ostream, const Placement &vertex) {
    ostream << vertex.getName();
    return ostream;
}
