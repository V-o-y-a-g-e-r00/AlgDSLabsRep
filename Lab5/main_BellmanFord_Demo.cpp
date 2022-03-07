#include <iostream>
//#include <filesystem> //для создания директорий

#include "presenthandler.h"
#include "Func.h"
#include "ShortestPathFunc.h"

#include "Graph.h"
#include "StatisticsGraph.inl"

#include "plothandler.h"


int main(int, char**) {
    
    //  int seed=time(0);
    int seed=4; //с seed 4 получается 3 итерации в Adjacency при n=5 m=4
    std::default_random_engine generator1(seed);

    presenthandler PresentHandler; //для отображения шагов
    PresentHandler.Mode=0;

    int N=5;
    Graph Graph1(N);
    Graph1.IsWithVerticesWeights=true;
    GenerateGraph(Graph1, 4, 100, generator1, PresentHandler);
    Graph1.ShowPlot(0, "Pic");

    PresentHandler.Mode=1;
    std::vector<int> x;
    std::vector<std::vector<int>> D;
    int s=0;
    BellmanFord(Graph1, s, x, D);

//    Graph1.ShowPlot(false, "");
    PrintMatrix(D, "BellmanFord D");

    std::cout <<"x=";
    for(auto& i: x) std::cout<<i<<"\t";
    std::cout<<std::endl;
}