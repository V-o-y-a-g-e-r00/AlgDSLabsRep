#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include "StatisticsMaze.inl"

int main(int, char**) {
    int seed=time(0);
    //int seed=2;
    std::default_random_engine generator1(seed);

    presenthandler PrHandler;
    PrHandler.Mode=1;
    StatisticsMaze( 4, 4, 1, 1.0 , 1, generator1, PrHandler, "filename", AldousBroder);
    int alpha=0; //угол, куда смотрит вырез стены
    StatisticsMaze( 4, 4, 1, 1.0 , 1, generator1, PrHandler, "filename", Wilson, alpha);
    

}