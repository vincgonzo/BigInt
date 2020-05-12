#include "BigInt.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <map>

using namespace std;

//Constructor
BigInt::BigInt():sign(1)
{}

BigInt::BigInt(const BigInt &b)
        : m_nbr(b.m_nbr),
          sign(b.sign)
{}

BigInt::BigInt(long long value)
{
    if (value < 0) {
        sign = 0;
        value *= -1;
    } else {
        sign = true;
    }

    while (value) {
        m_nbr.push_back((int) (value % default_base));
        value /= default_base;
    }
}

BigInt::BigInt(std::string str)
{
    int sailleZ = str.length();
    sign = (str[0] != '-');
    while (true) {
        if (sailleZ <= 0) break;
        if (!sign && sailleZ <= 1) break;

        int length = 0;
        int num = 0;
        int prefix = 1;
        for (int i(sailleZ - 1); i >= 0 && i >= sailleZ - 9; --i) {
            if (str[i] < '0' || str[i] > '9') break;
            num += (str[i] - '0') * prefix;
            prefix *= 10;
            ++length;
        }
        m_nbr.push_back(num);
        sailleZ -= length;
    }
}

//Adding
BigInt BigInt::operator+(BigInt const &b) const
{
    BigInt c = *this;
    if (!b.sign || !sign) {
        return c - b;
    }
    c += b;

    return c;
}

BigInt &BigInt::operator+=(BigInt const &b)
{
    if (!b.sign || !sign) {
        return *this -= b;
    }
    vector<int>::iterator
        it1 = m_nbr.begin();
    vector<int>::const_iterator
        it2 = b.m_nbr.begin();
    int sum = 0;
    while (it1 != m_nbr.end() || it2 != b.m_nbr.end()) {
        if (it1 != m_nbr.end()) {
            sum += *it1;
        } else {
            m_nbr.push_back(0);
            it1 = m_nbr.end()-1;
        }
        if (it2 != b.m_nbr.end()) {
            sum += *it2;
            ++it2;
        }
        *it1 = sum % default_base;
        ++it1;
        sum /= default_base;
    }
    if (sum) m_nbr.push_back(1);

    return *this;
}

BigInt BigInt::operator+(long long const &b) const
{
    BigInt c = *this;
    c += b;

    return c;
}

BigInt &BigInt::operator+=(long long b)
{
    vector<int>::iterator it = m_nbr.begin();
    bool initial_flag=true;
    while (b || initial_flag) {
        initial_flag=false;
        if (it != m_nbr.end()) {
            *it += b % default_base;
            b /= default_base;
            b += *it / default_base;
            *it %= default_base;
            ++it;
        } else {
            m_nbr.push_back(0);
            it = m_nbr.end() - 1;
        }
    }

    return *this;
}

//Subtraction
BigInt BigInt::operator-(BigInt const &b) const
{
    BigInt c = *this;
    c -= b;

    return c;
}

BigInt &BigInt::operator-=(BigInt const &b)
{
    vector<int>::iterator
        it1 = m_nbr.begin();
    vector<int>::const_iterator
        it2 = b.m_nbr.begin();
    int dif = 0;
    while (it1 != m_nbr.end() || it2 != b.m_nbr.end()) {
        if (it1 != m_nbr.end()) {
            dif += *it1;
            ++it1;
        }
        if (it2 != b.m_nbr.end()) {
            dif -= *it2;
            ++it2;
        }
        if (dif < 0) {
            *(it1 - 1) = dif + default_base;
            dif = -1;
        } else {
            *(it1 - 1) = dif % default_base;
            dif /= default_base;
        }
    }
    if (dif < 0) sign = false;

    if (m_nbr.size() > 1)
    {
        do
        {
            it1 = m_nbr.end() - 1;
            if (*it1 == 0) m_nbr.pop_back();
            else break;
        } while (m_nbr.size() > 1);
    }

    return *this;
}

//Multiplication
BigInt BigInt::operator*(BigInt const &b)
{
    if (b.m_nbr.size() == 1) return *this *= b.m_nbr[0];
    vector<int>::iterator it1;
    vector<int>::const_iterator it2;
    BigInt c;
    for (it1 = m_nbr.begin(); it1 != m_nbr.end(); ++it1) {
        for (it2 = b.m_nbr.begin(); it2 != b.m_nbr.end(); ++it2) {
//            c.skip = (unsigned int) (it1 - m_nbr.begin()) + (it2 - b.m_nbr.begin()); //TODO
            c += (long long) (*it1) * (*it2);
        }
    }
//    c.skip = 0;

    return c;
}

BigInt &BigInt::operator*=(BigInt const &b)
{
    *this = *this * b;

    return *this;
}

BigInt BigInt::operator*(int b)
{
    BigInt c = *this;
    c *= b;

    return c;
}

