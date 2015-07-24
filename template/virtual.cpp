#include <iostream>

using namespace std;
class B;
class X;
class A{
    friend B;
    friend X;
    A()
    {
        cout << "construct A is call" << endl;
    }
};

struct B : A{
    B()
    {
        cout << "construct B is call" << endl;
    }
};

struct C : B{
    C() 
    {
        cout << "construct C is call" << endl;
    }
};

struct X : virtual A {
    X() 
    {
        cout << "construct X is call" << endl;
    }
};

struct Y : X {
    Y() 
    {
        cout << "construct Y is call" << endl;
    }
};

int main()
{
    C c;
    Y y;
    return 0;
}
