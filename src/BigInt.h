#ifndef BigInt_H_INCLUDED
#define BigInt_H_INCLUDED
#include <iostream>
#include <vector>

#include <vector>
#include <iostream>
#include <limits>
#include <map>

class BigInt
{
private:
    std::vector<int> m_nbr;
    int sign;
//    static const int default_base=std::numeric_limits<int>::max();
    static const int default_base=1000000000;

public:
    //Constructors
    BigInt();
    BigInt(long long);
    BigInt(std::string str);
    BigInt(const BigInt& b);

    void decale(int nb);

    //Adding
    BigInt operator+(BigInt const &) const;
    BigInt &operator+=(BigInt const &);
    BigInt operator+(int const &) const;
    BigInt &operator+=(int);
    BigInt operator+(long long const &) const;
    BigInt &operator+=(long long);

    //Subtraction
    BigInt operator-(BigInt const &) const;
    BigInt &operator-=(BigInt const &);

    //Multiplication
    BigInt operator*(BigInt const &);
    BigInt &operator*=(BigInt const &);
    BigInt operator*(int );
    BigInt &operator*=(int );
    //Division
    BigInt operator/(BigInt const &);
    BigInt &operator/=(BigInt const &);
    BigInt operator/(int const &);
    BigInt &operator/=(int );

    //Modulo
    BigInt operator%(const int );
    BigInt operator%(BigInt const &);

    //Compare
    bool operator<(const BigInt &) const;
    bool operator>(const BigInt &) const;
    bool operator<=(const BigInt &) const;
    bool operator>=(const BigInt &) const;
    bool operator==(const BigInt &) const;
    bool operator!=(const BigInt &) const;

    //Allocation
    BigInt operator=(const long long &);


    //Input&Output
    friend std::istream &operator>>(std::istream &, BigInt &);
    friend std::ostream &operator<<(std::ostream &, BigInt const &);

    //Helpers
    void clear();
    BigInt &abs();

    //Trivia
    int digits() const;
    int trailing_zeros() const;
private:
    int segment_length(int) const;
    int compare(BigInt const &) const; //0 a == b, -1 a < b, 1 a > b
};

std::string to_string(BigInt const &);

#endif // BigInt_H_INCLUDED
