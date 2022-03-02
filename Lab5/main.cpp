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


/*template<typename T>
void PrintMatrix(std::vector<std::vector<T>>& Matrix, const char* MatrixName)
{
    typename std::vector<std::vector<T>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам) .Без typename вообще не компилируется, хотя казалось бы.
    typename std::vector<T>::iterator iterj;
    for(iteri=Matrix.begin(); iteri!=Matrix.end(); iteri++)
    {
        std::cout<< MatrixName<<"["<<std::distance(Matrix.begin(), iteri) <<"]=";
        for(iterj=iteri->begin(); iterj!=iteri->end(); iterj++)
        {
            std::cout<< (*iterj)<<"\t";
        }
        std::cout<<std::endl;
    }
} */
/*template<typename T>
void PrintMatrixToFile(std::vector<std::vector<T>>& Matrix, const char* MatrixName, const char* filename)
{
    std::ofstream fd(filename);
    typename std::vector<std::vector<T>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам) .Без typename вообще не компилируется, хотя казалось бы.
    typename std::vector<T>::iterator iterj;
    for(iteri=Matrix.begin(); iteri!=Matrix.end(); iteri++)
    {
       // fd<< MatrixName<<"["<<std::distance(Matrix.begin(), iteri) <<"]=";
        for(iterj=iteri->begin(); iterj!=iteri->end(); iterj++)
        {
            fd<< (*iterj)<<"\t";
        }
        fd<<std::endl;
    }
    fd.close();
}*/

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


    GenerateAdjacencyProb(Edges, seed, 0.5, false);
//    try {GenerateAdjacencyMNumberWithLoops(Edges, seed, 25);}
 /*   try {GenerateAdjacencyMNumberNoLoops(Edges, seed, 4);}
    catch(std::string str)
    {
        std::cout<<"exeption:"<<str<<std::endl;
        return -1;
    }*/

//    PrintMatrix<int>(AdjacencyMatrix, "AdjacencyMatrix");
//    PrintMatrixToFile(AdjacencyMatrix, "AdjacencyMatrix", "AdjacencyMatrixOut.txt");

    Edges.SetEdgesForPlot();
    Edges.PrintEdges(); 
    Edges.PrintEdges("Edges.txt"); //вывод информации о ребрах для наглядности. Не используется для рисования графа
    Vertices.SetVertXYForPlot();
    Vertices.PrintVertices();
    Vertices.PrintVertices("Vertices.dat");
    SetVarsForScript(Edges, 0, 0, "Pic1", "VarsForScript.dat"); //число вершин и ребер в файл
    system("./PlotGraph.bash");
}
