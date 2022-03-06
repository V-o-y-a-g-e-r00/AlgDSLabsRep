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

    int N=5;

    presenthandler PresentHandler; //для отображения шагов
    PresentHandler.Mode=0;

    plothandler PlotHandler;

 /*  Graph Graph1(N, false);
    Graph1.IsWithVerticesWeights=false;
    
    //GenerateAdjacencyProb(Graph1, 0.5, generator1, false);
    //GenerateAdjacencyMNumberNoLoops(Graph1, 4, generator1);
// try{ GenerateAdjacencyMNumberNoLoops(Graph1, 4, generator1); }
 //   catch(std::string str)
 //   {
 //       std::cout<<"exeption:"<<str<<std::endl;
 //       return -1;
 //   }

    int iteration=0;
    do
    {
        std::cout<<"Generating Adjacency: iteration: "<<iteration<<std::endl;
       
        try {GenerateAdjacencyMNumberNoLoops(Graph1, 4, generator1);}
        catch(std::string str)
        {
            std::cout<<"exeption:"<<str<<std::endl;
            return -1;
        }
        iteration++;
    }while(!IsConnectedDFS(Graph1, 0, PresentHandler));
    GenerateWeights(Graph1, generator1, 1, 100); //все норм. Если seed принял какое-либо значение, то им определяется количество попыток, которые будут сделаны, чтобы получить Adjacency однозначно, поэтому при данном seed Weight будет также однозначным

    Graph1.ShowPlot(false, "Pic");

    std::vector<std::vector<int>> MPath(N), MPathLength(N);
    for(auto& i: MPath) i.resize(N);
    for(auto& i: MPathLength) i.resize(N);

    FloydWarshall(Graph1, MPathLength, MPath);
    Graph1.PrintEdges();
    PrintMatrix(MPathLength, "MPathLength");
    PrintMatrix(MPath, "MPath");

*/
    std::vector<std::vector<int>> MPath, MPathLength;
    StatisticsGraph(10, 100, 1, 0.2, 100, 1, generator1, PresentHandler, PlotHandler.addandreturn("FloydWarshellOut1.txt"), GenerateGraph, FloydWarshall, FloydWarshallCallBackParamsTailHandler, MPathLength, MPath);
    

    PlotHandler.tofile("Plotfilelist.txt");
    system("./PlotScript.bash");

}
