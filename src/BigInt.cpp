#include "BigInt.h"
#include <iostream>

using namespace std;

BigInt::BigInt(): ch1(0), ch2(0){}

BigInt::BigInt(const BigInt &b):ch1(b.ch1), ch2(b.ch2)
{
}

BigInt::BigInt(unsigned long n): ch1(n), ch2(0){}

BigInt BigInt::operator+=(BigInt const& bi2)
{
    ch1 += bi2.ch1;
    ch2 += bi2.ch2;
}

bool BigInt::operator<(int const& a)
{
    return (ch1 < a)? true : false;
}

ostream& operator<<(ostream &flux, BigInt const& bi )
{
    if(bi.ch2 != 0)
        flux << bi.ch1 << bi.ch2;
    else
        flux << bi.ch1;
    return flux;
}

istream& operator>>(istream &flux, BigInt const& bi )
{
    flux >> bi.ch1;
}
/*
BigInt::BigInt(const char *ch)
{

}*/
