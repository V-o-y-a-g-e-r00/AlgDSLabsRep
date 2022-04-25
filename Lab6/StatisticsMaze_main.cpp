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
    PrHandler.Mode=11;
    plothandler PlotHandler;

    int NStart=4, NEnd=6, NStep=1, NumberOfRun=1;
    double MRatio=1;
    StatisticsMaze(NStart, NEnd, NStep, MRatio, NumberOfRun, generator1, PrHandler, PlotHandler.addandreturn("AldousBroderOut.txt"), AldousBroder);
    StatisticsMaze(NStart, NEnd, NStep, MRatio, NumberOfRun, generator1, PrHandler, PlotHandler.addandreturn("WilsonOut.txt"), Wilson);
    StatisticsMaze(NStart, NEnd, NStep, MRatio, NumberOfRun, generator1, PrHandler, PlotHandler.addandreturn("WilsonSerialOut.txt"), WilsonSerial);
    int alpha=0; //угол, куда смотрит вырез стены
    StatisticsMaze(NStart, NEnd, NStep, MRatio, NumberOfRun, generator1, PrHandler, PlotHandler.addandreturn("BinaryTreeOut.txt"), BinaryTree, alpha);
    
    PlotHandler.tofile("Plotfilelist.txt");
    system("./PlotScript.bash");
}