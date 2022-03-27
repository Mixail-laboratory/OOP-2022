#ifndef ADDER_FILEIO_HPP
#define ADDER_FILEIO_HPP
#include "Number.hpp"
#include <string>

class FileIO {
public:
    static std::vector<Number> getNumbersfromFile(const std::string& filename);
    static int getReturnBase(const std::string& filename);
    static void writeToFile(const std::string& filename, const Number& number);
};


#endif
