#include <iostream>
#include <ctime>
#include <iomanip>
#include <istream>
#include <map>
#include <fstream>

#include "StreamIO.hpp"
#include "PlacementDictionary.hpp"


std::time_t createTime(const std::string &str) {
    std::tm time = {};
    std::istringstream ss(str);
    ss >> std::get_time(&time, "%Y-%b-%d %H:%M:%S");
    if (ss.fail()) {
        throw std::invalid_argument("hhaaha");
    }
    return std::mktime(&time);
}

int main() {
    std::fstream fstream("places.txt");
    std::fstream fstream1("users.txt");
    try {
        auto places = StreamIO::readPlaces(fstream);
        PlacementDictionary placementDictionary(places);
        auto userLog = StreamIO::readLogFile(fstream1);
        std::vector<std::vector<Placement>> userPlaces;
        for (auto&[id, timecoords]: userLog) {
            for (auto item: timecoords){
                const auto place = placementDictionary.getPlace(item.second);
                userPlaces.push_back(place);
            }
            StreamIO::writeUserMovement(std::cout, id, userPlaces);
            userPlaces.clear();
        }
    }
    catch (std::invalid_argument exception) {
        std::cout << exception.what();
    }


    return 0;
}
