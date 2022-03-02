#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <iomanip> //setprecision
//#include <random> 
//#include <filesystem> //для создания директорий

#include "vertices.h"
#include "edges.h"
#include "Func.h"


int DFS(vertices& Vertices, edges& Edges, int StartVert)
{
  /*  if(StartVert>=Vertices.Vector.size() || StartVert<0)
    {
        std::stringstream ss;
        ss<<"StartVert cannot be equal to "<< StartVert <<std::endl;
        throw(ss.str());
    }
    */
    Vertices.Vector.at(StartVert).Color=12;
    int ColoredVertNumber=1;
    for(int j=0; j<Vertices.Vector.size(); j++)
    {
        if((Edges.Vector.at(StartVert).at(j).Adjacency==1) && (Vertices.Vector.at(j).Color!=12))
        {
        //    Vertices.PrintVertices("Vertices.dat");
        //    system("./PlotGraph.bash");
        //    getchar();
            ColoredVertNumber+=DFS(Vertices, Edges, j);
            
        }
    }
    return ColoredVertNumber;
}
bool IsConnectedDFS(vertices& Vertices, edges& Edges, int StartVert) //Проверка связности графа с помощью обхода в глубину
{
    if(DFS(Vertices, Edges, StartVert)==Vertices.Vector.size()) return true;
    else return false;
}
int main(int, char**) {
    int seed=time(0);
    //int seed=0; 

    int N=5;
    vertices Vertices(N);
    edges Edges(N);


    GenerateAdjacencyProb(Edges, seed, 0.3, false);
//    try {GenerateAdjacencyMNumberWithLoops(Edges, seed, 25);}
 /*   try {GenerateAdjacencyMNumberNoLoops(Edges, seed, 4);}
    catch(std::string str)
    {
        std::cout<<"exeption:"<<str<<std::endl;
        return -1;
    }*/

 //   Vertices.SetVertXYForPlot();
 //   Edges.SetEdgesForPlot(); //Вывод в файл для рисования графа
 //   Edges.PrintEdges("Edges.txt");

    int temp=DFS(Vertices, Edges, 0);
    std::cout<<"temp="<<temp<<std::endl;
  //  test(Edges);

    Vertices.SetVertXYForPlot();
    Vertices.PrintVertices();
    Vertices.PrintVertices("Vertices.dat");
    Edges.SetEdgesForPlot(); //Вывод в файл для рисования графа
    Edges.PrintEdges(); 
    Edges.PrintEdges("Edges.txt"); //вывод информации о ребрах для наглядности. Не используется для рисования графа

    SetVarsForScript(Edges, true, false, "Pic1", "VarsForScript.dat"); //число вершин и ребер в файл
    system("./PlotGraph.bash");
}
