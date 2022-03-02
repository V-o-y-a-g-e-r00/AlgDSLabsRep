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





int main(int, char**) {
    int seed=time(0);
    //int seed=0; 

    int N=5;
    vertices Vertices(N);
    edges Edges(N);


 //   GenerateAdjacencyProb(Edges, seed, 0.5, false);
//    try {GenerateAdjacencyMNumberWithLoops(Edges, seed, 25);}
/*    try {GenerateAdjacencyMNumberNoLoops(Edges, seed, 6);}
    catch(std::string str)
    {
        std::cout<<"exeption:"<<str<<std::endl;
        return -1;
    }
*/
    int iteration=0;
    std::default_random_engine generator(seed);
    while(!IsConnectedDFS(Vertices, Edges, 1, false))
    {
        ShowPlot(Vertices, Edges);
        getchar();
        std::cout<<"Generating Adjacency: iteration: "<<iteration<<std::endl;
        Vertices.ResetColors();
        try {GenerateAdjacencyMNumberNoLoops(Edges, 4, generator);}
        catch(std::string str)
        {
            std::cout<<"exeption:"<<str<<std::endl;
            return -1;
        }
        iteration++;
    }


    Vertices.SetVertXYForPlot();
    Vertices.PrintVertices();
    Vertices.PrintVertices("Vertices.dat");
    Edges.SetEdgesForPlot(); //Вывод в файл для рисования графа
    Edges.PrintEdges(); 
    Edges.PrintEdges("Edges.txt"); //вывод информации о ребрах для наглядности. Не используется для рисования графа

    SetVarsForScript(Edges, false, false, "Pic1", "VarsForScript.dat"); //число вершин и ребер в файл
    system("./PlotGraph.bash");
}
