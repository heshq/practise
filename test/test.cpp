#include <iostream>

struct A{
    int a = 1;
};

int test();

int main()
{
    using namespace std;
    //A a;
    //cout << a.a << endl;
    int rst = test();
    cout << rst << endl;
    return 0;
}
