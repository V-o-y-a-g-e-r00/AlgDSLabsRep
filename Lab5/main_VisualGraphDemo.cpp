#include <iostream>
#include "Graph.h"


int main(int, char**) {

    Graph Graph1(25);
    Graph1.IsOriented=true;
//    Graph1.Edges.at(0).at(0).Adjacency=true;

    int x[]={11,3,3,12,12,6,   18, 15, 15,      21, 27, 27, 21, 21, 27,  31,31,37,37,31,     41,41,41,47,47};
    int y[]={17,17,30,30,24,24,     21,21,30,   21,21,30,30,25,25,       32, 21,21,30,30,   17,30,21,21,30};

    for(int i=0; i<Graph1.Vertices.size(); i++)
    {
        Graph1.Vertices.at(i).x=(x[i]-25)*2; Graph1.Vertices.at(i).y=-(y[i]-25)*2;
        if(i<=5)
        {
            Graph1.Vertices.at(i).Color=14;
        }
        if(i>=6 && i<=8)
        {
            Graph1.Vertices.at(i).Color=12;
        }
        if(i>=9 && i<=14)
        {
            Graph1.Vertices.at(i).Color=13;
        }
        if(i>=20 && i<=24)
        {
            Graph1.Vertices.at(i).Color=14;
        }
    }
    for(int i=0; i<5; i++) //G
    {
        Graph1.Edges.at(i).at(i+1).Adjacency=true;
        Graph1.Edges.at(i).at(i+1).Color=3;
        Graph1.Edges.at(i).at(i).Adjacency=true;
        Graph1.Edges.at(i).at(i).Color=3;
    }
    Graph1.Edges.at(5).at(5).Adjacency=true;
    Graph1.Edges.at(5).at(5).Color=3;

    for(int i=6; i<8; i++) //r
    {
        Graph1.Edges.at(i).at(i+1).Adjacency=true;
        Graph1.Edges.at(i).at(i+1).Color=2;
    }
    for(int i=9; i<14; i++) //a
    {
        Graph1.Edges.at(i).at(i+1).Adjacency=true;
        Graph1.Edges.at(i).at(i+1).Color=4;
    }
    for(int i=15; i<19; i++) //p
    {
        Graph1.Edges.at(i).at(i+1).Adjacency=true;
    }
    for(int i=20; i<24; i++) //h
    {
        Graph1.Edges.at(i).at(i+1).Adjacency=true;
    }

    Graph1.ShowPlot(0, "pic", false);
    return 0;
}