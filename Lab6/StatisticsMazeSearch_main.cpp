#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include "MazeSearchAlg.h"
#include "StatisticsMazeSearch.inl"

#include "presenthandler.h"
#include "plothandler.h"

int main(int, char**) {
    int seed=time(0);
    //int seed=2;
    std::default_random_engine generator1(seed);

    presenthandler PrHandler;
    PrHandler.Mode=0; //11 выводить генерируемые лабиринты
    plothandler PlotHandler;

    int NStart=4, NEnd=500, NStep=10, NumberOfRun=1;
    double MRatio=1;
    StatisticsMazeSearch(NStart, NEnd, NStep, MRatio, NumberOfRun, generator1, PrHandler, PlotHandler.addandreturn("DijkstraOut.txt"), Dijkstra);
    StatisticsMazeSearch(NStart, NEnd, NStep, MRatio, NumberOfRun, generator1, PrHandler, PlotHandler.addandreturn("AStarOut.txt"), AStar);
    
    PlotHandler.tofile("Plotfilelist.txt");
    system("./PlotScript.bash");
}