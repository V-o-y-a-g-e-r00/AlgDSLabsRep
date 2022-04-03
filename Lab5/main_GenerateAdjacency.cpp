#include <iostream>
#include "Graph.h"
#include "Func.h"

int main(int, char**) {

    std::default_random_engine generator;
    Graph Graph1(10);
//    Graph1.IsOriented=true;

    for(int k=0; k<10000; k++)
    {
        GenerateAdjacencyProb(Graph1, 0.3, generator, false);
        for(auto& i:Graph1.Edges) //Увеличиваем вес на 1 и сбрасываем матрицу смежности
        {
            for(auto& j:i)
            {
                if(j.Adjacency==1)
                {
                    j.Weight++;
                    j.Adjacency=0;
                }
            }
        }
    }
    for(int i=0; i<Graph1.Edges.size(); i++) //Увеличиваем вес на 1 и сбрасываем матрицу смежности
    {
        for(int j=0; j<Graph1.Edges.at(i).size(); j++)
        {
            if(i!=j) Graph1.Edges.at(i).at(j).Adjacency=1;
        }
    }


    Graph1.ShowPlot();
    Graph1.PrintEdges();
    return 0;
}