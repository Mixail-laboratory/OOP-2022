cmake_minimum_required(VERSION 3.21)
project(WhoWhereWas)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Test/lib)

add_executable(WhoWhereWas main.cpp StreamIO.hpp StreamIO.cpp Placement.hpp
        PlacementDictionary.cpp PlacementDictionary.hpp
        Coordinates.hpp TimeOrderedCoordinates.hpp UserCoordinates.hpp)
