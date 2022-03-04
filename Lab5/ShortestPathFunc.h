#ifndef SHORTESTPATHFUNC_H_INCLUDED
#define SHORTESTPATHFUNC_H_INCLUDED

#include <vector>
#include <limits>

#include "vertices.h"
#include "edges.h"

#include "Func.h"

//matrix - матрица смежности
void FloydWarshall(vertices& Vertices, edges& Edges, std::vector<std::vector<int>>& MPathLength, std::vector<std::vector<int>>& MPath)
{
    for(int i=0; i< Edges.Vector.size(); i++) //заполняем матрицу стартовыми значениями.
    {
        for(int j=0; j< Edges.Vector.size(); j++)
        {
            MPath.at(i).at(j)=j; //граф у нас связный, так что будем надеяться, что какой-либо путь алгоритм найдет.
            if(Edges.Vector.at(i).at(j).Adjacency==0) //можно обойтись Adjacency, но алг. будет более громоздким
                if(i==j) MPathLength.at(i).at(j)=0; //тут есть подводный. У нас граф вроде бы без петель, но мы подразумеваем, что петли все-таки есть, и их вес равен нулю.
                else MPathLength.at(i).at(j)=std::numeric_limits<int>::max();
            else MPathLength.at(i).at(j)=Edges.Vector.at(i).at(j).Weight;
        }
    }
    //Пробегаемся по всем вершинам и ищем более короткий путь
    //через вершину k
    for(int k = 0; k < Edges.Vector.size(); k++) {
        for(int i = 0; i < Edges.Vector.size(); i++) {
            for(int j = 0; j < Edges.Vector.size(); j++) {
                //Новое значение ребра равно минимальному между старым
                //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
                if(MPathLength.at(i).at(j)>(long long int)MPathLength.at(i).at(k)+(long long int)MPathLength.at(k).at(j))
                {
                    MPathLength.at(i).at(j)=MPathLength.at(i).at(k)+MPathLength.at(k).at(j);
                    MPath.at(i).at(j)=MPath.at(i).at(k);
                //    PrintMatrix(MPath, "MPath");
                 //   getchar();
                }
             //   matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);

            }
        }
    }

}

#endif //SHORTESTPATHFUNC_H_INCLUDED