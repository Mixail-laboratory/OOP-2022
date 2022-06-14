#include "Histogram.hpp"
#include <sstream>

Histogram::Histogram(std::istream &istream) {
    std::string buffer;
    while (istream >> buffer) {
        histrogram[buffer]++;
    }
}


const int Histogram::getFrequency(const std::string &word) const {
    const auto found = histrogram.find(word);
    if (found == histrogram.end()) {
        return 0;
    }
    return found->second;
}

void Histogram::addWord(const std::string &word) {
    histrogram[word]++;
}

Histogram::Histogram(const std::vector<std::string> &vector) {
    for (auto &word: vector) {
        histrogram[word]++;
    }
}

bool Histogram::operator==(const Histogram &other) const {
    return histrogram == other.histrogram;
}

Histogram Histogram::operator+(const Histogram &other) const {
    Histogram hist(*this);
    for (auto&[key, value]: other.histrogram) {
        hist.histrogram[key] += value;
    }
    return hist;
}

Histogram Histogram::operator-(const Histogram &other) const {
    Histogram hist(*this);
    for (auto&[key, value]: other.histrogram) {
        hist.histrogram[key] -= value;
        if (hist.histrogram[key] <= 0) {
            hist.histrogram.erase(key);
        }
    }
    return hist;
}
