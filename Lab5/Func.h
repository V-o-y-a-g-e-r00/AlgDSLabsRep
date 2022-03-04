#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random> 

#include "presenthandler.h"


#include "Graph.h"


void GenerateAdjacencyProb(Graph& Graph1, double probability, std::default_random_engine generator, bool IsWithLoops) //генерируем матрицу смежности. probability -вероятность появления ребра
{
    //настраиваем генератор
    std::discrete_distribution<int> distribution {1-probability, probability}; //единички генерируются с вероятностью probability, а нолики с вероятностью 1-probability

 //   std::vector<std::vector<int>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам)
 //   std::vector<int>::iterator iterj;
    for(int i=0; i<Graph1.Edges.size(); i++)
    {
        for(int j=0; j<Graph1.Edges.at(i).size();j++)
        {
            if(IsWithLoops)
            {
                if(j>=i)
                {
                    //int dice_roll = distribution(generator);
                    Graph1.Edges.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
                }
                else
                {
                    Graph1.Edges.at(i).at(j).Adjacency=Graph1.Edges.at(j).at(i).Adjacency; //граф неориентированный
                }
            }
            else
            {
                if(j==i)
                {
                    Graph1.Edges.at(i).at(j).Adjacency=0;
                }
                else
                {
                    if(j>i)
                    {
                        //int dice_roll = distribution(generator);
                        Graph1.Edges.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
                    }
                    else
                    {
                        Graph1.Edges.at(i).at(j).Adjacency=Graph1.Edges.at(j).at(i).Adjacency; //граф неориентированный
                    }
                }

            }
        }

    }
}

void GenerateAdjacencyMNumberWithLoops(Graph& Graph1, int m, std::default_random_engine& generator) //генерируем матрицу смежности. m -число ребер в случайном графе. generator нужно передавать, если мы хотим, чтобы была возможность генерации одинаковой последовательности при многократном вызове функции
{
 
    //настраиваем генератор
//    std::default_random_engine generator(seed);

    int n=(Graph1.Edges.size()+1)*Graph1.Edges.size()/2; //общее число случаев в классическом определении вероятности (пользуемся формулой арфиметической прогрессии для нахождения числа ячеек)
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
    for(int i=0; i<Graph1.Edges.size(); i++)
    {
        for(int j=0; j<Graph1.Edges.at(i).size();j++)
        {
            if(j>=i)
            {
                std::discrete_distribution<int> distribution {1-(double)m/n, (double)m/n}; //
                //int dice_roll = distribution(generator);
                Graph1.Edges.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
                if(Graph1.Edges.at(i).at(j).Adjacency!=0) //пользуемся классическим определением вероятности
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
                Graph1.Edges.at(i).at(j).Adjacency=Graph1.Edges.at(j).at(i).Adjacency; //граф неориентированный
            }
        }
    }
}
void GenerateAdjacencyMNumberNoLoops(Graph& Graph1, int m, std::default_random_engine& generator) //генерируем матрицу смежности. m -число ребер в случайном графе.
{

    //настраиваем генератор
//    std::default_random_engine generator(seed);

    int n=(Graph1.Edges.size()-1+0)*Graph1.Edges.size()/2; //общее число случаев в классическом определении вероятности (пользуемся формулой арфиметической прогрессии для нахождения числа ячеек)
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
    for(int i=0; i<Graph1.Edges.size(); i++)
    {
        for(int j=0; j<Graph1.Edges.at(i).size();j++)
        {
            if(j==i)
            {
                Graph1.Edges.at(i).at(j).Adjacency=0;
            }
            else
            {
                if(j>i)
                {
                    std::discrete_distribution<int> distribution {1-(double)m/n, (double)m/n}; //
                    //int dice_roll = distribution(generator);
                    Graph1.Edges.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
                    if(Graph1.Edges.at(i).at(j).Adjacency!=0) //пользуемся классическим определением вероятности
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
                    Graph1.Edges.at(i).at(j).Adjacency=Graph1.Edges.at(j).at(i).Adjacency; //граф неориентированный
                }
            }
        }
    }
}
void GenerateWeights(Graph& Graph1, std::default_random_engine& generator, int WeightMin, int WeightMax)
{
    std::uniform_int_distribution<int> distribution(WeightMin, WeightMax);
    for(int i=0; i<Graph1.Edges.size(); i++)
    {
        for(int j=0; j<Graph1.Edges.at(i).size();j++)
        {
            if(j>=i)
            {
                Graph1.Edges.at(i).at(j).Weight=distribution(generator);
            }
            else
            {
                Graph1.Edges.at(i).at(j).Weight=Graph1.Edges.at(j).at(i).Weight;
            }
        }
    }
}




