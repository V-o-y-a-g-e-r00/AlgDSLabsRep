#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random> 

#include "edges.h"
#include "vertices.h"
#include "presenthandler.h"
#include "visual.h"


void GenerateAdjacencyProb(edges& Edges, int seed, double probability, bool IsWithLoops) //генерируем матрицу смежности. probability -вероятность появления ребра
{
    //настраиваем генератор
    std::default_random_engine generator(seed);
    std::discrete_distribution<int> distribution {1-probability, probability}; //единички генерируются с вероятностью probability, а нолики с вероятностью 1-probability

 //   std::vector<std::vector<int>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам)
 //   std::vector<int>::iterator iterj;
    for(int i=0; i<Edges.Vector.size(); i++)
    {
        for(int j=0; j<Edges.Vector.at(i).size();j++)
        {
            if(IsWithLoops)
            {
                if(j>=i)
                {
                    //int dice_roll = distribution(generator);
                    Edges.Vector.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
                }
                else
                {
                    Edges.Vector.at(i).at(j).Adjacency=Edges.Vector.at(j).at(i).Adjacency; //граф неориентированный
                }
            }
            else
            {
                if(j==i)
                {
                    Edges.Vector.at(i).at(j).Adjacency=0;
                }
                else
                {
                    if(j>i)
                    {
                        //int dice_roll = distribution(generator);
                        Edges.Vector.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
                    }
                    else
                    {
                        Edges.Vector.at(i).at(j).Adjacency=Edges.Vector.at(j).at(i).Adjacency; //граф неориентированный
                    }
                }

            }
        }

    }
}

void GenerateAdjacencyMNumberWithLoops(edges& Edges, int m, std::default_random_engine& generator) //генерируем матрицу смежности. m -число ребер в случайном графе. generator нужно передавать, если мы хотим, чтобы была возможность генерации одинаковой последовательности при многократном вызове функции
{
 
    //настраиваем генератор
//    std::default_random_engine generator(seed);

    int n=(Edges.Vector.size()+1)*Edges.Vector.size()/2; //общее число случаев в классическом определении вероятности (пользуемся формулой арфиметической прогрессии для нахождения числа ячеек)
    //проверка на одз
    if(m>n)
    {
        std::string str;
        std::stringstream ss;
        ss << "m=" <<m<<" is too big! (max m=n="<<n<<")"<<std::endl;
        throw(ss.str());
    }

    std::vector<std::vector<int>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам)
    std::vector<int>::iterator iterj;
    for(int i=0; i<Edges.Vector.size(); i++)
    {
        for(int j=0; j<Edges.Vector.at(i).size();j++)
        {
            if(j>=i)
            {
                std::discrete_distribution<int> distribution {1-(double)m/n, (double)m/n}; //
                //int dice_roll = distribution(generator);
                Edges.Vector.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
                if(Edges.Vector.at(i).at(j).Adjacency!=0) //пользуемся классическим определением вероятности
                {
                    m--;
                    n--;
                }
                else
                {
                    n--;
                }
            }
            else
            {
                Edges.Vector.at(i).at(j).Adjacency=Edges.Vector.at(j).at(i).Adjacency; //граф неориентированный
            }
        }
    }
}
void GenerateAdjacencyMNumberNoLoops(edges& Edges, int m, std::default_random_engine& generator) //генерируем матрицу смежности. m -число ребер в случайном графе.
{

    //настраиваем генератор
//    std::default_random_engine generator(seed);

    int n=(Edges.Vector.size()-1+0)*Edges.Vector.size()/2; //общее число случаев в классическом определении вероятности (пользуемся формулой арфиметической прогрессии для нахождения числа ячеек)
    //проверка на одз
    if(m>n)
    {
        std::string str;
        std::stringstream ss;
        ss << "m=" <<m<<" is too big! (max m=n="<<n<<")"<<std::endl;
        throw(ss.str());
    }

 //   std::vector<std::vector<int>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам)
 //   std::vector<int>::iterator iterj;
    for(int i=0; i<Edges.Vector.size(); i++)
    {
        for(int j=0; j<Edges.Vector.at(i).size();j++)
        {
            if(j==i)
            {
                Edges.Vector.at(i).at(j).Adjacency=0;
            }
            else
            {
                if(j>i)
                {
                    std::discrete_distribution<int> distribution {1-(double)m/n, (double)m/n}; //
                    //int dice_roll = distribution(generator);
                    Edges.Vector.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
                    if(Edges.Vector.at(i).at(j).Adjacency!=0) //пользуемся классическим определением вероятности
                    {
                        m--;
                        n--;
                    }
                    else
                    {
                        n--;
                    }
                }
                else
                {
                    Edges.Vector.at(i).at(j).Adjacency=Edges.Vector.at(j).at(i).Adjacency; //граф неориентированный
                }
            }
        }
    }
}
void GenerateWeights(edges& Edges, std::default_random_engine& generator, int WeightMin, int WeightMax)
{
    std::uniform_int_distribution<int> distribution(WeightMin, WeightMax);
    for(int i=0; i<Edges.Vector.size(); i++)
    {
        for(int j=0; j<Edges.Vector.at(i).size();j++)
        {
            if(j>=i)
            {
                Edges.Vector.at(i).at(j).Weight=distribution(generator);
            }
            else
            {
                Edges.Vector.at(i).at(j).Weight=Edges.Vector.at(j).at(i).Weight;
            }
        }
    }
}