BigInt &BigInt::operator*=(int b)
{
//    vector<int>::iterator it = m_nbr.begin();
    if (b < 0)
        sign = -sign, b = -b;
    for (int i = 0, sum = 0; i < (int) m_nbr.size() || sum; ++i)
    {
        if(i == m_nbr.size())
            m_nbr.push_back(0);
//            std::cout << " sum : " <<  sum << std::endl;
//            std::cout << " iterator before : " <<  m_nbr[i] << std::endl;
        long long calcul = m_nbr[i] * (long long) b + sum;
//            std::cout << " calcul : " <<  calcul << std::endl;
        sum = (int) (calcul / default_base);
//            std::cout << " sum after calcul : " <<  sum << std::endl;
        m_nbr[i] = (int) (calcul % default_base);
//            std::cout << " iterator after mutl and trim : " <<  m_nbr[i] << std::endl;
    }
}


//Multiplication
BigInt BigInt::operator/(BigInt const &b)
{
    if (b.m_nbr.size() == 1) return *this /= b.m_nbr[0];
    vector<int>::iterator it1;
    vector<int>::const_iterator it2;
    BigInt c;
    for (it1 = m_nbr.begin(); it1 != m_nbr.end(); ++it1) {
        for (it2 = b.m_nbr.begin(); it2 != b.m_nbr.end(); ++it2) {
//            c.skip = (unsigned int) (it1 - m_nbr.begin()) + (it2 - b.m_nbr.begin()); //TODO
            c += (long long) (*it1) / (*it2);
        }
    }
//    c.skip = 0;

    return c;
}

BigInt &BigInt::operator/=(BigInt const &b)
{
    *this = *this / b;

    return *this;
}

BigInt BigInt::operator/(long long const &b)
{
    BigInt c = *this;
    c /= b;

    return c;
}

BigInt &BigInt::operator/=(int b)
{
//    vector<int>::iterator it = m_nbr.begin();
//    long long sum = 0;
//    while (it != m_nbr.end()) {
//        sum += (long long) (*it) / b;
//        *it = (int) (sum % default_base);
//        sum /= default_base;
//        ++it;
//    }
//    if (sum) m_nbr.push_back((int) sum);
    if (b < 0)
            sign = -sign, b = -b;
    for (int i = (int) m_nbr.size() - 1, rem = 0; i >= 0; --i)
    {
        long long cur = m_nbr[i] + rem * (long long) default_base;
        m_nbr[i] = (int) (cur / b);
        rem = (int) (cur % b);
    }

    return *this;
}


//Compare
int BigInt::compare(const BigInt &a) const //0 this == a || -1 this < a || 1 this > a
{
    if (sign && !a.sign) return 1;
    if (!sign && a.sign) return -1;

    int check = 1;
    if (!sign && !a.sign) check = -1;

    if (m_nbr.size() < a.m_nbr.size()) return -1 * check;
    if (m_nbr.size() > a.m_nbr.size()) return check;
    for (size_t i(m_nbr.size()); i > 0; --i) {
        if (m_nbr[i-1] < a.m_nbr[i-1]) return -1 * check;
        if (m_nbr[i-1] > a.m_nbr[i-1]) return check;
    }

    return 0; // ==
}

bool BigInt::operator<(BigInt const &b) const
{
    return compare(b) == -1;
}

bool BigInt::operator<=(const BigInt &b) const
{
    int compared = compare(b);

    return compared == 0 || compared == -1;
}

bool BigInt::operator>(const BigInt &b) const
{
    return compare(b) == 1;
}

bool BigInt::operator>=(const BigInt &b) const
{
    int compared = compare(b);

    return compared == 0 || compared == 1;
}

bool BigInt::operator==(BigInt const &b) const
{
    return compare(b) == 0;
}

bool BigInt::operator!=(BigInt const &b) const
{
    return ! (*this == b);
}

//Allocation
BigInt BigInt::operator=(const long long &a)
{
    m_nbr.clear();
    long long t = a;
    do {
        m_nbr.push_back((int) (t % default_base));
        t /= default_base;
    } while (t != 0);

    return *this;
}

//Trivia
int BigInt::digits() const
{
    int segments = m_nbr.size();

    if (segments == 0) return 0;

    int digits = 9 * (segments - 1);
    digits += segment_length(m_nbr.back());

    return digits;
}

//Helpers
void BigInt::clear()
{
    m_nbr.clear();
    sign = 1;
//    skip = 0;
}

BigInt &BigInt::abs()
{
    sign = 1;

    return *this;
}

//Input&Output
ostream &operator<<(ostream &out, BigInt const &a)
{
    if (!a.m_nbr.size()) return out << 0;
    int i = a.m_nbr.size() - 1;
    for (; i>=0 && a.m_nbr[i] == 0; --i);

    if (i == -1) return out << 0;
    if (!a.sign) out << '-';

    vector<int>::const_reverse_iterator it = a.m_nbr.rbegin() + (a.m_nbr.size() - i - 1);

    out << *it++;
    for (; it != a.m_nbr.rend(); ++it) {
        for (int i(0), len = a.segment_length(*it); i < 9 - len; ++i) out << '0';
        if (*it) out << *it;
    }

    return out;
}

istream &operator>>(istream &in, BigInt &a)
{
    std::string str;
    in >> str;

    a = str;

    return in;
}

int BigInt::segment_length(int segment) const
{
    int length = 0;
    while (segment) {
        segment /= 10;
        ++length;
    }

    return length;
}

string to_string(BigInt const &value)
{
    ostringstream stream;
    stream << value;

    return stream.str();
}
