#include "Number.hpp"

Number::Number() {
    base = 0;
    digits = {};
}

Number::Number(int _base, const std::vector<int> &digits_) {
        base = _base;
        digits.insert(digits.cend(), digits_.cbegin(), digits_.cend());

}

