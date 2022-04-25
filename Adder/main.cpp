#include <iostream>
#include <fstream>
#include "StreamIO.hpp"


int main(int argc, char *argv[]) {
    InputData data;
    Number sum;
    std::ifstream ifstream("input.txt");
    try {
        data = StreamIO::getInputData(ifstream);
        sum = Number::plus(data.numberA, data.numberB, data.returnBase);
        StreamIO::writeNumber(std::cout, sum);
    }
    catch (std::invalid_argument excpetion) {

        std::cout << excpetion.what();
        //std::cout << "Invalid data was found, operation will be executed with default numbers" << std::endl;

    }


    return 0;
}
