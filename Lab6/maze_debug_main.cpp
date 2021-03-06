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

    maze Maze(6,6);
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
//    WilsonReduced(Maze, generator1, PrHandler, 0.3);
/*    Maze.SetCellWalls(0,0,3, false);
    Maze.SetCellWalls(0,1,3, false);
    Maze.SetCellWalls(1,0,3, false);
    Maze.SetCellWalls(1,1,3, false);
    Maze.SetCellWalls(1,0,0, false);
    Maze.SetCellValue(1,1, '@');*/
   
 //   Maze.ShowDecorate((char*)"MazeOut.txt");
    Wilson(Maze, generator1, PrHandler);
    Maze.ResetValues();
    std::stringstream ss;
    std::string str("maze  by me");
    char ch='N';
    int i=0, j=0;
/*    for(int k=0; (k<str.size())&& i<Maze.n && j<Maze.m; k++)
    {
        ch=str.c_str()[k];
    //    str.erase();
    //   str.pop_back(); 
        if (ch!=' ') Maze.SetCellValue(i,j, ch);
        j++;
        i+=j/Maze.m;
        j=j%Maze.m;

    }
    */
   Maze.SetValuesByStr(str);
    Maze.ShowDecorate((char*)"cout",0, 2, true);
 //   std::cout << ch<<std::endl;
}
