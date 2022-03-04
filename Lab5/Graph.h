#ifndef GRAPH_H
#define GRAPH_H

#include "VisualGraph.h"

class Graph: public VisualGraph
{
public:
    class vertices
    {
    public:
        std::vector<vertex>& refVertices; //ссылка на массив вершин, находящийся в родительском объекте
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
    public:
        std::vector<std::vector<edge>>& refEdges;
        edges(std::vector<std::vector<edge>>& NrefEdges): refEdges(NrefEdges)
        {

        }

    };

    vertices vertsVertices;
    edges edgesEdges;

    Graph(int N, bool NIsOriented=false): VisualGraph(N, NIsOriented), vertsVertices(BaseGraph::Vertices), edgesEdges(BaseGraph::Edges) //инициализируем ссылки на массивы в базовом объекте
    {

    }

};

#endif /* GRAPH_H */
