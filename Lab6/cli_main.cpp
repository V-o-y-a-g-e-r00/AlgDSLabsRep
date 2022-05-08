#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"
#include "MazeSearchAlg.h"

int main(int, char**) {

std::cin.sync_with_stdio(false); //Синхронизируем с вводом stdio. Без этого не работает in_avail()

std::string str;
bool IsGood=false;
while(!IsGood)
{
    //Вводим используя стандартный поток ввода. (мерзкая штука)
    std::cin.clear(); //Очищаем флаги
    std::cin.ignore(std::cin.rdbuf()->in_avail()-1); //Пропускаем все символы в буфере

    std::cout<<"Ввод:"<<std::endl;
    std::cin>>str;
    std::cout<<"str="<<str<<std::endl;

    IsGood=true;
    //Проверяем на недопустимые симоволы
    if(str.find_first_not_of("0123456789")!=std::string::npos)
    {
        IsGood=false;
    }
    //Проверяем на лишние символы в потоке
        
//    std::cout<<"before isspace"<<std::endl;
    while(std::isspace(std::cin.peek()) && std::cin.rdbuf()->in_avail()-1!=0) std::cin.ignore(1); //отбрасываем whitespace -ы
//    std::cout<<"after isspace"<<std::endl;
    if(std::cin.rdbuf()->in_avail()-1!=0)
    {
        IsGood=false;
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
