#ifndef BigInt_H_INCLUDED
#define BigInt_H_INCLUDED
#include <iostream>
#include <vector>

#include <vector>
#include <iostream>
#include <map>

class BigInt
{
private:
    std::vector<int> number;
    bool positive;
    int base;
    unsigned int skip;
    static const int default_base=1000000000;

public:
    //Constructors
    BigInt();
    BigInt(long long);
    BigInt(std::string);
    BigInt(const BigInt& b);

    //Adding
    BigInt operator+(BigInt const &) const;
    BigInt &operator+=(BigInt const &);
    BigInt operator+(long long const &) const;
    BigInt &operator+=(long long);

    //Subtraction
    BigInt operator-(BigInt const &) const;
    BigInt &operator-=(BigInt const &);

    //Multiplication
    BigInt operator*(BigInt const &);
    BigInt &operator*=(BigInt const &);
    BigInt operator*(long long const &);
    BigInt &operator*=(int const &);

    //Compare
    bool operator<(const BigInt &) const;
    bool operator>(const BigInt &) const;
    bool operator<=(const BigInt &) const;
    bool operator>=(const BigInt &) const;
    bool operator==(const BigInt &) const;
    bool operator!=(const BigInt &) const;

    //Allocation
    BigInt operator=(const long long &);

    //Access
    int operator[](int const &);

    //Input&Output
    friend std::istream &operator>>(std::istream &, BigInt &);
    friend std::ostream &operator<<(std::ostream &, BigInt const &);

    //Helpers
    void clear();
    BigInt &abs();

    //Power
    BigInt &pow(int const &);

    //Trivia
    int digits() const;
    int trailing_zeros() const;
private:
    int segment_length(int) const;
    BigInt pow(int const &, std::map<int, BigInt> &);
    int compare(BigInt const &) const; //0 a == b, -1 a < b, 1 a > b
};

BigInt abs(BigInt);
std::string to_string(BigInt const &);
BigInt factorial(int);


#endif // BigInt_H_INCLUDED
