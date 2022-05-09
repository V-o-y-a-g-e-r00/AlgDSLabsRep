#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"
#include "MazeSearchAlg.h"

int main(int, char**) {

Config cg;
try
{
    cg.Read((char*)"Config.txt");
}
catch(std::string e)
{
    std::cout<<"exeption: " <<e<<std::endl;
}
cg.Print();
std::cout<<"-------------"<<std::endl;

int intVal;
std::string strVal;
//bool IsFound=cg.GetVal(std::string("seed"), intVal);
if(cg.GetVal(std::string("filenameFin"), intVal)) std::cout<<"intVal="<<intVal<<std::endl;
else std::cout<<"intVal does not exist! "<<std::endl;
if(cg.GetVal(std::string("filenameFin"), strVal)) std::cout<<"strVal="<<strVal<<std::endl;
else std::cout<<"strVal does not exist! "<<std::endl;

return 0;
}
