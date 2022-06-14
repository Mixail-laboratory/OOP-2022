#pragma once

#include <string>

struct Vertex final {
    Vertex() = default;

    Vertex(const std::string &_name) : name(_name) {};


    bool operator==(const Vertex &other) const {
        return name == other.name;
    }

    struct HashFunction {
        size_t operator()(const Vertex &vertex) const {
            size_t xHash = std::hash<std::string>()(vertex.name);
            return xHash;
        }
    };

    const std::string &getName() const {
        return name;
    };

    bool operator<(const Vertex &vertex) const {
        return name < vertex.name;
    }

private:
    std::string name;
};