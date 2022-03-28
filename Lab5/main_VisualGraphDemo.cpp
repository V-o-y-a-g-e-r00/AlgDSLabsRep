#include <iostream>
#include "Graph.h"


int main(int, char**) {

    Graph Graph1(4);
    Graph1.IsOriented=true;
    Graph1.Edges.at(0).at(0).Adjacency=true;
    Graph1.Edges.at(0).at(1).Adjacency=true;
    Graph1.Edges.at(1).at(0).Adjacency=true;
    Graph1.ShowPlot(0, "pic");
    return 0;
}