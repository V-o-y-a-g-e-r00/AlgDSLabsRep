#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"

int main(int, char**) {
    int seed=time(0);
    //int seed=2;
    std::default_random_engine generator1(seed);

    maze Maze(5000,5000);
 /*   try
    {
         MazeFromFile(Maze, (char*)"Maze.txt");
    }
    catch(std::string str)
    {
        std::cout << str << std::endl;
    }
*/
    presenthandler PrHandler;
    PrHandler.Mode=1;
    AldousBroder(Maze, generator1, PrHandler);
 //   Maze.ShowDecorate((char*)"cout",0);
    Maze.ShowDecorate((char*)"MazeOut.txt");


}
