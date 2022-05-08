#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"
#include "MazeSearchAlg.h"

int main(int, char**) {

std::cin.sync_with_stdio(false); //Синхронизируем с вводом stdio. Без этого не работает in_avail() Важно вызвать эту функцию до первого чтения или ввода. Иначе последсвия будут непредсказуемыми.

PrintFile((char *)"Welcome.txt");
PrintFile((char *)"Menu.txt");



bool IsQuited=false;
int Choice=0;
while(!IsQuited)
{
    int Choice=ValidInput((char*)"пункт меню");
    std::cout<<"Выбран пункт меню="<<Choice<<std::endl;
    switch (Choice)
    {
    case 1:
        
        break;
    case 2:
        
        break;
    case 3:
        
        break;
    case 4:
        
        break;

    case 5:
        
        break;
    case 6:
        
        break;
    case 7:
        
        break;
    case 8:
        
        break;
    case 9:
        
        break;
    case 10:
        
        break;
    case 11:
        
        break;
    case 12:
        
        break;
    case 13:
        IsQuited=true;
        break;
    case 14:
        PrintFile((char*)"Help.txt");
        break;
    case 15:
        PrintFile((char*)"Menu.txt");
        break;
    default:
        std::cout<<"Нет такого пункта меню"<<std::endl;
        break;
    }
}


/*


std::cin.clear();
std::cout<<"std::cin.rdbuf()->in_avail()="<<std::cin.rdbuf()->in_avail()<<std::endl;
std::cin.ignore(std::cin.rdbuf()->in_avail()-1);


std::cout<<"Ввод:"<<std::endl;
std::cin>>str;
std::cout<<"str="<<str<<std::endl;
std::cout<<"std::cin.rdbuf()->in_avail()="<<std::cin.rdbuf()->in_avail()<<std::endl;
*/
return 0;
}
