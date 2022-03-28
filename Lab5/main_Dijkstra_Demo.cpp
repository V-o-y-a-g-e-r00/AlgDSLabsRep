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
    std::default_random_engine generator1(seed);

    presenthandler PresentHandler; //для отображения шагов
    PresentHandler.Mode=1;

    int N=10;
    Graph Graph1(N);
    Graph1.IsWithVerticesWeights=true;
    GenerateGraph(Graph1, 11, 100, generator1, PresentHandler);
    Graph1.ShowPlot(0, "Pic");

    PresentHandler.Mode=1;
    std::vector<std::vector<int>> Pathes;
    int SourceIndex=0;
    Dijkstra(Graph1, SourceIndex, Pathes, PresentHandler);

//    Graph1.ShowPlot(false, "");
    PrintMatrix(Pathes, "Pathes");

}
