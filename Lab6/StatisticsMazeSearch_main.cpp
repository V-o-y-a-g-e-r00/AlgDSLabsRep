#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include "MazeSearchAlg.h"
#include "StatisticsMazeSearch.inl"

#include "presenthandler.h"
#include "plothandler.h"

#include <thread>

int main(int, char**) {
    int seed=time(0);
    //int seed=2;
    std::default_random_engine generator1(seed), generator2(seed), generator3(seed), generator4(seed);

    presenthandler PrHandler;
    PrHandler.Mode=0; //11 выводить генерируемые лабиринты
    plothandler PlotHandler;

    int NStart=4, NEnd=504, NStep=125, NumberOfRun=500;
    double MRatio=1;

    StatisticsMazeSearch StatisticsMazeSearch1, StatisticsMazeSearch2, StatisticsMazeSearch3, StatisticsMazeSearch4;
    std::thread thread1(&StatisticsMazeSearch::StatisticsMazeSearchFunc<mazeWeighted>, std::ref(StatisticsMazeSearch1), NStart, NEnd, NStep, MRatio, NumberOfRun, std::ref(generator1), std::ref(PrHandler), PlotHandler.addandreturn("DijkstraOut.txt"), Dijkstra);
    thread1.join();
    std::thread thread2(&StatisticsMazeSearch::StatisticsMazeSearchFunc<mazeWeighted>, std::ref(StatisticsMazeSearch2), NStart, NEnd, NStep, MRatio, NumberOfRun, std::ref(generator2), std::ref(PrHandler), PlotHandler.addandreturn("AStarOut.txt"), AStar);
    thread2.join();
    std::thread thread3(&StatisticsMazeSearch::StatisticsMazeSearchFunc<maze>, std::ref(StatisticsMazeSearch3), NStart, NEnd, NStep, MRatio, NumberOfRun, std::ref(generator3), std::ref(PrHandler), PlotHandler.addandreturn("LeeOut.txt"), Lee);
    thread3.join();
    std::thread thread4(&StatisticsMazeSearch::StatisticsMazeSearchFunc<maze>, std::ref(StatisticsMazeSearch4), NStart, NEnd, NStep, MRatio, NumberOfRun, std::ref(generator4), std::ref(PrHandler), PlotHandler.addandreturn("Lee2WavesOut.txt"), Lee2Waves);
    thread4.join();

 //   thread1.join();
 //   thread2.join();
 //   thread3.join();
 //   thread4.join();

    PlotHandler.tofile("Plotfilelist.txt");
    system("./PlotScript.bash");
}