#include "FileIO.hpp"
#include <fstream>
#include <stdexcept>

std::vector<Number> FileIO::getNumbersfromFile(const std::string &filename) {
    std::ifstream ifstream(filename);
    std::vector<Number> numbers;
    int base;
    std::vector<int> Digits;
    for (int i = 0; i < 2; i++) {
        std::string buffer;
        std::getline(ifstream, buffer);
        if (buffer.size() < 4 || buffer.find(':', 0) == std::string::npos || buffer.find('"') == std::string::npos) {
            throw std::invalid_argument("Parser err: invalid string");
        }
        base = std::stoi(buffer);

        size_t pos = buffer.find_first_of('\"', 0);
        size_t pos1 = buffer.find_first_of('\"', pos + 1);
        size_t len = (pos1 == std::string::npos) ? std::string::npos : pos1 - pos - 1;

        std::string digit(buffer.substr(pos + 1, len));


        for (auto &it: digit) {
            if (!isdigit(it)) {
                Digits.push_back(it - 'A' + 10);
            } else {
                Digits.push_back(it - '0');
            }
        }
        Number number(base, Digits);

        numbers.push_back(number);
        Digits.clear();
    }


    return numbers;
}

void FileIO::writeToFile(const std::string &filename, const Number &number) {
    std::ofstream ofstream(filename);
    ofstream << number.base << ": " << "\"";
    for (auto &item: number.digits) {
        ofstream << item;
    }
    ofstream << "\"";
}

int FileIO::getReturnBase(const std::string &filename) {
    std::ifstream ifstream(filename);
    std::string buffer;
    std::getline(ifstream, buffer);
    std::getline(ifstream, buffer);
    std::getline(ifstream, buffer);

    int retBase = std::stoi(buffer);

    return retBase;
}
