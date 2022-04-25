#include "StreamIO.hpp"
#include <fstream>
#include <stdexcept>
#include <algorithm>

namespace {
    int getBase(const std::string &BaseString) {
        auto it = std::find_if(BaseString.begin(), BaseString.end(), [](char const &c) {
            return !std::isdigit(c);
        });

        if (it != BaseString.end() || BaseString.empty()){
            throw std::invalid_argument("Parser err: invalid string with return base");
        }
        int retBase = std::stoi(BaseString);
        return retBase;
    }

    Number getNumber(const std::string &buffer) {
        const char delimiter = ':';
        if (buffer.size() < 5 || buffer.find(delimiter) == std::string::npos || buffer.find('"') == std::string::npos) {
            throw std::invalid_argument("Parser err: invalid string");
        }
        size_t delimiterPos = buffer.find_first_of(delimiter);
        std::string baseString(buffer.substr(0, delimiterPos));
        int base = getBase(baseString);

        if (buffer[delimiterPos + 1] != ' ' || buffer[delimiterPos + 2] != '\"'){
            throw std::invalid_argument("Parser err: invalid string");
        }
        size_t pos = buffer.find_first_of('\"');
        std::vector<int> Digits = {};
        size_t pos1 = buffer.find_first_of('\"', pos + 1);
        size_t len = (pos1 == std::string::npos) ? std::string::npos : pos1 - pos - 1;
        if (!len) {
            throw std::invalid_argument("Parser err: empty number entry");
        }
        std::string digit(buffer.substr(pos + 1, len));
        for (auto &it: digit) {
            int dig;
            if (!isdigit(it)) {
                if (!isupper(it)) {
                    throw std::invalid_argument("Parser err: incorrect number entry");
                }
                dig = it - 'A' + 10;
                if (dig >= base) {
                    throw std::invalid_argument("Parser err: incorrect number entry");
                }
            }
            if (!isalpha(it)) {
                dig = it - '0';
                if (dig >= base) {
                    throw std::invalid_argument("Parser err: incorrect number entry");
                }
            }
            Digits.push_back(dig);
        }

        size_t size = buffer.size();
        if (pos1 + 1 < size){
            throw std::invalid_argument("Parser err: invalid string");
        }

        return {base, Digits};
    }
}


std::ostream &StreamIO::writeNumber(std::ostream &ostream, const Number &number) {
    ostream << number.getBase() << ": " << "\"";
    if (number.getBase() > 10) {
        for (auto &item: number.getDigits()) {
            if (item > 10) {
                ostream << static_cast<char>('A' + item - 10);
            } else {
                ostream << item;
            }

        }
        ostream << "\"";
        return ostream;
    }
    for (auto &item: number.getDigits()) {
        ostream << item;
    }
    ostream << "\"";
    return ostream;
}


InputData StreamIO::getInputData(std::istream &istream) {

    std::string buffer;
    int countOfStrings = 0;
    Number numberA, numberB;
    int returnBase;
    while (std::getline(istream, buffer)) {
        if (buffer.empty()) {
            continue;
        }
        switch (countOfStrings) {
            case 0: {
                try {
                    numberA = getNumber(buffer);
                }
                catch (std::invalid_argument) {
                    continue;
                }
                break;
            }
            case 1: {
                try {
                    numberB = getNumber(buffer);
                }
                catch (std::invalid_argument){
                    continue;
                }
                break;
            }
            case 2: {
                try {
                    returnBase = getBase(buffer);
                }
                catch (std::invalid_argument){
                    continue;
                }
                break;
            }
        }

        countOfStrings++;
        if (countOfStrings == 3){
            break;
        }
    }

    if (countOfStrings < 3) {
        throw std::invalid_argument("Parser err: not enough information");
    }

    return {numberA, numberB, returnBase};
}
