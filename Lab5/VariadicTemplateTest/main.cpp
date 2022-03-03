#include <iostream>


int foo(int x)
{
    return x;
}
template<typename... Args>
void  BetterCallSaul(Args ...args)
{
    int temp=foo(args...);
    //int temp=args ...;

    std::cout<< temp <<std::endl;
}

int main(int, char**) {
    std::cout << "Hello, world!\n";
    BetterCallSaul(2);

}
