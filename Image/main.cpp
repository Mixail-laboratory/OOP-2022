#include <iostream>

#include "Image.hpp"
int main() {

    Image image = {-1, 2, 3};

    std::cout << image.channels() << std::endl;
    return 0;
}
