#ifndef EDGES_H_INCLUDED
#define EDGES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include <iomanip>
#include <sstream>

class edges
{
public:
    struct edge
    {
        int Adjacency=0; //существование ребра
        int Weight=0; //вес ребра
        int Color=1; //1 черный 2 зеленый; 3 голубой; 4 красный
    };
    std::vector<std::vector<edge>> Vector;

    edges(int N): Vector(N)
    {
        for(auto& iter: Vector)
            iter.resize(N);
    }
    void PrintEdges(const char* filename="std::cout") // можно ввести "std::cout" и тогда информация будет выведена в консоль. Для рисования графиков не используется
    {
        if(!strcmp(filename, "std::cout")) //если строки равны
        {
            std::cout<<"[Adgacency Weight Color]"<<std::endl;
            for(auto& i: Vector)
            {
                for(auto& j: i)
                {
                    std::stringstream ss;
                    ss<<"["<<j.Adjacency<<" "<<j.Weight<<" "<<j.Color<<"]";
                //    std::cout.setf(std::ios::left);
                 //   std::cout.left;
                //    std::cout<<std::setfill('=')<<std::setw(20) << std::left << ss.str();
                    std::cout<<std::setw(10) << std::left << ss.str();
                }
                std::cout<<std::endl;
            }
        }
        else
        {
            std::ofstream fd(filename); 
            fd<<"[Adgacency Weight Color]"<<std::endl;
            for(auto& i: Vector)
            {
                for(auto& j: i)
                    fd<<"["<<j.Adjacency<<" "<<j.Weight<<" "<<j.Color<<"] ";
                fd<<std::endl;
            }
            fd.close();
        }
    }
    void SetEdgesForPlot(const char* fname="EdgesForPlot.dat")
    {       
        std::ofstream fd(fname);
        fd<<"#i;j;Weight;Color"<<std::endl;
        for(int i=0; i<Vector.size(); i++)
            for(int j=i; j<Vector.at(i).size(); j++) //просматриваем только верхний угл. Граф у нас неориентированный! Тут заполняется вектор с ребрами
            {  
            //    std::cout<<i<<"\t"<<j<<"\t"<<Edges.at(i).at(j).Weight<<"\t"<<Edges.at(i).at(j).Color<<std::endl;
                if(Vector.at(i).at(j).Adjacency==1)
                {   
                    fd<<i<<"\t"<<j<<"\t"<<Vector.at(i).at(j).Weight<<"\t"<<Vector.at(i).at(j).Color<<std::endl;
                }
            }
        fd.close();
    }

};

#endif //EDGES_H_INCLUDED