#include <iostream>
#include "Graph.h"


int main(int, char**) {
Graph Graph1(4);
Graph1.edgesEdges.AdjacencyFromFile((char *)"AdjM.txt");
Graph1.PrintEdges();
return 0;
}