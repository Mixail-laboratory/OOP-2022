#include <iostream>
#include "Histogram.hpp"
int main() {
    Histogram histogram;
    histogram.addWord("0");
    histogram.addWord("1");
    histogram.addWord("0");


    Histogram histogram2;
    histogram2.addWord("0");
    histogram2.addWord("1");
    histogram2.addWord("3");

    Histogram newHist = histogram - histogram2;
    for (auto iter = newHist.cbegin(); iter != newHist.cend(); iter++){
        std::cout << iter->first << " " << iter->second <<  std::endl;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
