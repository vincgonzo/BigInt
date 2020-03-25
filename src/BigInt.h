#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED
#include <iostream>

class BigInt
{
    unsigned long long ch1;
    unsigned long long ch2;

public:
    BigInt();
    BigInt(const BigInt &b);
    BigInt(unsigned long n);
    //BigInt(const char *ch);

    BigInt operator+=(BigInt const& bi2);
    bool operator<(int const& a);

    friend std::ostream& operator<<(std::ostream &flux, BigInt const& bi);
    friend std::istream& operator>>(std::istream &flux, BigInt const& bi);
};

#endif // BIGINT_H_INCLUDED
