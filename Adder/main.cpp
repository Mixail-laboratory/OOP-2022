#include <iostream>
#include "FileIO.hpp"
#include "Adder.hpp"

int main() {
    std::vector<Number> nums = FileIO::getNumbersfromFile("input.txt");
    int base = FileIO::getReturnBase("input.txt");

    Number sum = Adder::plus(nums[0], nums[1], base);
    std::cout << "Hello, World!" << std::endl;
    std::vector<int> answer = {1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1};
    int i = 0;
    for (auto item: sum.digits) {
        if (item != answer[i]){
            std::cout << "false";
        }
        i++;
    }
    FileIO::writeToFile("output.txt", sum);

    return 0;
}
