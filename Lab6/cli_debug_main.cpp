#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"
#include "MazeSearchAlg.h"

int main(int, char**) {
    std::cin.sync_with_stdio(false);
    char buffer[3]={'\0'};

    int i;
    std::cin>>i;
    std::cout<<"in_avail()="<<std::cin.rdbuf()->in_avail()<<std::endl;
    while(std::cin.rdbuf()->in_avail()>0) //отбрасываем whitespace -ы
    {
        int ich=std::cin.peek();
        std::cout<<"ich="<<ich<<std::endl;

        std::cin.ignore(1); //peek блокирует ввод, поэтому его делаем уже внутри цикла
    }
    std::cout<<"in_avail()="<<std::cin.rdbuf()->in_avail()<<std::endl;
    std::cin.ignore(1);




//ValidInput();
//int ich=std::cin.peek();
//std::cout<<"ich="<<ich<<std::endl;
//std::cin.ignore(1);
//std::cout<<"after ignore"<<std::endl;
//ich=std::cin.peek();
//std::cout<<"ich="<<ich<<std::endl;

return 0;
}
