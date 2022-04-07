#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <string>
#include <sstream>
#include "VisualGraph.h"


class Graph: public VisualGraph
{
public:
    class vertices
    {
    private:
        std::vector<vertex>& refVertices; //ссылка на массив вершин, находящийся в родительском объекте. Решил сделать закрытой, т.к. обращение к одной сущности по двум именам не есть гуд.
    //    void getlineWithCheck()
    
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
/*        std::istream& getlineCheck() //возвр тип как у std::getline()
        {

        }*/
    public:
        edges(std::vector<std::vector<edge>>& NrefEdges): refEdges(NrefEdges)
        {

        }
        void ResetColors()
        {
            for(auto& i: refEdges)
                for(auto& j: i) j.Color=1;
        }
        void AdjacencyFromFile(char *filename)
        {
            std::ifstream fin(filename);
            if(!fin.is_open()) //проверка на успешность открытия файла
            {
                std::stringstream ss;
                ss << "Can not open file:"<<filename<<std::endl;
                throw(ss.str());
            }
            for(int i=0; i<refEdges.size(); i++)
            {
                std::string str; //Строка из файла
                bool IsSatisf=false; //fasle строку нужно пропустить. Т.е. не пускать её в данные.
                do{
                    
                    if(std::getline(fin, str)) //чтение прошло успешно //getline возвращает указатель потока. Указатель потока при перегрузке в bool в "хорошем" состоянии перегружается в true в "плохом" в false. Т.е. если чтение было удачным, то вернется true
                    {
                        if(str=="")
                        {
                            std::cout<<"AdjacencyFromFile: Unexpected empty string in file. Do you sure about your array size in file? The data will be read anyway"<<std::endl;
                            IsSatisf=false;
                        }
                        else if(str.at(0)=='#')
                        {
                            IsSatisf=false;
                        }
                        else IsSatisf=true;
                    }
            //    std::cout<<"fin.good()="<<fin.good()<<"!IsSatisf="<<!IsSatisf<<std::endl;
                }while(fin.good() && !IsSatisf);
                if(!fin.good()&&!IsSatisf)
                {
                    if(fin.eof())
                    {
                        std::cout<<"AdjacencyFromFile: Unexpected end of file. Do you sure about your array size in file? The data will be read anyway"<<std::endl;
                    }
                    else
                    {
                        std::cout<<"AdjacencyFromFile: Unexpected error"<<std::endl;
                    }
                    break; //выходим из итеративного цикла
                }
                std::cout<<"str="<<str<<std::endl;


                std::stringstream ss;
                ss<<str;
                for(int j=0; j<refEdges.size(); j++)
                {
                    ss>>refEdges.at(i).at(j).Adjacency;
                }
            }
            fin.close();
        }

    };

    vertices vertsVertices; //обертки
    edges edgesEdges;

    Graph(int N, bool NIsOriented=false): VisualGraph(N, NIsOriented), vertsVertices(BaseGraph::Vertices), edgesEdges(BaseGraph::Edges) //инициализируем ссылки на массивы в базовом объекте
    {

    }

};

#endif /* GRAPH_H */
