#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include "StatisticsMaze.inl"

#include "presenthandler.h"
#include "plothandler.h"

int main(int, char**) {
    int seed=time(0);
    //int seed=2;
    std::default_random_engine generator1(seed);

    presenthandler PrHandler;
    PrHandler.Mode=0; //11 выводить генерируемые лабиринты
    plothandler PlotHandler;

    int NStart=4, NEnd=50, NStep=5, NumberOfRun=100;
    double MRatio=1;
    StatisticsMaze(NStart, NEnd, NStep, MRatio, NumberOfRun, generator1, PrHandler, PlotHandler.addandreturn("WilsonOut.txt"), Wilson); //200x200 около 9 секунд генерируются
    StatisticsMaze(NStart, NEnd, NStep, MRatio, NumberOfRun, generator1, PrHandler, PlotHandler.addandreturn("WilsonSerialOut.txt"), WilsonSerial);
    StatisticsMaze(NStart, NEnd, NStep, MRatio, NumberOfRun, generator1, PrHandler, PlotHandler.addandreturn("AldousBroderOut.txt"), AldousBroder);
    int alpha=0; //угол, куда смотрит вырез стены
    StatisticsMaze(NStart, NEnd, NStep, MRatio, NumberOfRun, generator1, PrHandler, PlotHandler.addandreturn("BinaryTreeOut.txt"), BinaryTree, alpha);
    
    PlotHandler.tofile("Plotfilelist.txt");
    system("./PlotScript.bash");
}