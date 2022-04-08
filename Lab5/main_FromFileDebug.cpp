#include <iostream>
#include "Graph.h"
#include "Func.h"
#include "ShortestPathFunc.h"
#include "presenthandler.h"

int main(int, char**) {
Graph Graph1(8);
Graph1.IsWithVerticesWeights=true;
//Graph1.Edges.at(3).at(3).Adjacency=-1;
Graph1.edgesEdges.AdjacencyFromFile((char *)"AdjM.txt");
Graph1.PrintEdges();
Graph1.vertsVertices.xyFromFile((char *)"xyVert.txt");
Graph1.PrintVertices();
//Graph1.edgesEdges.WeightFromFile((char*)"WeightEdgesM.txt");
//Graph1.vertsVertices.WeightFromFile((char*)"WeightVert.txt");

std::default_random_engine generator1(1);
GenerateWeights(Graph1, generator1, 3, 15);



/*
std::vector<std::vector<int>> Pathes;
presenthandler PresentHandler;
PresentHandler.Mode=2;
int src=0;
for(int src=0; src<8; src++)
{
    Dijkstra(Graph1, src, Pathes, PresentHandler);
}

Graph1.ShowPlot(false, "pic", false);*/
std::vector<std::vector<int>> MPath;
std::vector<std::vector<int>> MPathLength;
FloydWarshallCallBackParamsTailHandler(8,MPathLength,MPath);
FloydWarshall(Graph1, MPathLength, MPath);
std::cout<<"-------------------------------"<<std::endl;
PrintMatrix(MPathLength, "");



return 0;
}