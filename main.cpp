#include <string>
#include <iostream>
#include "src/BigInt.h"

using namespace std;

int main() {
    BigInt a(123);
    BigInt b;
    BigInt g;

    cout << a << endl;
    cout << "====================" << endl;
    cout << "Entrez un (grand) nombre: ";
    cin >> g;

    cout << "number G : " << g << endl;

    BigInt c("154547675874997658616423456789012345678901234567890123456789012345678901234567890");

    cout << "number C : " << c << endl;

    b = c * g;
    cout << "number B : " << b << endl;
    BigInt d = b / a;
    cout << "number D : " << d << endl;
    if(d != a)
        cout << "Bizarre. Ce message ne devrait pas apparaitre\n";
}
