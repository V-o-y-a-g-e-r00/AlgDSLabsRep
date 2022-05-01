#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"
#include "MazeSearchAlg.h"

int main(int, char**) {
  //  int seed=time(0);
    int seed=4;
    std::default_random_engine generator1(seed);
    presenthandler PrHandler;
    PrHandler.Mode=1;

    mazeWeighted MazeWeighted(5,5, 1);
    WilsonReduced(MazeWeighted, generator1, PrHandler, 0.3);
    RandomCircules(MazeWeighted, generator1, 2, 2, 0.2, 1, 0.5); //1, 3, 0.03, 2, 0.5

    MazeWeighted.WeightsToValues();
    MazeWeighted.ShowDecorate((char*)"cout",1, 2, true);

  std::vector<std::pair<int,int>> Path;
  Dijkstra(MazeWeighted, 0, 0, 4, 4, Path, PrHandler);
  PrintVector(Path, "Path");

}
