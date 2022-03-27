#ifndef ADDER_ADDER_HPP
#define ADDER_ADDER_HPP
#include "FileIO.hpp"
#include "Number.hpp"

class Adder {
public:
    static unsigned long long toDecimal(const Number& number);
    static Number toBase(const Number& number, int newBase);
    static Number plus(const Number& numer_A, const Number& number_B, const int& newBase);
};


#endif //ADDER_ADDER_HPP
