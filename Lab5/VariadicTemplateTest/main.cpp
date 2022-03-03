#include <iostream>


void foo(int& x)
{
    x=2;
}
template<typename... Args>
void  BetterCallSaul(void(*CallBack)(Args&...), Args& ...args)
{
    CallBack(args...);
    //int temp=args ...;
    //std::cout<< temp <<std::endl;
}

int main(int, char**) {
    std::cout << "Hello, world!\n";
    int mainx=1;
    std::cout<< "mainx="<<mainx<<std::endl;
    BetterCallSaul(foo, mainx);
    std::cout<< "mainx="<<mainx<<std::endl;
}

 /*   template<typename... CallBackParamsTail>
    statisticsGraph(void(*CallBack)(CallBackParamsTail...), CallBackParamsTail ...callbackparamstail)
    {

    }*/