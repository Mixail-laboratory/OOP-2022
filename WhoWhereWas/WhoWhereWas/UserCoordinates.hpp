#pragma once

#include "TimeOrderedCoordinates.hpp"

struct UserCoordinates final {
public:
    UserCoordinates() = default;

    UserCoordinates(const unsigned int _id, const TimeOrderedCoordinates &_timeCoordinates) : id(_id), timeOrederedCoordinates(
            _timeCoordinates) {};

    const unsigned int getId() const {
        return id;
    }

    const TimeOrderedCoordinates &getTimeOrderedCoordinates() const {
        return timeOrederedCoordinates;
    }

private:
    unsigned int id{};
    TimeOrderedCoordinates timeOrederedCoordinates{};
};