#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"

int main(int, char**) {
  //  int seed=time(0);
    int seed=1;
    std::default_random_engine generator1(seed);
    presenthandler PrHandler;
    PrHandler.Mode=0;

    mazeWeighted MazeWeighted(3,3);
    maze Maze(3,3);

	MazeFromFile(MazeWeighted, (char*)"MazeIn.txt");
	MazeFromFile(Maze, (char*)"MazeIn.txt");

//    WeightCircule(MazeWeighted, 5, 5, 5, 2);
 //   for(int k=0; k<10; k++)
//    WilsonReduced(MazeWeighted, generator1, PrHandler, 0.3);
//    RandomCircules(MazeWeighted, generator1, 1, 3, 0.03, 2, 0.5);

//    MazeWeighted.WeightsToValues();
    MazeWeighted.ShowDecorate((char*)"cout",1, 2, true);
    Maze.ShowDecorate((char*)"cout",1, 2, true);
	std::cout<<"MazeWeighted.Weights.size()="<<MazeWeighted.Weights.size()<<std::endl;
 //   std::cout << ch<<std::endl;
}
