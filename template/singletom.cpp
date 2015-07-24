#include <iostream>

template< typename T>
struct Singleton{
        friend T;
        static T& instance()
        {
            static T _instance;
            return _instance;
        }

};

class A : Singleton< A>{
    private:
        A(){}
    public:
        //A(){}
        using Singleton::instance;
};

int main()
{
    A::instance();
    return 0;
}
