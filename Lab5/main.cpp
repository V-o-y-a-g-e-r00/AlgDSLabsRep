#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <iomanip> //setprecision
//#include <random> 
//#include <filesystem> //для создания директорий

#include "presenthandler.h"
#include "Func.h"
#include "ShortestPathFunc.h"

//#include "BaseGraph.h"
//#include "VisualGraph.h"
#include "Graph.h"
#include "StatisticsGraph.inl"

#include "plothandler.h"


int main(int, char**) {
    
    //  int seed=time(0);
    int seed=4; //с seed 4 получается 3 итерации в Adjacency при n=5 m=4
    std::default_random_engine generator1(seed), generator2(seed); //будут генерировать одинаковые последовательности.

    int N=5;

    presenthandler PresentHandler0, PresentHandler1; //для отображения шагов
    PresentHandler0.Mode=0;
    PresentHandler1.Mode=0;

    plothandler PlotHandler;

    std::vector<std::vector<int>> MPath, MPathLength;
    StatisticsGraph(5, 50, 5, 0.5, 100, 1, generator1, PresentHandler0, PlotHandler.addandreturn("FloydWarshellOut.txt"), GenerateGraph, FloydWarshall, FloydWarshallCallBackParamsTailHandler, MPathLength, MPath);
    
    int SourceIndex=0;
    std::vector<std::vector<int>> Pathes;
    StatisticsGraph(5, 50, 5, 0.5, 100, 1, generator2, PresentHandler0, PlotHandler.addandreturn("DijkstraOut.txt"), GenerateGraph, Dijkstra, DijkstraCallBackParamsTailHandler, SourceIndex, Pathes, PresentHandler1);

    PlotHandler.tofile("Plotfilelist.txt");
    system("./PlotScript.bash");

}
