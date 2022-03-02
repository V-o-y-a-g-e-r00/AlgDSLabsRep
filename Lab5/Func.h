#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random> 

#include "edges.h"


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
/* void test(edges& Edges)
{
    
}*/
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
    for(auto& i: Edges.Vector)
        for(auto& j: i)
        {
            if(j.Adjacency==1)
            {
                j.Weight=distribution(generator);
            }
        }
}


void SetVarsForScript(edges& Edges, bool IsOriented, bool IsSavePictureToFile, const char* PictureName, const char* filename) //Эти величины будет читать bash скрипт. Edges, чтобы мы могли вывести число вершин и ребер 
{
    int m=0; //число ребер в графе
    for(int i=0; i<Edges.Vector.size(); i++)
        for(int j=i; j<Edges.Vector.at(i).size(); j++)
        {
            m+=Edges.Vector.at(i).at(j).Adjacency;
        }
    std::ofstream fd(filename);
    fd<<"#nmtitle IsOriented IsSavePictureToFile PictureName"<<std::endl;
    fd<<"\"n="<<Edges.Vector.size()<<"; m="<<m<< "\"\t"<<IsOriented<<"\t"<<IsSavePictureToFile<<"\t"<<PictureName<<std::endl;
    fd.close();
}
/*template<typename T>
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
} */
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
void ShowPlot(vertices& Vertices, edges& Edges, bool IsSavePictureToFile=false, const char* PictureName="Pic1")
{
    Vertices.SetVertXYForPlot();
    Vertices.PrintVertices("Vertices.dat");
    Edges.SetEdgesForPlot(); //Вывод в файл для рисования графа 
    Edges.PrintEdges("Edges.txt"); //вывод информации о ребрах для наглядности. Не используется для рисования графа

    SetVarsForScript(Edges, false, false, PictureName, "VarsForScript.dat"); //число вершин и ребер в файл
    system("./PlotGraph.bash");
}
int DFS(vertices& Vertices, edges& Edges, int StartVert, bool IsStepByStep)
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
            if(IsStepByStep)
            {
                ShowPlot(Vertices, Edges);
                getchar();
            }
            ColoredVertNumber+=DFS(Vertices, Edges, j, IsStepByStep);
            
        }
    }
    return ColoredVertNumber;
}
bool IsConnectedDFS(vertices& Vertices, edges& Edges, int StartVert, bool IsStepByStep) //Проверка связности графа с помощью обхода в глубину
{
//    int dtemp=DFS(Vertices, Edges, StartVert);
//    std::cout<<"DFS="<<dtemp<<" Vertices.Vector.size()="<<Vertices.Vector.size()<<std::endl;
    if(DFS(Vertices, Edges, StartVert, IsStepByStep)==Vertices.Vector.size()) return true;
    else return false;
}
#endif //FUNC_H_INCLUDED