#include "Adder.hpp"
#include <cmath>
#include <deque>
#include <algorithm>

unsigned long long Adder::toDecimal(const Number &number) {
    size_t size = number.digits.size();
    unsigned long long sum = 0;
    unsigned long long tmp;
    for (size_t i = 0; i < size; i++) {
        long long mult = std::pow(number.base, size - i - 1);
        tmp = number.digits[i] * mult;
        sum += tmp;
    }
    return sum;
}

Number Adder::toBase(const Number &number, int newBase) {
    unsigned long long d_number = toDecimal(number);
    std::deque<int> rest;
    Number newNumber;
    unsigned long long res;
    while (d_number) {
        res = d_number % newBase;
        d_number = d_number / newBase;
        rest.push_front(res);
    }
    newNumber.digits.insert(newNumber.digits.cend(), rest.cbegin(), rest.cend());

    rest.clear();
    newNumber.base = newBase;
    return newNumber;
}

Number Adder::plus(const Number &number_A, const Number &number_B, const int &newBase) {
    Number C1 = Adder::toBase(number_A, newBase);
    Number C2 = Adder::toBase(number_B, newBase);


    std::reverse(C1.digits.begin(), C1.digits.end());
    std::reverse(C2.digits.begin(), C2.digits.end());
    int carry = 0;
    int i = 0;
    while (i < std::max(C1.digits.size(), C2.digits.size()) || carry) {
        if (i == C1.digits.size())
            C1.digits.push_back(0);
        if (i < C2.digits.size())
            C1.digits[i] += carry + C2.digits[i];
        else
            C1.digits[i] += carry;
        carry = C1.digits[i] >= newBase;
        if (carry)
            C1.digits[i] -= newBase;
        i++;
    }
    std::reverse(C1.digits.begin(), C1.digits.end());
    return C1;

}

