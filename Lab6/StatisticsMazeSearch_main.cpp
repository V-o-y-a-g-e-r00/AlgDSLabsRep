#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include "MazeSearchAlg.h"
#include "StatisticsMazeSearch.inl"

#include "presenthandler.h"
#include "plothandler.h"

#include <thread>
void foor(int& i)
{
    std::cout<<"i="<<i<<std::endl;
}

int main(int, char**) {
    int seed=time(0);
    //int seed=2;
    std::default_random_engine generator1(seed), generator2(seed);

    presenthandler PrHandler;
    PrHandler.Mode=0; //11 выводить генерируемые лабиринты
    plothandler PlotHandler;

    int NStart=4, NEnd=200, NStep=10, NumberOfRun=1;
    double MRatio=1;

    StatisticsMazeSearch StatisticsMazeSearch1, StatisticsMazeSearch2;
    std::thread thread1(&StatisticsMazeSearch::StatisticsMazeSearchFunc, std::ref(StatisticsMazeSearch1), NStart, NEnd, NStep, MRatio, NumberOfRun, std::ref(generator1), std::ref(PrHandler), PlotHandler.addandreturn("DijkstraOut.txt"), Dijkstra);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1ms);
    std::thread thread2(&StatisticsMazeSearch::StatisticsMazeSearchFunc, std::ref(StatisticsMazeSearch2), NStart, NEnd, NStep, MRatio, NumberOfRun, std::ref(generator2), std::ref(PrHandler), PlotHandler.addandreturn("AStarOut.txt"), AStar);
    
    int i=1;
 //   std::thread thread1(foor, std::ref(i));
    thread1.join();
    thread2.join();

    PlotHandler.tofile("Plotfilelist.txt");
    system("./PlotScript.bash");
}