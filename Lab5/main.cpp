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

/*bool DFSConnectivityCheck(std::vector<std::vector<int>>& AdjacencyMatrix, std::vector<vertex>& vertices) //Проверка связности графа с помощью обхода в глубину
{
    return false;
}*/
int main(int, char**) {
    int seed=time(0);
    //int seed=0; 

    int N=5;
    vertices Vertices(N);
    edges Edges(N);


    GenerateAdjacencyProb(Edges, seed, 0.5, true);
//    try {GenerateAdjacencyMNumberWithLoops(Edges, seed, 25);}
 /*   try {GenerateAdjacencyMNumberNoLoops(Edges, seed, 4);}
    catch(std::string str)
    {
        std::cout<<"exeption:"<<str<<std::endl;
        return -1;
    }*/

//    PrintMatrix<int>(AdjacencyMatrix, "AdjacencyMatrix");
//    PrintMatrixToFile(AdjacencyMatrix, "AdjacencyMatrix", "AdjacencyMatrixOut.txt");
    Vertices.SetVertXYForPlot();
    Vertices.PrintVertices();
    Vertices.PrintVertices("Vertices.dat");
    Edges.SetEdgesForPlot(); //Вывод в файл для рисования графа
    Edges.PrintEdges(); 
    Edges.PrintEdges("Edges.txt"); //вывод информации о ребрах для наглядности. Не используется для рисования графа

    SetVarsForScript(Edges, true, false, "Pic1", "VarsForScript.dat"); //число вершин и ребер в файл
    system("./PlotGraph.bash");
}
