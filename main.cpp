#include <iostream>
#include "src/BigInt.h"

using namespace std;

int main() {
     BigInt a = 123;
     BigInt b;

cout << a << endl;
cout << "====================" << endl;
cout << b << endl;
     cout << "Entrez un (grand) nombre: ";
     cin >> b;

     /*while(a < 1000000)
        a += b;
     cout << a << endl;*/

    /*BigInt c = "123456789012345678901234567890123456789012345678901234567890";
    b = c * a;
    BigInt d = b / c;
    if(d != a)
        cout << "Bizarre. Ce message ne devrait pas apparaitre\n";*/
}
