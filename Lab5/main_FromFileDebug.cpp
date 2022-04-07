#include <iostream>
#include "Graph.h"


int main(int, char**) {
Graph Graph1(4);
Graph1.Edges.at(3).at(3).Adjacency=-1;
//Graph1.edgesEdges.AdjacencyFromFile((char *)"AdjM.txt");
//Graph1.PrintEdges();
Graph1.vertsVertices.xyFromFile((char *)"xyVert.txt");
Graph1.PrintVertices();
return 0;
}