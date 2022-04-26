#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"

int main(int, char**) {
 //   int seed=time(0);
    int seed=2;
    std::default_random_engine generator1(seed);
    presenthandler PrHandler;
    PrHandler.Mode=0;

    maze Maze(10,10);
 /*   for(int i=0; i<Maze.n; i++)
    {
        for(int j=0; j<Maze.m; j++)
        {
            Maze.SetCellWalls(i,j, 1, false, true);
            Maze.SetCellWalls(i,j, 2, false, true);
        }
    }
*/
 /*   try
    {
         MazeFromFile(Maze, (char*)"Maze.txt");
    }
    catch(std::string str)
    {
        std::cout << str << std::endl;
    }
*/
  //  WallsReduce(Maze, 0.5, generator1);
   WilsonReduced(Maze, generator1, PrHandler, 0.3);
   Maze.ShowDecorate((char*)"cout",0);
 //   Maze.ShowDecorate((char*)"MazeOut.txt");
 //   Wilson(Maze, generator1, PrHandler);

}
