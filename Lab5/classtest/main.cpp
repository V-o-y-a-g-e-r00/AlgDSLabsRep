#include <iostream>

class base
{
public:
    int x=5;
};
class derived: public base
{
public:
    int& refx;
    derived(): refx(base::x)
    {
        std::cout<<"refx="<< refx <<std::endl;
        refx=11;
        std::cout<<"refx="<< refx <<std::endl;
        std::cout<<"base::x="<< base::x <<std::endl;
    }

};

int main(int, char**) {
    std::cout << "Hello, world!\n";
    derived derived1;

}
