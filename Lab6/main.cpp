#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"

int main(int, char**) {
   // int seed=time(0);
    int seed=2;
    std::default_random_engine generator1(seed);

    maze Maze(10,10);
/*    try
    {
         MazeFromFile(Maze, (char*)"Maze.txt");
    }
    catch(std::string str)
    {
        std::cout << str << std::endl;
    }
*/
    
    AldousBroder(Maze, generator1);
    Maze.ShowDecorate((char*)"cout",1);
 //   Maze.ShowDecorate((char*)"MazeOut.txt");


}
