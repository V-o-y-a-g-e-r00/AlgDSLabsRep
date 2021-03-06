#ifndef VISUALGRAPH_H
#define VISUALGRAPH_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <math.h>

#include "BaseGraph.h"

#define RADIUS 40

class VisualGraph: public BaseGraph
{
public:
    VisualGraph(int N, bool NIsOriented=false):BaseGraph(N, NIsOriented)
    {

    }

//void SetVarsForScript(edges& Edges, bool IsOriented, bool IsWithVerticesWeights, bool IsSavePictureToFile, std::string PictureName,const char* filename) //Эти величины будет читать bash скрипт. Edges, чтобы мы могли вывести число вершин и ребер 
    void SetVarsForScript(bool IsSavePictureToFile, std::string PictureName, const char* filename) //Эти величины будет читать bash скрипт. Edges, чтобы мы могли вывести число вершин и ребер 
    {
        int m=0; //число ребер в графе
        for(int i=0; i<Edges.size(); i++)
            for(int j=i; j<Edges.at(i).size(); j++)
            {
                m+=Edges.at(i).at(j).Adjacency;
            }
        std::ofstream fd(filename);
        fd<<"#nmtitle IsOriented IsSavePictureToFile PictureName IsWithVerticesWeights"<<std::endl;
        fd<<"\"n="<<Edges.size()<<"; m="<<m<< "\"\t"<<IsOriented<<"\t"<<IsSavePictureToFile<<"\t"<<PictureName<<"\t"<<IsWithVerticesWeights<<std::endl;
        fd.close();
    }



    void PrintVertices(const char* filename="std::cout")
    {
        if(!strcmp(filename, "std::cout")) //если строки равны
        {
            std::cout<<"#i; x; y; color;weight"<<std::endl;
            for(int i=0; i<Vertices.size(); i++)
            {
                std::cout<<i<<" "<<Vertices.at(i).x<<" "<<Vertices.at(i).y<<" "<<Vertices.at(i).Color<<" "<<Vertices.at(i).Weight<<std::endl;
            }
        }
        else
        {
            std::ofstream fd(filename); 
            fd<<"#i; x; y; color;weight"<<std::endl;
            for(int i=0; i<Vertices.size(); i++)
            {
                fd<<i<<" "<<Vertices.at(i).x<<" "<<Vertices.at(i).y<<" "<<Vertices.at(i).Color<<" "<<Vertices.at(i).Weight<<std::endl;
            }
            fd.close();
        }
    }
    void SetVertXYForPlot(int CenterX=0, int CenterY=0, const char* fname="Vertices.dat")
    {
        double r=RADIUS;
        double alpha=0;
        double dalpha=2*M_PI/Vertices.size();
        
        double x, y;
        int CurrVertIndex=0;

        for(int i=0; i<Vertices.size(); i++)
        {
            //(i%2==0) ? r/=1.5 : r*=1.5;
            
        //    Vector.at(i).VertIndex=i;
            Vertices.at(i).x=cos(alpha)*r;
            Vertices.at(i).y=sin(alpha)*r;
            
            if(i%8<4) r-=RADIUS*0.15; //в виде звезды
            else r+=RADIUS*0.15;
            alpha+=dalpha;
        }
    }





    void PrintEdges(const char* filename="std::cout") // можно ввести "std::cout" и тогда информация будет выведена в консоль. Для рисования графиков не используется
    {
        if(!strcmp(filename, "std::cout")) //если строки равны
        {
            std::cout<<"[Adgacency Weight Color]"<<std::endl;
            for(auto& i: Edges)
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
            for(auto& i: Edges)
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
        if(IsOriented)
        {
            for(int i=0; i<Edges.size(); i++)
            {
                for(int j=0; j<Edges.at(i).size(); j++) //Граф у нас ориентированный! Тут заполняется вектор с ребрами
                {  
                //    std::cout<<i<<"\t"<<j<<"\t"<<Edges.at(i).at(j).Weight<<"\t"<<Edges.at(i).at(j).Color<<std::endl;
                    if(Edges.at(i).at(j).Adjacency==1)
                    {   
                        fd<<i<<"\t"<<j<<"\t"<<Edges.at(i).at(j).Weight<<"\t"<<Edges.at(i).at(j).Color<<std::endl;
                    }
                }
            }
        }
        else
        {
            for(int i=0; i<Edges.size(); i++)
            {
                for(int j=i; j<Edges.at(i).size(); j++) //просматриваем только верхний угл. Граф у нас неориентированный! Тут заполняется вектор с ребрами
                {  
                //    std::cout<<i<<"\t"<<j<<"\t"<<Edges.at(i).at(j).Weight<<"\t"<<Edges.at(i).at(j).Color<<std::endl;
                    if(Edges.at(i).at(j).Adjacency==1)
                    {   
                        fd<<i<<"\t"<<j<<"\t"<<Edges.at(i).at(j).Weight<<"\t"<<Edges.at(i).at(j).Color<<std::endl;
                    }
                }
            }
        }

        fd.close();
    }

    void ShowPlot(bool IsSavePictureToFile=false, std::string PictureName="pic", bool IsSetVertXYForPlot=true) //PictureName без расширения
    {
        if(IsSetVertXYForPlot) SetVertXYForPlot();

        PrintVertices("Vertices.dat");
        SetEdgesForPlot(); //Вывод в файл для рисования графа 
        PrintEdges("Edges.txt"); //вывод информации о ребрах для наглядности. Не используется для рисования графа

        SetVarsForScript(IsSavePictureToFile, PictureName, "VarsForScript.dat"); //число вершин и ребер в файл
        system("./PlotGraph.bash");
    }

};

#endif /* VISUALGRAPH_H */
