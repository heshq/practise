#include <iostream>
#include <memory>
class A
{
    private:
        int id;
        static int ID;
    public:
        A():id( ID++)
        {
            std::cout<<"id:"<<id<<" construct is called"<<std::endl;
        }
        ~A()
        {
            std::cout<<"id:"<<id<<" destruct is called"<<std::endl;
        }
};

int A::ID = 0;

int main()
{
    //std::shared_ptr< A> ptr( new A[5]);//error ,will only destruct the first element
    //std::unique_ptr< A> ptr( new A[5]);//error,will only destruct the first element
    std::unique_ptr< A[]> ptr( new A[5]);//error ,will only destruct the first element
    return 0;
}
