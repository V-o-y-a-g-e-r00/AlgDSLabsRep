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

    mazeWeighted MazeWeighted(10,10);
//    WeightCircule(MazeWeighted, 5, 5, 5, 2);
    for(int k=0; k<10; k++) RandomCircules(MazeWeighted, generator1, 1, 2, 0.5, 1, 0.2);

    MazeWeighted.WeightsToValues();
    MazeWeighted.ShowDecorate((char*)"cout",1, 2, true);
 //   std::cout << ch<<std::endl;
}
