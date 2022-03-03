#ifndef SHORTESTPATHFUNC_H_INCLUDED
#define SHORTESTPATHFUNC_H_INCLUDED

#include <vector>
#include <limits>

#include "vertices.h"
#include "edges.h"

#include "Func.h"

//matrix - матрица смежности
void FloydWarshall(vertices& Vertices, edges& Edges, std::vector<std::vector<int>>& MPath)
{
    for(int i=0; i< MPath.size(); i++) //заполняем матрицу стартовыми значениями.
    {
        for(int j=0; j< MPath.size(); j++)
        {
            MPath.at(i).at(j)=j; //граф у нас связный, так что будем надеяться, что какой-либо путь алгоритм найдет.
            if(Edges.Vector.at(i).at(j).Adjacency==0) Edges.Vector.at(i).at(j).Weight=std::numeric_limits<int>::max(); //можно обойтись Adjacency, но алг. будет более громоздким
            
        }
    }
    PrintMatrix(MPath, "MPath");
    Edges.PrintEdges();
    //Пробегаемся по всем вершинам и ищем более короткий путь
    //через вершину k
    for(int k = 0; k < Edges.Vector.size(); k++) {
        for(int i = 0; i < Edges.Vector.size(); i++) {
            for(int j = 0; j < Edges.Vector.size(); j++) {
                //Новое значение ребра равно минимальному между старым
                //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
                if(Edges.Vector.at(i).at(j).Weight>(long long int)Edges.Vector.at(i).at(k).Weight+(long long int)Edges.Vector.at(k).at(j).Weight)
                {
                    Edges.Vector.at(i).at(j).Weight=Edges.Vector.at(i).at(k).Weight+Edges.Vector.at(k).at(j).Weight;
                    MPath.at(i).at(j)=MPath.at(i).at(k);
                    PrintMatrix(MPath, "MPath");
                    getchar();
                }
             //   matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);

            }
        }
    }

}
/*
void originalFloydWarshall(double **matrix, int numberOfVert, int **MPath) { //double **matrix-матрица исходных расстояний, туда же пишется результат, int numberOfVert-число вершин, int **MPath-матрица маршрутизации
  //  int MPath[numberOfVert][numberOfVert]; //матрица 1-ых элеметов в пути от i до j;  Т.е. путь от i до j такой: i->MPath[i][j]->...->j
    for(int i=0; i< numberOfVert; i++) //заполняем матрицу стартовыми значениями.
    {
        for(int j=0; j< numberOfVert; j++)
        {
            MPath[i][j]=j;
        }
    }
    //Пробегаемся по всем вершинам и ищем более короткий путь
    //через вершину k
    for(int k = 0; k < numberOfVert; k++) {
        for(int i = 0; i < numberOfVert; i++) {
            for(int j = 0; j < numberOfVert; j++) {
                //Новое значение ребра равно минимальному между старым
                //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
                if(matrix[i][j]>matrix[i][k]+matrix[k][j])
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    MPath[i][j]=MPath[i][k];
                }
             //   matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);

            }
        }
    }
}
*/

#endif //SHORTESTPATHFUNC_H_INCLUDED