#ifndef ADDER_STREAMIO_HPP
#define ADDER_STREAMIO_HPP

#include "Number.hpp"
#include <string>


struct InputData {
    Number numberA;
    Number numberB;
    int returnBase;
};

class StreamIO final {
public:
    StreamIO() = delete;

    static InputData getInputData(std::istream &istream);

    static std::ostream &writeNumber(std::ostream &ostream, const Number &number);
};


#endif
