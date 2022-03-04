#ifndef GRAPH_H
#define GRAPH_H

#include "VisualGraph.h"

class Graph: public VisualGraph
{
public:
    class vertices
    {
    private:
        std::vector<vertex>& refVertices; //ссылка на массив вершин, находящийся в родительском объекте. Решил сделать закрытой, т.к. обращение к одной сущности по двум именам не есть гуд.
    public:
        vertices(std::vector<vertex>& NrefVertices): refVertices(NrefVertices)
        {

        }
        void ResetColors()
        {
            for(auto& i: refVertices) i.Color=11;
        }
    };
    class edges
    {
    private:
        std::vector<std::vector<edge>>& refEdges;
    public:
        edges(std::vector<std::vector<edge>>& NrefEdges): refEdges(NrefEdges)
        {

        }
        void ResetColors()
        {
            for(auto& i: refEdges)
                for(auto& j: i) j.Color=1;
        }

    };

    vertices vertsVertices; //обертки
    edges edgesEdges;

    Graph(int N, bool NIsOriented=false): VisualGraph(N, NIsOriented), vertsVertices(BaseGraph::Vertices), edgesEdges(BaseGraph::Edges) //инициализируем ссылки на массивы в базовом объекте
    {

    }

};

#endif /* GRAPH_H */