int DFS(Graph& Graph1, int StartVert, presenthandler& PresentHandler) //IsStepByStep 0-не по шагам; 1-по шагам; 2-вывод в файл
{
  /*  if(StartVert>=Vertices.Vector.size() || StartVert<0)
    {
        std::stringstream ss;
        ss<<"StartVert cannot be equal to "<< StartVert <<std::endl;
        throw(ss.str());
    }
    */
    Graph1.Vertices.at(StartVert).Color=12;
    int ColoredVertNumber=1;
    for(int j=0; j<Graph1.Vertices.size(); j++)
    {
        if((Graph1.Edges.at(StartVert).at(j).Adjacency==1) && (Graph1.Vertices.at(j).Color!=12))
        {
            if(PresentHandler.Mode>=1)
            {
                Graph1.ShowPlot(PresentHandler.Mode-1, std::string("Pic").append(PresentHandler.GetFileNumberAndIncrease()));
                if(PresentHandler.Mode==1) getchar();
            }
            ColoredVertNumber+=DFS(Graph1, j, PresentHandler);
            
        }
    }
    return ColoredVertNumber;
}
bool IsConnectedDFS(Graph& Graph1, int StartVert, presenthandler& PresentHandler) //Проверка связности графа с помощью обхода в глубину
{
//    int dtemp=DFS(Vertices, Edges, StartVert);
//    std::cout<<"DFS="<<dtemp<<" Vertices.Vector.size()="<<Vertices.Vector.size()<<std::endl;
    if(DFS(Graph1, StartVert, PresentHandler)==Graph1.Vertices.size())
    {
        if(PresentHandler.Mode>=1)
        {
            Graph1.ShowPlot(PresentHandler.Mode-1, std::string("Pic").append(PresentHandler.GetFileNumberAndIncrease()));
            if(PresentHandler.Mode==1) getchar();
        }
        Graph1.vertsVertices.ResetColors();
        return true;
    }
    else
    {
        if(PresentHandler.Mode>=1)
        {
            Graph1.ShowPlot(PresentHandler.Mode-1, std::string("Pic").append(PresentHandler.GetFileNumberAndIncrease()));
            if(PresentHandler.Mode==1) getchar();
        }
        Graph1.vertsVertices.ResetColors();
        return false;
    }
}
template<typename T>
void PrintMatrix(std::vector<std::vector<T>>& Matrix, const char* MatrixName)
{
    typename std::vector<std::vector<T>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам) .Без typename вообще не компилируется, хотя казалось бы.
    typename std::vector<T>::iterator iterj;
    for(iteri=Matrix.begin(); iteri!=Matrix.end(); iteri++)
    {
        std::cout<< MatrixName<<"["<<std::distance(Matrix.begin(), iteri) <<"]=";
        for(iterj=iteri->begin(); iterj!=iteri->end(); iterj++)
        {
            std::cout<< (*iterj)<<"\t";
        }
        std::cout<<std::endl;
    }
    std::cout<<"----------"<<std::endl;
}
/*template<typename T>
void PrintMatrixToFile(std::vector<std::vector<T>>& Matrix, const char* MatrixName, const char* filename)
{
    std::ofstream fd(filename);
    typename std::vector<std::vector<T>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам) .Без typename вообще не компилируется, хотя казалось бы.
    typename std::vector<T>::iterator iterj;
    for(iteri=Matrix.begin(); iteri!=Matrix.end(); iteri++)
    {
       // fd<< MatrixName<<"["<<std::distance(Matrix.begin(), iteri) <<"]=";
        for(iterj=iteri->begin(); iterj!=iteri->end(); iterj++)
        {
            fd<< (*iterj)<<"\t";
        }
        fd<<std::endl;
    }
    fd.close();
}*/
#endif //FUNC_H_INCLUDED