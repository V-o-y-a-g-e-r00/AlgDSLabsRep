#ifndef SHORTESTPATHFUNC_H_INCLUDED
#define SHORTESTPATHFUNC_H_INCLUDED

#include "vertices.h"
#include "edges.h"
//matrix - матрица смежности

void originalFloydWarshall(vertices& Vertices, edges& Edges)

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



#endif //SHORTESTPATHFUNC_H_INCLUDED