#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <iomanip> //setprecision
//#include <random> 
//#include <filesystem> //для создания директорий

#include "vertices.h"
#include "edges.h"
#include "presenthandler.h"
#include "Func.h"
#include "ShortestPathFunc.h"

#include "BaseGraph.h"
#include "VisualGraph.h"
#include "Graph.h"


int main(int, char**) {
    int seed=4; //с seed 4 получается 3 итерации в Adjacency при n=5 m=4
     int N=5;

    Graph Graph1(N, false);
    Graph1.IsWithVerticesWeights=true;
    std::default_random_engine generator1(seed);
    GenerateAdjacencyMNumberNoLoopsGraph(Graph1, 4, generator1);
    Graph1.edgesEdges.ResetColors();
    Graph1.ShowPlot(false, "Pic");
    getchar();

 

  //  int seed=time(0);
    

   
    vertices Vertices(N);
    edges Edges(N);

    presenthandler PresentHandler; //для отображения шагов
    PresentHandler.Mode=0;


 //   GenerateAdjacencyProb(Edges, seed, 0.5, false);
//    try {GenerateAdjacencyMNumberWithLoops(Edges, seed, 25);}
/*    try {GenerateAdjacencyMNumberNoLoops(Edges, seed, 6);}
    catch(std::string str)
    {
        std::cout<<"exeption:"<<str<<std::endl;
        return -1;
    } */

    int iteration=0;
    std::default_random_engine generator(seed);
    do
    {
        std::cout<<"Generating Adjacency: iteration: "<<iteration<<std::endl;
       
        try {GenerateAdjacencyMNumberNoLoops(Edges, 4, generator);}
        catch(std::string str)
        {
            std::cout<<"exeption:"<<str<<std::endl;
            return -1;
        }
        iteration++;
    }while(!IsConnectedDFS(Vertices, Edges, 0, PresentHandler));
    GenerateWeights(Edges, generator, 1, 100); //все норм. Если seed принял какое-либо значение, то им определяется количество попыток, которые будут сделаны, чтобы получить Adjacency однозначно, поэтому при данном seed Weight будет также однозначным

    Vertices.PrintVertices();
    Edges.PrintEdges(); 
    ShowPlot(Vertices, Edges, false, false, "PicRez");

    std::vector<std::vector<int>> MPath(N), MPathLength(N);
    for(auto& i: MPath) i.resize(N);
    for(auto& i: MPathLength) i.resize(N);

    MPath[0][0]=1;
    FloydWarshall(Vertices, Edges, MPathLength, MPath);
    Edges.PrintEdges();
    PrintMatrix(MPathLength, "MPathLength");
    PrintMatrix(MPath, "MPath");

}
