#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"

int main(int, char**) {
//    int seed=time(0);
    //int seed=2;
//    std::default_random_engine generator1(seed);

    maze Maze(10,10);
    for(int i=0; i<Maze.n; i++)
    {
        for(int j=0; j<Maze.m; j++)
        {
            Maze.SetCellWalls(i,j, 0, false);
            Maze.SetCellWalls(i,j, 3, false);
        }
    }
 //   Maze.SetCellWalls(0,0, 0, false);
 //   Maze.SetCellWalls(0,0, 3, false);
//    Maze.SetCellWalls(1,1, 1, false);
 //   Maze.SetCellWalls(1,1, 2, false);
 /*   try
    {
         MazeFromFile(Maze, (char*)"Maze.txt");
    }
    catch(std::string str)
    {
        std::cout << str << std::endl;
    }
*/

   Maze.ShowDecorate((char*)"cout",0);
 //   Maze.ShowDecorate((char*)"MazeOut.txt");
 //   Wilson(Maze, generator1, PrHandler);

}
