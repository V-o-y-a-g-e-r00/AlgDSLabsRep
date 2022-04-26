#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"
#include "MazeSearchAlg.h"

int main(int, char**) {
 //   int seed=time(0);
    int seed=2;
    std::default_random_engine generator1(seed);
    presenthandler PrHandler;
    PrHandler.Mode=1;

    maze Maze(5,5);
 
  //  WallsReduce(Maze, 0.5, generator1);
   WilsonReduced(Maze, generator1, PrHandler, 0.3);
   Lee(Maze, 0,0, Maze.n-1, Maze.m-1, PrHandler);
   Maze.ShowDecorate((char*)"cout",0);
 //   Maze.ShowDecorate((char*)"MazeOut.txt");
 //   Wilson(Maze, generator1, PrHandler);

}