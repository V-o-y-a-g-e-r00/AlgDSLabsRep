#ifndef VERTICES_H_INCLUDED
#define VERTICES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <math.h>

#define RADIUS 40

class vertices
{
public:
    struct vertex
    {
        int VertIndex=0;
        double x=0;
        double y=0;
        int Color=11; //Определяет стиль в gnuplot. 11 белый; 12 зеленый; 13 голубой; 14 красный

    };
    std::vector<vertex> Vector;

    vertices(int N): Vector(N){}
    void PrintVertices(const char* filename="std::cout")
    {
        if(!strcmp(filename, "std::cout")) //если строки равны
        {
            std::cout<<"#VertIndex; x; y; color"<<std::endl;
            for(auto& i: Vector)
            {
                std::cout<<i.VertIndex<<" "<<i.x<<" "<<i.y<<" "<<i.Color<<std::endl;
            }
        }
        else
        {
            std::ofstream fd(filename); 
            fd<<"#VertIndex; x; y; color"<<std::endl;
            for(auto& i: Vector)
            {
                fd<<i.VertIndex<<" "<<i.x<<" "<<i.y<<" "<<i.Color<<std::endl;
            }
            fd.close();
        }
    }
    void SetVertXYForPlot(int CenterX=0, int CenterY=0, const char* fname="Vertices.dat")
    {
        double r=RADIUS;
        double alpha=0;
        double dalpha=2*M_PI/Vector.size();
        
        double x, y;
        int CurrVertIndex=0;

        for(int i=0; i<Vector.size(); i++)
        {
            //(i%2==0) ? r/=1.5 : r*=1.5;
            
            Vector.at(i).VertIndex=i;
            Vector.at(i).x=cos(alpha)*r;
            Vector.at(i).y=sin(alpha)*r;
            
            if(i%8<4) r-=RADIUS*0.15; //в виде звезды
            else r+=RADIUS*0.15;
            alpha+=dalpha;
        }
/*
        std::vector<vertex>::iterator iter=Vector.begin();
        for(iter=Vector.begin();iter!=Vector.end();iter++) //выводим индексы и координаты вершин на экран
        {
            std::cout<< "vertices element:"<< std::distance(Vector.begin(),iter)<<" :VertIndex="<< iter->VertIndex<< "; x="<<iter->x<<"; y="<<iter->y<<"; Color="<<iter->y<<iter->Color<<std::endl;
        }

        std::ofstream fd(fname, std::ios_base::out|std::ios_base::trunc); //выводим индексы и координаты вершин в файлик
        fd<<"#VertIndex; x; y; color"<<std::endl;
        for(iter=Vector.begin();iter!=Vector.end();iter++)
        {
            fd<< std::fixed <<std::setprecision(3)<<iter->VertIndex<< "\t"<<iter->x<<"\t"<<iter->y<<"\t"<<iter->Color<<std::endl;
        }
        fd.close();
        */
    }

};

#endif //VERTICES_H_INCLUDED