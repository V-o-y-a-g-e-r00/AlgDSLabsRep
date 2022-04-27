#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"
#include "MazeSearchAlg.h"
#include <utility>

int main(int, char**) {
 //   int seed=time(0);
    int seed=2;
    std::default_random_engine generator1(seed);
    presenthandler PrHandler;
    PrHandler.Mode=1;

    maze Maze(6,5);
 
    WallsReduce(Maze, 0.5, generator1);
//   WilsonReduced(Maze, generator1, PrHandler, 0.3);
   std::vector<std::pair<int,int>> Way;
    std::vector<int> Way1(10, 33);
   Lee2Waves(Maze, 2, 2, 2, 3, Way, PrHandler);
   PrintVector(Way, "Way");
//   Maze.ShowDecorate((char*)"cout",0);
 //   Maze.ShowDecorate((char*)"MazeOut.txt");
 //   Wilson(Maze, generator1, PrHandler);

}