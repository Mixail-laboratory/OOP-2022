#include <iostream>
#include <fstream>
#include "StreamIO.hpp"


int main() {

    std::ifstream ifstream("input.txt");
    InputData data = StreamIO::getInputData(ifstream);

    Number sum = Number::plus(data.numberA, data.numberB, data.returnBase);
    std::cout << "Hello, World!" << std::endl;
    std::vector<int> answer = {1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1};
    //int i = 0;
    /*
    for (auto item: sum.getDigits()) {
        if (item != answer[i]){
            std::cout << "false";
        }
        i++;
    }
     */
    StreamIO::writeNumber(std::cout, sum);


    return 0;
}
