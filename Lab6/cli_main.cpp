#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"
#include "MazeSearchAlg.h"

int main(int, char**) {

std::cin.sync_with_stdio(false);

std::cin.clear();
std::cout<<"std::cin.rdbuf()->in_avail()="<<std::cin.rdbuf()->in_avail()<<std::endl;
std::cin.ignore(std::cin.rdbuf()->in_avail()-1);

std::string str;
std::cout<<"Ввод:"<<std::endl;
std::cin>>str;
std::cout<<"str="<<str<<std::endl;




std::cin.clear();
std::cout<<"std::cin.rdbuf()->in_avail()="<<std::cin.rdbuf()->in_avail()<<std::endl;
std::cin.ignore(std::cin.rdbuf()->in_avail()-1);


std::cout<<"Ввод:"<<std::endl;
std::cin>>str;
std::cout<<"str="<<str<<std::endl;
std::cout<<"std::cin.rdbuf()->in_avail()="<<std::cin.rdbuf()->in_avail()<<std::endl;

return 0;
}