int DFS(vertices& Vertices, edges& Edges, int StartVert, presenthandler& PresentHandler) //IsStepByStep 0-не по шагам; 1-по шагам; 2-вывод в файл
{
  /*  if(StartVert>=Vertices.Vector.size() || StartVert<0)
    {
        std::stringstream ss;
        ss<<"StartVert cannot be equal to "<< StartVert <<std::endl;
        throw(ss.str());
    }
    */
    Vertices.Vector.at(StartVert).Color=12;
    int ColoredVertNumber=1;
    for(int j=0; j<Vertices.Vector.size(); j++)
    {
        if((Edges.Vector.at(StartVert).at(j).Adjacency==1) && (Vertices.Vector.at(j).Color!=12))
        {
            if(PresentHandler.Mode>=1)
            {
                ShowPlot(Vertices, Edges, false, PresentHandler.Mode-1, std::string("Pic").append(PresentHandler.GetFileNumberAndIncrease()));
                if(PresentHandler.Mode==1) getchar();
            }
            ColoredVertNumber+=DFS(Vertices, Edges, j, PresentHandler);
            
        }
    }
    return ColoredVertNumber;
}
bool IsConnectedDFS(vertices& Vertices, edges& Edges, int StartVert, presenthandler& PresentHandler) //Проверка связности графа с помощью обхода в глубину
{
//    int dtemp=DFS(Vertices, Edges, StartVert);
//    std::cout<<"DFS="<<dtemp<<" Vertices.Vector.size()="<<Vertices.Vector.size()<<std::endl;
    if(DFS(Vertices, Edges, StartVert, PresentHandler)==Vertices.Vector.size())
    {
        if(PresentHandler.Mode>=1)
        {
            ShowPlot(Vertices, Edges, false, PresentHandler.Mode-1, std::string("Pic").append(PresentHandler.GetFileNumberAndIncrease()));
            if(PresentHandler.Mode==1) getchar();
        }
        Vertices.ResetColors();
        return true;
    }
    else
    {
        if(PresentHandler.Mode>=1)
        {
            ShowPlot(Vertices, Edges, false, PresentHandler.Mode-1, std::string("Pic").append(PresentHandler.GetFileNumberAndIncrease()));
            if(PresentHandler.Mode==1) getchar();
        }
        Vertices.ResetColors();
        return false;
    }
}
#endif //FUNC_H_INCLUDED