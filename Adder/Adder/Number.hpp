#ifndef ADDER_NUMBER_HPP
#define ADDER_NUMBER_HPP

#include <vector>

class Number final {
public:
    Number();

    Number(int base, const std::vector<int> &digits);

    int getBase() const;

    const std::vector<int> &getDigits() const;

    static Number plus(const Number &number_A, const Number &number_B, const int newBase);


private:
    int base;
    std::vector<int> digits;
    static const int MINBASE = 2;
    static  const int MAXBASE = 36;

    static unsigned long long toDecimal(const Number &number);

    static Number toBase(const Number &number, const int newBase);
};


#endif
