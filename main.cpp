#include <string>
#include <iostream>
#include <limits>
#include "src/BigInt.h"

using namespace std;

int main() {
    BigInt g("51545728427386549532");
    BigInt c("154547675874997658616423456789012345678901234567890123456789012345678901234567890");
    BigInt y("154547675874997658616423456789012345678901234567890123456789012345678901234567878");


    BigInt a(4000000000);

    BigInt test3(25);



    cout << a << endl;
    cout << "%%%%%%%%%%%%%%%   Multiplication with : " << test3 << "  %%%%%%%%%%%%%%%%%%%%%%" << endl;
    a *= test3;
    cout << a << endl;    a /= test3;
    cout << a << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
////
//    cout << "======== Same with BigInt de ouf ============" << endl;
//    cout << c << endl;
//    cout << "%%%%%%%%%%%%%%%   Multiplication with : " << g << "  %%%%%%%%%%%%%%%%%%%%%%" << endl;
//    c *= g;
//    cout << c << endl;
//    c /= g;
//    cout << c << endl;

//    if(d != a)
//        cout << "Bizarre. Ce message ne devrait pas apparaitre\n";
}
