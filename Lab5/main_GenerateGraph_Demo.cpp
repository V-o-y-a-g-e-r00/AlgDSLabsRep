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

    int N=6;

    presenthandler PresentHandler; //для отображения шагов
    PresentHandler.Mode=2;

    plothandler PlotHandler;

   Graph Graph1(N, false);
    Graph1.IsWithVerticesWeights=false;
    
    //GenerateAdjacencyProb(Graph1, 0.5, generator1, false);
    //GenerateAdjacencyMNumberNoLoops(Graph1, 4, generator1);
// try{ GenerateAdjacencyMNumberNoLoops(Graph1, 4, generator1); }
 //   catch(std::string str)
 //   {
 //       std::cout<<"exeption:"<<str<<std::endl;
 //       return -1;
 //   }

/*    int iteration=0;
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
*/
    GenerateGraph(Graph1, 6, 100, generator1, PresentHandler);

    Graph1.ShowPlot(1, "Pic");

/*    std::vector<std::vector<int>> MPath(N), MPathLength(N);
    for(auto& i: MPath) i.resize(N);
    for(auto& i: MPathLength) i.resize(N);

    FloydWarshall(Graph1, MPathLength, MPath);
    Graph1.PrintEdges();
    PrintMatrix(MPathLength, "MPathLength");
    PrintMatrix(MPath, "MPath");
*/
}
