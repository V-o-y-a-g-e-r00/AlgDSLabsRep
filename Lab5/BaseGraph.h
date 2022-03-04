#ifndef BASEGRAPH_H
#define BASEGRAPH_H

#include <vector>



//смотри UML диаграмму
class BaseGraph
{
public:
struct vertex
{
    double x=0; //Оставить или нет координаты - вопрос. На сколько они являются характеристикой самого графа, а не его изображения.
    double y=0;
    int Weight=0;
    int Color=11; //Определяет стиль в gnuplot. 11 белый; 12 зеленый; 13 голубой; 14 красный
};
struct edge
{
    int Adjacency=0; //существование ребра
    int Weight=0; //вес ребра
    int Color=1; //1 черный 2 зеленый; 3 голубой; 4 красный
};

std::vector<vertex> Vertices;
std::vector<std::vector<edge>> Edges;
bool IsOriented=false; //Ну тоже свойства графа, как-никак. Т.е. не отображения, а самого графа.
bool IsWithVerticesWeights=false;

BaseGraph(int N, bool NIsOriented=false):Vertices(N), Edges(N), IsOriented(NIsOriented)
{
    for(auto& i: Edges)
    {
        i.resize(N);
    }
}


};
#endif /* BASEGRAPH_H */
