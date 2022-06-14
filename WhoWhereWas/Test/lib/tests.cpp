#include "gtest/gtest.h"
#include "../../StreamIO.hpp"
#include "../../PlacementDictionary.hpp"


TEST(StreamIO, InvalidPlaces) {
    std::stringstream sstream;
    sstream.str("Shop 0 10 5 15\n"
                "Bar 6 14 10 20\n"
                "Gallery      -25 86 -45 95\n"
                "Home    34 106  255 258");
    EXPECT_ANY_THROW(StreamIO::readPlaces(sstream));
}

TEST(StreamIO, InvalidUsers) {
    std::stringstream sstrem;
    sstrem.str("2022-May-15 06:08:00 01 -105 256\n"
               "2022-May-15 04:00:00 02 9 -17\n"
               "2022-May-15 12:00:00 03 35 90\n"
               "2022-May-15 02:00:00 02 01 11");
    EXPECT_ANY_THROW(StreamIO::readLogFile(sstrem));
}

TEST(StreamIO, InvaidTime) {
    std::stringstream stringstream;
    stringstream.str("2022-MOy-15 06:08:00 01 105 256\n"
                     "2022-May-15 04:00:00 02 9 17\n"
                     "2022-May-15 12:00:00 03 35 90\n"
                     "2022-May-15 02:00:00 02 01 11");
    EXPECT_ANY_THROW(StreamIO::readLogFile(stringstream));
}

TEST(Coordinates, InvalidCoors) {

    EXPECT_ANY_THROW(Coordinates coordinates(-1, 2));
}

TEST(PlacementDictionary, findPlaces) {
    std::stringstream sstream;
    sstream.str("Shop 0 10 5 15\n"
                "Bar 6 14 10 20\n"
                "Gallery      25 86 45 95\n"
                "Home    48 106 52  110\n"
                "Metro 100 200 150 250");
    auto places = StreamIO::readPlaces(sstream);
    PlacementDictionary placementDictionary(places);
    auto foundPlace = placementDictionary.getPlace({3, 11});
    EXPECT_EQ(foundPlace[0].getName(), "Shop");
    foundPlace = placementDictionary.getPlace({9, 17});
    EXPECT_EQ(foundPlace[0].getName(), "Bar");
//    EXPECT_EQ(placementDictionary.getPlace({30, 90}).getName(), "Gallery");
//    EXPECT_EQ(placementDictionary.getPlace({50, 107}).getName(), "Home");
//    EXPECT_EQ(placementDictionary.getPlace({101, 201}).getName(), "Metro");
//    EXPECT_NO_THROW(placementDictionary.getPlace({0, 0}));
}
/*
TEST(UserMoving, testUserMove) {
    std::stringstream sstream;
    sstream.str("Shop 0 10 5 15\n"
                "Bar 6 14 10 20\n"
                "Gallery      25 86 45 95\n"
                "Home    48 106 52  110\n"
                "Metro 100 200 150 250");
    std::stringstream usstream;
    usstream.str("2022-May-15 06:08:00 01 105 206\n"
                 "2022-May-15 04:00:00 02 9 17\n"
                 "2022-May-15 12:00:00 03 50 108\n"
                 "2022-May-15 02:00:00 02 01 11\n"
                 "2022-May-15 08:00:54 01 30 90");
    auto places = StreamIO::readPlaces(sstream);
    auto userLog = StreamIO::readLogFile(usstream);
    PlacementDictionary placementDictionary(places);

    std::stringstream ostream;
    std::vector<Placement> userPlaces;

    for (auto&[id, timecoords]: userLog) {
        for (auto item: timecoords){
            const auto place = placementDictionary.getPlace(item.second);
            userPlaces.push_back(place);
        }
        StreamIO::writeUserMovement(ostream, id, userPlaces);
        userPlaces.clear();
    }

    std::stringstream ostream1;
    ostream1.str("User id: 3\n"
                 "Home\n"
                 "User id: 2\n"
                 "Shop - Bar\n"
                 "User id: 1\n"
                 "Metro - Gallery\n");
    EXPECT_EQ(ostream.str(), ostream1.str());
}
*/