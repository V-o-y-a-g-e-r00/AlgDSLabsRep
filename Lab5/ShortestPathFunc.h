#ifndef SHORTESTPATHFUNC_H_INCLUDED
#define SHORTESTPATHFUNC_H_INCLUDED

#include <vector>
#include <limits>

#include "Func.h"
#include "presenthandler.h"



//matrix - матрица смежности
void FloydWarshall(Graph& Graph1, std::vector<std::vector<int>>& MPathLength, std::vector<std::vector<int>>& MPath)
{
    for(int i=0; i< Graph1.Edges.size(); i++) //заполняем матрицу стартовыми значениями.
    {
        for(int j=0; j< Graph1.Edges.size(); j++)
        {
            MPath.at(i).at(j)=j; //граф у нас связный, так что будем надеяться, что какой-либо путь алгоритм найдет.
            if(Graph1.Edges.at(i).at(j).Adjacency==0) //можно обойтись Adjacency, но алг. будет более громоздким
                if(i==j) MPathLength.at(i).at(j)=0; //тут есть подводный. У нас граф вроде бы без петель, но мы подразумеваем, что петли все-таки есть, и их вес равен нулю.
                else MPathLength.at(i).at(j)=std::numeric_limits<int>::max();
            else MPathLength.at(i).at(j)=Graph1.Edges.at(i).at(j).Weight;
        }
    }
    //Пробегаемся по всем вершинам и ищем более короткий путь
    //через вершину k
    for(int k = 0; k < Graph1.Edges.size(); k++) {
        for(int i = 0; i < Graph1.Edges.size(); i++) {
            for(int j = 0; j < Graph1.Edges.size(); j++) {
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
void FloydWarshallCallBackParamsTailHandler(int N, std::vector<std::vector<int>>& MPathLength, std::vector<std::vector<int>>& MPath) //чтобы в объекте класса статистики функция работала как нужно.
{
    MPathLength.resize(N);
    for(auto& i: MPathLength) i.resize(N);

    MPath.resize(N);
    for(auto& i: MPath) i.resize(N);
}

//Дейкстра==================================
void Dijkstra(Graph& Graph1, int SourceIndex, std::vector<std::vector<int>>& Pathes, presenthandler& PresentHandler)
{
    int MAX_WEIGHT=std::numeric_limits<int>::max();
    int NULL_INDEX=std::numeric_limits<int>::max();
    int minWeightIndex; //Индекс вершины с минимальным весом
    int minWeight; //Вес вершины с минимальным весом

    //Подготовка цветов и весов вершин.
    Graph1.vertsVertices.ResetColors();
    for(auto& i: Graph1.Vertices)
    {
        i.Weight=MAX_WEIGHT;
    }
    Graph1.Vertices.at(SourceIndex).Weight=0;

    //Нахождение весов всех вершин. Т.е. минимальных путей от начальной вершины до всех остальных вершин.
    do
    {
        /*  Поиск вершины с минимальным весом*/
        minWeightIndex = NULL_INDEX;
        minWeight = MAX_WEIGHT;
        for (int i = 0; i<Graph1.Vertices.size(); i++)
        { 
            if ((Graph1.Vertices.at(i).Color == 11) && (Graph1.Vertices.at(i).Weight<minWeight)) //Если вершину ещё не обошли и вес меньше min
            { // Переприсваиваем значения
                minWeight = Graph1.Vertices.at(i).Weight;
                minWeightIndex = i;
            }
        }

        /*Обход соседей(вершин) из выбранной вершины*/
        // Добавляем найденный минимальный вес к текущему весу вершины и сравниваем с текущим минимальным весом вершины
        if (minWeightIndex != NULL_INDEX) //Если удалось найти непомеченную вершину
        {
            for (int i = 0; i<Graph1.Vertices.size(); i++)
            {
                if (Graph1.Edges.at(minWeightIndex).at(i).Weight > 0)
                {
                    int tempWeight = minWeight + Graph1.Edges.at(minWeightIndex).at(i).Weight;
                    if (tempWeight < Graph1.Vertices.at(i).Weight)
                    {
                        Graph1.Vertices.at(i).Weight = tempWeight;
                    }
                }
            }
            Graph1.Vertices.at(minWeightIndex).Color=13;
        }
        if(PresentHandler.Mode>=1)
        {
            Graph1.ShowPlot(PresentHandler.Mode-1, std::string("DijkstraPic").append(PresentHandler.GetFileNumberAndIncrease()));
            if(PresentHandler.Mode==1) getchar();
        }
    } while (minWeightIndex != NULL_INDEX);


    //Нахождение путей от исходной вершины до всех остальных вершин
    for(int DestIndex=0; DestIndex<Graph1.Vertices.size(); DestIndex++) //ищем путь до каждой вершины из исходной
    {
        // Восстановление пути
        std::vector<int> tempPath; //вектор, в котором путь от исходной вершины до другой вершины хранится задом наперед.
        int CurrentDestIndex=DestIndex; //CurrentDestIndex -величина, в которой мы будем хранить нашу текущую вершину при нахождении пути.
        tempPath.push_back(CurrentDestIndex); // начальный элемент - конечная вершина
    //  int k = 1; // индекс предыдущей вершины
        int DestWeight = Graph1.Vertices.at(CurrentDestIndex).Weight; // вес конечной вершины

        while (CurrentDestIndex != SourceIndex) // пока не дошли до начальной вершины
        {
            for (int i = 0; i<Graph1.Vertices.size(); i++) // просматриваем все вершины
                if (Graph1.Edges.at(i).at(CurrentDestIndex).Weight != 0)   // если связь есть
                {
                    int tempWeight = DestWeight - Graph1.Edges.at(i).at(CurrentDestIndex).Weight; // определяем вес пути из предыдущей вершины
                    if (tempWeight == Graph1.Vertices.at(i).Weight) // если вес совпал с рассчитанным
                    {                 // значит из этой вершины и был переход
                        DestWeight = tempWeight; // сохраняем новый вес
                        CurrentDestIndex = i;       // сохраняем предыдущую вершину
                        tempPath.push_back(i); // и записываем ее в массив
                    }
                }
        }

        //переворачиваем и записываем tempPath
        while(tempPath.size()!=0)
        {
            Pathes.at(DestIndex).push_back(tempPath.back());
            tempPath.pop_back();
        }
    }
}


#endif //SHORTESTPATHFUNC_H_INCLUDED