#include "Number.hpp"
#include <cmath>
#include <algorithm>


Number::Number() : base(10), digits{0} {}

Number::Number(int base_, const std::vector<int> &digits_) : base(base_), digits(digits_) {

    if (base < MINBASE || base > MAXBASE){
        throw std::invalid_argument("Constructor err: you can't create number with invalid base");
    }

    if (digits.empty()){
        throw std::invalid_argument("Constructor err: empty digits array detected");
    }

    for (auto& item: digits){
        if (item >= base){
            throw std::invalid_argument("Constructor err: your number is greater than base");
        }

        if (item < 0){
            throw std::invalid_argument("Constructor err: numbers in digits is negative");
        }
    }
}

int Number::getBase() const{
    return base;
}

const std::vector<int> &Number::getDigits() const {
    return digits;
}

unsigned long long Number::toDecimal(const Number &number) {
    size_t size = number.digits.size();
    unsigned long long sum = 0;
    for (size_t i = 0; i < size; i++) {
        unsigned long long mult = std::pow(number.base, size - i - 1);
        unsigned long long tmp = number.digits[i] * mult;
        sum += tmp;
    }
    return sum;
}

Number Number::toBase(const Number &number, const int newBase) {
    if (number.getBase() == newBase) {
        Number newNumber = number;
        std::reverse(newNumber.digits.begin(), newNumber.digits.end());
        return newNumber;
    }
    unsigned long long d_number = toDecimal(number);
    std::vector<int> rest;
    Number newNumber;
    newNumber.base = newBase;
    newNumber.digits.clear();
    unsigned long long res;
    while (d_number) {
        res = d_number % newBase;
        d_number = d_number / newBase;
        rest.push_back(res);
    }
    newNumber.digits.insert(newNumber.digits.cend(), rest.cbegin(), rest.cend());

    rest.clear();
    return newNumber;
}

Number Number::plus(const Number &number_A, const Number &number_B, const int newBase) {

    if (newBase > MAXBASE || newBase < MINBASE) {
        throw std::invalid_argument("Operation plus err: invalid new base detected");
    }
    Number C1 = Number::toBase(number_A, newBase);
    Number C2 = Number::toBase(number_B, newBase);
    int carry = 0;

    for (size_t i = 0; i < std::max(C1.digits.size(), C2.digits.size()) || carry; i++) {
        if (i == C1.digits.size()) {
            C1.digits.push_back(0);
        }
        C1.digits[i] += carry + (i < C2.getDigits().size() ? C2.getDigits()[i] : 0);
        carry = C1.digits[i] >= newBase;
        if (carry) {
            C1.digits[i] -= newBase;
        }
    }
    std::reverse(C1.digits.begin(), C1.digits.end());
    return C1;
}




