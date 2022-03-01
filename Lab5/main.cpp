#include <iostream>

#include <math.h>
#include <vector>
#include <fstream>
#include <iomanip> //setprecision
//#include <string> //будем использовать для нахождения максимальной точности вероятности

#include <random> 

#include <cstring>

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
    void PrintEdges(const char* filename="std::cout") // можно ввести "std::cout" и тогда информация будет выведена в консоль
    {
        if(!strcmp(filename, "std::cout")) //если строки равны
        {
            std::cout<<"[Adgacency Weight Color]"<<std::endl;
            for(auto& i: Vector)
            {
                for(auto& j: i)
                    std::cout<<"["<<j.Adjacency<<" "<<j.Weight<<" "<<j.Color<<"] ";
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
    //Функции для вывода отдельных полей в виде матриц в файл. Не используются для рисования графиков. Нужны, чтобы сохранить результат.
    


};

void GenerateAdjacencyProb(edges& Edges, int seed, double probability) //генерируем матрицу смежности. probability -вероятность появления ребра
{
    //настраиваем генератор
    std::default_random_engine generator(seed);
    std::discrete_distribution<int> distribution {1-probability, probability}; //единички генерируются с вероятностью probability, а нолики с вероятностью 1-probability

    std::vector<std::vector<int>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам)
    std::vector<int>::iterator iterj;
    for(int i=0; i<Edges.Vector.size(); i++)
    {
        for(int j=0; j<Edges.Vector.at(i).size();j++)
        {
            if(j>=i)
            {
                //int dice_roll = distribution(generator);
                Edges.Vector.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
            }
            else
            {
                Edges.Vector.at(i).at(j).Adjacency=Edges.Vector.at(i).at(j).Adjacency; //граф неориентированный
            }
        }
    }
}

void GenerateAdjacencyMNumber(edges& Edges, int seed, int m) //генерируем матрицу смежности. m -число ребер в случайном графе
{

    //настраиваем генератор
    std::default_random_engine generator(seed);

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

void SetGraphInfo(edges& Edges, const char* filename) //число вершин и ребер в файл
{
    int m=0; //число ребер в графе
    for(int i=0; i<Edges.Vector.size(); i++)
        for(int j=i; j<Edges.Vector.at(i).size(); j++)
        {
            m+=Edges.Vector.at(i).at(j).Adjacency;
        }
    std::ofstream fd(filename);
  //  fd<<AdjacencyMatrix.size()<<"\t"<<m<<std::endl;
    fd<<"\"n="<<Edges.Vector.size()<<";m="<<m<< "\""<<std::endl;
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

/*bool DFSConnectivityCheck(std::vector<std::vector<int>>& AdjacencyMatrix, std::vector<vertex>& vertices) //Проверка связности графа с помощью обхода в глубину
{
    return false;
}*/
int main(int, char**) {
    int seed=time(0);
    //int seed=0; 

    int N=50;
    vertices Vertices(N);
    edges Edges(N);


//    GenerateAdjacencyProb(Edges, seed, 0.5);
    try {GenerateAdjacencyMNumber(Edges, seed, 50);}
    catch(std::string str)
    {
        std::cout<<"exeption:"<<str<<std::endl;
        return -1;
    }

//    PrintMatrix<int>(AdjacencyMatrix, "AdjacencyMatrix");
//    PrintMatrixToFile(AdjacencyMatrix, "AdjacencyMatrix", "AdjacencyMatrixOut.txt");

    Edges.SetEdgesForPlot();
    Edges.PrintEdges();
    Edges.PrintEdges("Edges.txt");
    Vertices.SetVertXYForPlot();
    Vertices.PrintVertices();
    Vertices.PrintVertices("Vertices.dat");
    SetGraphInfo(Edges, "GraphInfo.dat"); //число вершин и ребер в файл
    system("./PlotGraph.gpi");
}
