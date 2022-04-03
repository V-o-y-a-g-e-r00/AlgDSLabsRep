#include <iostream>
#include "Graph.h"
#include "StatisticsGraph.inl"
#include "ShortestPathFunc.h"
#include "presenthandler.h"
#include "plothandler.h"
#include "Func.h" //GenerateGraph();



int main(int, char**) {

    Graph Graph1(5);
    std::default_random_engine generator1;
    presenthandler PresentHandler0;
    plothandler PlotHandler;

    int param1;
    int param2;
    char param3;
    StatisticsGraph(5, 10, 1, 0.5, 100, 1, generator1, PresentHandler0, PlotHandler.addandreturn("AlgFuncExampleOut.txt"), GenerateGraph, AlgFuncExample, AlgFuncExampleCallBackParamsTailHandler, param1, param2, param3);

    return 0;
}
