#ifndef ADDER_NUMBER_HPP
#define ADDER_NUMBER_HPP
#include <vector>

class Number {
public:
    Number();
    ~Number() = default;
    Number(int base, const std::vector<int>& digits);
    int base;
    std::vector<int> digits;
};


#endif //ADDER_NUMBER_HPP
